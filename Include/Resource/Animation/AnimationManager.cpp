
#include "AnimationManager.h"
#include "AnimationSequence.h"
#include "../Texture/Texture.h"

CAnimationManager::CAnimationManager()
{
}

CAnimationManager::~CAnimationManager()
{
}

bool CAnimationManager::Init()
{
	return true;
}

bool CAnimationManager::CreateAnimationSequence(const std::string& Name,
	CTexture* Texture)
{
	CAnimationSequence* Sequence = FindAnimation(Name);

	if (Sequence)
		return false;

	Sequence = new CAnimationSequence;

	Sequence->SetName(Name);
	Sequence->m_Texture = Texture;

	m_mapSequence.insert(std::make_pair(Name, Sequence));

	return true;
}

bool CAnimationManager::AddAnimationFrame(const std::string& Name,
	const Vector2& Start, const Vector2& End)
{
	CAnimationSequence* Sequence = FindAnimation(Name);

	if (!Sequence)
		return false;

	Sequence->AddFrame(Start, End);

	return true;
}

bool CAnimationManager::AddAnimationFrame(const std::string& Name,
	float PosX, float PosY, float SizeX, float SizeY)
{
	CAnimationSequence* Sequence = FindAnimation(Name);

	if (!Sequence)
		return false;

	Sequence->AddFrame(PosX, PosY, SizeX, SizeY);

	return true;
}

CAnimationSequence* CAnimationManager::FindAnimation(const std::string& Name)
{
	auto	iter = m_mapSequence.find(Name);

	if (iter == m_mapSequence.end())
		return nullptr;

	return iter->second;
}

void CAnimationManager::ReleaseAnimation(const std::string& Name)
{
	auto	iter = m_mapSequence.find(Name);

	if (iter == m_mapSequence.end())
		return;

	if (iter->second->GetRefCount() == 1)
		m_mapSequence.erase(iter);
}
