
#include "Animation.h"
#include"AnimationInfo.h"
#include"../Resource/Animation/AnimationSequence.h"
#include"../Scene/Scene.h"
#include"../Scene/SceneResource.h"
#include"../Resource/ResourceManager.h"


CAnimation::CAnimation() :
    m_Owner(nullptr),
    m_Scene(nullptr),
    m_CurrentAnimation(nullptr)
{
}

CAnimation::~CAnimation()
{
    auto iter = m_mapAnimation.begin();
    auto iterEnd = m_mapAnimation.end();

    for (; iter != iterEnd; ++iter)
    {
        SAFE_DELETE(iter->second);
    }
}

void CAnimation::AddAnimation(const std::string& SequenceName, bool Loop, float PlayTime, float PlayScale, bool Reverse)
{
    if (FindInfo(SequenceName))
        return;

    CAnimationSequence* Sequence = nullptr;

    if (m_Scene)
    {
         Sequence = m_Scene->GetSceneResource()->FindAnimation(SequenceName);
    }

    else
    {
        Sequence = CResourceManager::GetInst()->FindAnimation(SequenceName);
    }

    if (!Sequence)
        return;

    CAnimationInfo* Info = new CAnimationInfo;

    Info->m_Sequence = Sequence;
    Info->m_Loop = Loop;
    Info->m_PlayTime = PlayTime;
    Info->m_PlayScale = PlayScale;
    Info->m_Reverse = Reverse;
    Info->m_FrameTime = Info->m_PlayTime / Sequence->GetFrameCount();
    

    if (m_mapAnimation.empty())
        m_CurrentAnimation = Info;

    m_mapAnimation.insert(std::make_pair(SequenceName, Info));
    



}

void CAnimation::SetPlayTime(const std::string& Name, float PlayTime)
{
    CAnimationInfo* Info = FindInfo(Name);

    if (!Info)
        return;

    Info->m_PlayTime = PlayTime;
}

void CAnimation::SetPlayScale(const std::string& Name, float PlayScale)
{
    CAnimationInfo* Info = FindInfo(Name);

    if (!Info)
        return;

    Info->m_PlayScale = PlayScale;
}

void CAnimation::SetPlayLoop(const std::string& Name, bool Loop)
{
    CAnimationInfo* Info = FindInfo(Name);

    if (!Info)
        return;

    Info->m_Loop = Loop;
}

void CAnimation::SetPlayReverse(const std::string& Name, float Reverse)
{
    CAnimationInfo* Info = FindInfo(Name);

    if (!Info)
        return;

    Info->m_Reverse = Reverse;
}

void CAnimation::SetCurrentAnimation(std::string& Name)
{
    CAnimationInfo* Info = FindInfo(Name);

    if (!Info)
        return;


    m_CurrentAnimation = Info;

    m_CurrentAnimation->m_Frame = 0;
    m_CurrentAnimation->m_Time = 0.f;

    size_t Size = m_CurrentAnimation->m_vecNotify.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_CurrentAnimation->m_vecNotify[i]->Call = false;
    }
}

void CAnimation::ChangeAnimation(const std::string& Name)
{
    if (m_CurrentAnimation->m_Sequence->GetName() == Name)
        return;

    CAnimationInfo* Info = FindInfo(Name);

    if (!Info)
        return;


    m_CurrentAnimation->m_Frame = 0;
    m_CurrentAnimation->m_Time = 0.f;

    size_t Size = m_CurrentAnimation->m_vecNotify.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_CurrentAnimation->m_vecNotify[i]->Call = false;
    }


    m_CurrentAnimation = Info;

    m_CurrentAnimation->m_Frame = 0;
    m_CurrentAnimation->m_Time = 0.f;

     Size = m_CurrentAnimation->m_vecNotify.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_CurrentAnimation->m_vecNotify[i]->Call = false;
    }


}

bool CAnimation::CheckCurrentAnimation(const std::string& Name)
{
    return m_CurrentAnimation->m_Sequence->GetName() == Name;
}

void CAnimation::Update(float DeltaTime)
{
    m_CurrentAnimation->m_Time += DeltaTime * m_CurrentAnimation->m_PlayScale;

    bool AnimationEnd = false;

    if (m_CurrentAnimation->m_Time >= m_CurrentAnimation->m_FrameTime)
    {
        m_CurrentAnimation->m_Time -= m_CurrentAnimation->m_FrameTime;

        if (m_CurrentAnimation->m_Reverse)
        {
            --m_CurrentAnimation->m_Frame;

            if (m_CurrentAnimation->m_Frame < 0)
                AnimationEnd = true;
        }
        else
        {
            ++m_CurrentAnimation->m_Frame;

            if (m_CurrentAnimation->m_Frame == m_CurrentAnimation->m_Sequence->GetFrameCount())
                AnimationEnd = true;
        }
    }

    size_t Size = m_CurrentAnimation->m_vecNotify.size();

    for (size_t i = 0; i < Size; ++i)
    {
        if (!m_CurrentAnimation->m_vecNotify[i]->Call &&
            m_CurrentAnimation->m_vecNotify[i]->Frame == m_CurrentAnimation->m_Frame)
        {
            m_CurrentAnimation->m_vecNotify[i]->Call = true;
            m_CurrentAnimation->m_vecNotify[i]->Function();
        }
    }

    if (AnimationEnd)
    {

        if (m_currentAnimationEndFunc)
            m_currentAnimationEndFunc();

        if (m_CurrentAnimation->m_Loop)
        {
            if (m_CurrentAnimation->m_Reverse)
            {
                m_CurrentAnimation->m_Frame = m_CurrentAnimation->m_Sequence->GetFrameCount() - 1;
            }

            else
                m_CurrentAnimation->m_Frame = 0;
        }

        else
        {
            if (m_CurrentAnimation->m_Reverse)
            {
                m_CurrentAnimation->m_Frame = 0;
            }

            else
                m_CurrentAnimation->m_Frame = m_CurrentAnimation->m_Sequence->GetFrameCount() - 1;
        }

        if (m_CurrentAnimation->m_EndFunction)
            m_CurrentAnimation->m_EndFunction();

        for (size_t i = 0; i < Size; ++i)
        {
            m_CurrentAnimation->m_vecNotify[i]->Call = false;
        }

    }
}

CAnimationInfo* CAnimation::FindInfo(const std::string& Name)
{
    auto iter = m_mapAnimation.find(Name);

    if (iter == m_mapAnimation.end())
        return nullptr;


    return iter->second;
}
