
#include "SceneResource.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../Resource/Sound/Sound.h"
#include "../Resource/Font/Font.h"

CSceneResource::CSceneResource()
{
}

CSceneResource::~CSceneResource()
{
	{
		auto	iter = m_mapTexture.begin();
		auto	iterEnd = m_mapTexture.end();

		for (; iter != iterEnd;)
		{
			std::string	Key = iter->first;

			iter = m_mapTexture.erase(iter);
			iterEnd = m_mapTexture.end();

			CResourceManager::GetInst()->ReleaseTexture(Key);
		}
	}

	{
		auto	iter = m_mapAnimationSequence.begin();
		auto	iterEnd = m_mapAnimationSequence.end();

		for (; iter != iterEnd;)
		{
			std::string	Key = iter->first;

			iter = m_mapAnimationSequence.erase(iter);
			iterEnd = m_mapAnimationSequence.end();

			CResourceManager::GetInst()->ReleaseAnimation(Key);
		}
	}

	{
		auto	iter = m_mapSound.begin();
		auto	iterEnd = m_mapSound.end();

		for (; iter != iterEnd;)
		{
			std::string	Key = iter->first;

			iter = m_mapSound.erase(iter);
			iterEnd = m_mapSound.end();

			CResourceManager::GetInst()->ReleaseSound(Key);
		}
	}

	{
		auto	iter = m_mapFont.begin();
		auto	iterEnd = m_mapFont.end();

		for (; iter != iterEnd;)
		{
			std::string	Key = iter->first;

			iter = m_mapFont.erase(iter);
			iterEnd = m_mapFont.end();

			CResourceManager::GetInst()->ReleaseFont(Key);
		}
	}
}

bool CSceneResource::LoadTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

#ifdef UNICODE

bool CSceneResource::LoadTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name,
	const std::vector<std::wstring>& vecFullPath)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

#else

bool CSceneResource::LoadTexture(const std::string& Name,
	const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name,
	const std::vector<std::string>& vecFullPath)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}


#endif

CTexture* CSceneResource::LoadTexture(FILE* File)
{
	CTexture* Texture = CResourceManager::GetInst()->LoadTexture(File);

	if (!Texture)
		return nullptr;

	if (!FindTexture(Texture->GetName()))
		m_mapTexture.insert(std::make_pair(Texture->GetName(), Texture));

	return Texture;;
}

bool CSceneResource::SetColorKey(const std::string& Name, unsigned char r, unsigned char g, unsigned char b, int Index)
{
	return CResourceManager::GetInst()->SetColorKey(Name, r, g, b, Index);
}

bool CSceneResource::SetColorKeyAll(const std::string& Name, unsigned char r, unsigned char g, unsigned char b)
{
	return CResourceManager::GetInst()->SetColorKeyAll(Name, r, g, b);
}

CTexture* CSceneResource::FindTexture(const std::string& Name)
{
	auto	iter = m_mapTexture.find(Name);

	if (iter == m_mapTexture.end())
	{
		CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

		if (!Texture)
			return nullptr;

		m_mapTexture.insert(std::make_pair(Name, Texture));

		return Texture;
	}

	return iter->second;
}

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	CTexture* Texture)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, Texture))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, TexName))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName, const TCHAR* FileName,
	const std::string& PathName)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, TexName,
		FileName, PathName))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& Name,
	const std::string& TexName, const TCHAR* FullPath)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(Name, TexName,
		FullPath))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

#ifdef UNICODE

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName, const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, TexName,
		vecFileName, PathName))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& Name,
	const std::string& TexName, const std::vector<std::wstring>& vecFullPath)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(Name, TexName,
		vecFullPath))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

#else

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, TexName,
		vecFileName, PathName))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& Name,
	const std::string& TexName, const std::vector<std::string>& vecFullPath)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(Name, TexName,
		vecFullPath))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

#endif

bool CSceneResource::AddAnimationFrame(const std::string& Name,
	const Vector2& Start, const Vector2& End)
{
	return CResourceManager::GetInst()->AddAnimationFrame(Name, Start, End);
}

bool CSceneResource::AddAnimationFrame(const std::string& Name, float PosX,
	float PosY, float SizeX, float SizeY)
{
	return CResourceManager::GetInst()->AddAnimationFrame(Name, PosX, PosY, SizeX, SizeY);
}

CAnimationSequence* CSceneResource::FindAnimation(const std::string& Name)
{
	auto	iter = m_mapAnimationSequence.find(Name);

	if (iter == m_mapAnimationSequence.end())
	{
		CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

		if (!Animation)
			return nullptr;

		m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

		return Animation;
	}

	return iter->second;
}

bool CSceneResource::CreateSoundChannel(const std::string& Name)
{
	return CResourceManager::GetInst()->CreateSoundChannel(Name);
}

bool CSceneResource::LoadSound(const std::string& GroupName, const std::string& Name, bool Loop, const char* FileName, const std::string& PathName)
{
	if (FindSound(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadSound(GroupName, Name, Loop, FileName, PathName))
		return false;

	CSound* Sound = CResourceManager::GetInst()->FindSound(Name);

	m_mapSound.insert(std::make_pair(Name, Sound));

	return true;
}

bool CSceneResource::SetVolume(int Volume)
{
	return CResourceManager::GetInst()->SetVolume(Volume);
}

bool CSceneResource::SetVolume(const std::string& GroupName, int Volume)
{
	return CResourceManager::GetInst()->SetVolume(GroupName, Volume);
}

bool CSceneResource::SoundPlay(const std::string& Name)
{
	return CResourceManager::GetInst()->SoundPlay(Name);
}

bool CSceneResource::SoundStop(const std::string& Name)
{
	return CResourceManager::GetInst()->SoundStop(Name);
}

bool CSceneResource::SoundPause(const std::string& Name)
{
	return CResourceManager::GetInst()->SoundPause(Name);
}

bool CSceneResource::SoundResume(const std::string& Name)
{
	return CResourceManager::GetInst()->SoundResume(Name);
}

FMOD::ChannelGroup* CSceneResource::FindChannelGroup(const std::string& Name)
{
	return CResourceManager::GetInst()->FindChannelGroup(Name);
}

CSound* CSceneResource::FindSound(const std::string& Name)
{
	auto	iter = m_mapSound.find(Name);

	if (iter == m_mapSound.end())
	{
		CSound* Sound = CResourceManager::GetInst()->FindSound(Name);

		if (!Sound)
			return nullptr;

		m_mapSound.insert(std::make_pair(Name, Sound));

		return Sound;
	}

	return iter->second;
}

bool CSceneResource::LoadFont(const std::string& Name, const TCHAR* FontName,
	int Width, int Height)
{
	if (FindFont(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadFont(Name, FontName, Width, Height))
		return false;

	CFont* Font = CResourceManager::GetInst()->FindFont(Name);

	m_mapFont.insert(std::make_pair(Name, Font));

	return true;
}

bool CSceneResource::LoadFont(const TCHAR* FontFileName, const std::string& PathName)
{
	return CResourceManager::GetInst()->LoadFont(FontFileName, PathName);
}

void CSceneResource::SetFont(const std::string& Name, HDC hDC)
{
	return CResourceManager::GetInst()->SetFont(Name, hDC);
}

void CSceneResource::ResetFont(const std::string& Name, HDC hDC)
{
	return CResourceManager::GetInst()->ResetFont(Name, hDC);
}

CFont* CSceneResource::FindFont(const std::string& Name)
{
	auto	iter = m_mapFont.find(Name);

	if (iter == m_mapFont.end())
	{
		CFont* Font = CResourceManager::GetInst()->FindFont(Name);

		if (!Font)
			return nullptr;

		m_mapFont.insert(std::make_pair(Name, Font));

		return Font;
	}

	return iter->second;
}
