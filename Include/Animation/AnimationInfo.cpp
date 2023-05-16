
#include "AnimationInfo.h"
#include "../Resource/Animation/AnimationSequence.h"

CAnimationInfo::CAnimationInfo() :
	m_Frame(0),
	m_Time(0.f),
	m_FrameTime(0.f),
	m_PlayTime(1.f),
	m_PlayScale(1.f),
	m_Loop(false),
	m_Reverse(false)
{
}

CAnimationInfo::~CAnimationInfo()
{
	size_t Size = m_vecNotify.size();
	  
	for(size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecNotify[i]);
	}

}
