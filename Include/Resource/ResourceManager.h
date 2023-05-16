#pragma once

#include "../SingletonMacro.h"
#include "../GameInfo.h"

class CResourceManager
{
private:
	class CTextureManager* m_TextureManager;
	class CAnimationManager* m_AnimationManager;
	class CSoundManager* m_SoundManager;
	class CFontManager* m_FontManager;

public:
	bool Init();
	void Update();

public:	// ==================== Texture ====================
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE

	bool LoadTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

	bool LoadTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif // UNICODE

	class CTexture* LoadTexture(FILE* File);

	bool SetColorKey(const std::string& Name, unsigned char r, unsigned char g, unsigned char b,
		int Index = 0);
	bool SetColorKeyAll(const std::string& Name, unsigned char r, unsigned char g, unsigned char b);

	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(const std::string& Name);



public:	// ==================== Animation Sequence ====================
	bool CreateAnimationSequence(const std::string& Name, class CTexture* Texture);
	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName);
	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const TCHAR* FileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const TCHAR* FullPath);

#ifdef UNICODE

	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const std::vector<std::wstring>& vecFileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const std::vector<std::wstring>& vecFullPath);

#else

	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const std::vector<std::string>& vecFileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const std::vector<std::string>& vecFullPath);

#endif // UNICODE


	bool AddAnimationFrame(const std::string& Name, const Vector2& Start,
		const Vector2& End);
	bool AddAnimationFrame(const std::string& Name,
		float PosX, float PosY, float SizeX, float SizeY);

	class CAnimationSequence* FindAnimation(const std::string& Name);
	void ReleaseAnimation(const std::string& Name);



public:	// ============================ Sound ================================
	bool CreateSoundChannel(const std::string& Name);
	bool LoadSound(const std::string& GroupName, const std::string& Name,
		bool Loop, const char* FileName, const std::string& PathName = SOUND_PATH);
	bool SetVolume(int Volume);
	bool SetVolume(const std::string& GroupName, int Volume);
	bool SoundPlay(const std::string& Name);
	bool SoundStop(const std::string& Name);
	bool SoundPause(const std::string& Name);
	bool SoundResume(const std::string& Name);


	FMOD::ChannelGroup* FindChannelGroup(const std::string& Name);
	class CSound* FindSound(const std::string& Name);
	void ReleaseSound(const std::string& Name);

public: // ================================== Font =================================
	bool LoadFont(const std::string& Name, const TCHAR* FontName,
		int Width, int Height);
	bool LoadFont(const TCHAR* FontFileName, const std::string& PathName = FONT_PATH);
	void SetFont(const std::string& Name, HDC hDC);
	void ResetFont(const std::string& Name, HDC hDC);
	class CFont* FindFont(const std::string& Name);
	void ReleaseFont(const std::string& Name);


	DECLARE_SINGLE(CResourceManager)
};

