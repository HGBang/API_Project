#pragma once

#include "../../GameInfo.h"

class CFontManager
{
	friend class CResourceManager;

private:
	CFontManager();
	~CFontManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CFont>>	m_mapFont;

public:
	bool Init();
	bool LoadFont(const std::string& Name, const TCHAR* FontName,
		int Width, int Height);
	bool LoadFont(const TCHAR* FontFileName, const std::string& PathName = FONT_PATH);
	void SetFont(const std::string& Name, HDC hDC);
	void ResetFont(const std::string& Name, HDC hDC);
	class CFont* FindFont(const std::string& Name);
	void ReleaseFont(const std::string& Name);
};

