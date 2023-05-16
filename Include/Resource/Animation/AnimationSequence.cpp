
#include "AnimationSequence.h"

CAnimationSequence::CAnimationSequence()
{
}

CAnimationSequence::~CAnimationSequence()
{
}

void CAnimationSequence::AddFrame(const Vector2& Start, const Vector2& End)
{
	AnimationFrameData	Data = {};

	Data.Start = Start;
	Data.End = End;

	m_vecFrame.push_back(Data);
}

void CAnimationSequence::AddFrame(float PosX, float PosY, float SizeX, float SizeY)
{
	AnimationFrameData	Data = {};

	Data.Start = Vector2(PosX, PosY);
	Data.End = Vector2(PosX + SizeX, PosY + SizeY);

	m_vecFrame.push_back(Data);
}
