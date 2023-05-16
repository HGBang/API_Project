#pragma once

#include "../../Ref.h"
#include "../Texture/Texture.h"

class CAnimationSequence :
    public CRef
{
    friend class CAnimationManager;
    friend class CAnimationInfo;

private:
    CAnimationSequence();
    ~CAnimationSequence();

private:
    CSharedPtr<CTexture>  m_Texture;
    std::vector<AnimationFrameData> m_vecFrame;

public:
    CTexture* GetTexture()    const
    {
        return m_Texture;
    }

    ETexture_Type GetTextureType()  const
    {
        return m_Texture->GetTextureType();
    }

    const AnimationFrameData& GetFrame(int Index)   const
    {
        return m_vecFrame[Index];
    }

    int GetFrameCount() const
    {
        return (int)m_vecFrame.size();
    }

public:
    void AddFrame(const Vector2& Start, const Vector2& End);
    void AddFrame(float PosX, float PosY, float SizeX, float SizeY);
};

