
#include "Texture.h"
#include "../../PathManager.h"
#include "../../GameManager.h"

CTexture::CTexture() :
	m_Type(ETexture_Type::Sprite)
{
	SetTypeID<CTexture>();
}

CTexture::~CTexture()
{
	size_t	Size = m_vecImageInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecImageInfo[i]);
	}
}

bool CTexture::LoadTexture(const TCHAR* FileName,
	const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	TCHAR	FullPath[MAX_PATH] = {};

	if (Path)
		lstrcpy(FullPath, Path->Path);

	lstrcat(FullPath, FileName);

	bool Result = LoadTextureFullPath(FullPath);

	if (Result)
	{
		lstrcpy(m_vecImageInfo.back()->FileName, FileName);
		m_vecImageInfo.back()->PathName = PathName;
	}

	return Result;
}

bool CTexture::LoadTextureFullPath(const TCHAR* FullPath)
{
	// 화면DC를 넣고 메모리 DC를 얻는다.
	HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// 비트맵을 로딩한다.
	HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		FullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!hBmp)
		return false;

	// 읽어온 비트맵을 메모리 DC에 지정한다.
	// 기존에 DC가 가지고 있던 도구를 반환한다.
	HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

	BITMAP	BmpInfo;

	GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

	ImageInfo* Info = new ImageInfo;

	Info->hMemDC = hDC;
	Info->hBmp = hBmp;
	Info->hPrevBmp = hPrevBmp;
	Info->BmpInfo = BmpInfo;
	lstrcpy(Info->FullPath, FullPath);

	m_vecImageInfo.push_back(Info);

	return true;
}

#ifdef UNICODE

bool CTexture::LoadTexture(const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	m_Type = ETexture_Type::Frame;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	std::vector<std::wstring>	vecFullPath;

	size_t	Size = vecFileName.size();

	// 미리 개수만큼 push 해놓는 효과이다.
	vecFullPath.resize(Size);

	// 미리 배열 공간을 확보하여 꽉 찼을때 공간 재할당이 일어나는것을 방지해주는
	// 역할을 할때 사용한다.
	//vecFullPath.reserve(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		if (Path)
			vecFullPath[i] = Path->Path;

		vecFullPath[i] += vecFileName[i];
	}

	bool Result = LoadTextureFullPath(vecFullPath);

	if (Result)
	{
		for (size_t i = 0; i < Size; ++i)
		{
			lstrcpy(m_vecImageInfo[i]->FileName, vecFileName[i].c_str());
			m_vecImageInfo[i]->PathName = PathName;
		}
	}

	return Result;
}

bool CTexture::LoadTextureFullPath(const std::vector<std::wstring>& vecFullPath)
{
	m_Type = ETexture_Type::Frame;

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 화면DC를 넣고 메모리 DC를 얻는다.
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// 비트맵을 로딩한다.
		// string 이나 wstring 클래스의 c_str() 함수는 문자열 포인터를 얻어온다.
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		// 읽어온 비트맵을 메모리 DC에 지정한다.
		// 기존에 DC가 가지고 있던 도구를 반환한다.
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP	BmpInfo;

		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		ImageInfo* Info = new ImageInfo;

		Info->hMemDC = hDC;
		Info->hBmp = hBmp;
		Info->hPrevBmp = hPrevBmp;
		Info->BmpInfo = BmpInfo;
		lstrcpy(Info->FullPath, vecFullPath[i].c_str());

		m_vecImageInfo.push_back(Info);
	}

	return true;
}

#else

bool CTexture::LoadTexture(const std::vector<std::string>& vecFileName,
	const std::string& PathName)
{
	m_Type = ETexture_Type::Frame;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	std::vector<std::string>	vecFullPath;

	size_t	Size = vecFileName.size();

	// 미리 개수만큼 push 해놓는 효과이다.
	vecFullPath.resize(Size);

	// 미리 배열 공간을 확보하여 꽉 찼을때 공간 재할당이 일어나는것을 방지해주는
	// 역할을 할때 사용한다.
	//vecFullPath.reserve(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		if (Path)
			vecFullPath[i] = Path->Path;

		vecFullPath[i] += vecFileName[i];
	}

	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::string>& vecFullPath)
{
	m_Type = ETexture_Type::Frame;

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 화면DC를 넣고 메모리 DC를 얻는다.
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// 비트맵을 로딩한다.
		// string 이나 wstring 클래스의 c_str() 함수는 문자열 포인터를 얻어온다.
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		// 읽어온 비트맵을 메모리 DC에 지정한다.
		// 기존에 DC가 가지고 있던 도구를 반환한다.
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP	BmpInfo;

		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		ImageInfo* Info = new ImageInfo;

		Info->hMemDC = hDC;
		Info->hBmp = hBmp;
		Info->hPrevBmp = hPrevBmp;
		Info->BmpInfo = BmpInfo;

		m_vecImageInfo.push_back(Info);
	}

	return true;
}

#endif // UNICODE

bool CTexture::LoadTexture(ImageInfo* Info, const TCHAR* FileName,
	const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	TCHAR	FullPath[MAX_PATH] = {};

	if (Path)
		lstrcpy(FullPath, Path->Path);

	lstrcat(FullPath, FileName);

	bool Result = LoadTextureFullPath(Info, FullPath);

	if (Result)
	{
		lstrcpy(m_vecImageInfo.back()->FileName, FileName);
		m_vecImageInfo.back()->PathName = PathName;
	}

	return Result;
}

bool CTexture::LoadTextureFullPath(ImageInfo* Info, const TCHAR* FullPath)
{
	// 화면DC를 넣고 메모리 DC를 얻는다.
	HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// 비트맵을 로딩한다.
	HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		FullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!hBmp)
		return false;

	// 읽어온 비트맵을 메모리 DC에 지정한다.
	// 기존에 DC가 가지고 있던 도구를 반환한다.
	HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

	BITMAP	BmpInfo;

	GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

	Info->hMemDC = hDC;
	Info->hBmp = hBmp;
	Info->hPrevBmp = hPrevBmp;
	Info->BmpInfo = BmpInfo;
	lstrcpy(Info->FullPath, FullPath);

	return true;
}

#ifdef UNICODE

bool CTexture::LoadTexture(std::vector<ImageInfo*>* vecInfo, const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	m_Type = ETexture_Type::Frame;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	std::vector<std::wstring>	vecFullPath;

	size_t	Size = vecFileName.size();

	// 미리 개수만큼 push 해놓는 효과이다.
	vecFullPath.resize(Size);

	// 미리 배열 공간을 확보하여 꽉 찼을때 공간 재할당이 일어나는것을 방지해주는
	// 역할을 할때 사용한다.
	//vecFullPath.reserve(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		if (Path)
			vecFullPath[i] = Path->Path;

		vecFullPath[i] += vecFileName[i];
	}

	bool Result = LoadTextureFullPath(vecInfo, vecFullPath);

	if (Result)
	{
		for (size_t i = 0; i < Size; ++i)
		{
			lstrcpy(m_vecImageInfo[i]->FileName, vecFileName[i].c_str());
			m_vecImageInfo[i]->PathName = PathName;
		}
	}

	return Result;
}

bool CTexture::LoadTextureFullPath(std::vector<ImageInfo*>* vecInfo, const std::vector<std::wstring>& vecFullPath)
{
	m_Type = ETexture_Type::Frame;

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 화면DC를 넣고 메모리 DC를 얻는다.
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// 비트맵을 로딩한다.
		// string 이나 wstring 클래스의 c_str() 함수는 문자열 포인터를 얻어온다.
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		// 읽어온 비트맵을 메모리 DC에 지정한다.
		// 기존에 DC가 가지고 있던 도구를 반환한다.
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP	BmpInfo;

		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		ImageInfo* Info = *(vecInfo->begin() + i);

		Info->hMemDC = hDC;
		Info->hBmp = hBmp;
		Info->hPrevBmp = hPrevBmp;
		Info->BmpInfo = BmpInfo;
		lstrcpy(Info->FullPath, vecFullPath[i].c_str());
	}

	return true;
}

#else

bool CTexture::LoadTexture(std::vector<ImageInfo*>* vecInfo, const std::vector<std::string>& vecFileName,
	const std::string& PathName)
{
	m_Type = ETexture_Type::Frame;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	std::vector<std::string>	vecFullPath;

	size_t	Size = vecFileName.size();

	// 미리 개수만큼 push 해놓는 효과이다.
	vecFullPath.resize(Size);

	// 미리 배열 공간을 확보하여 꽉 찼을때 공간 재할당이 일어나는것을 방지해주는
	// 역할을 할때 사용한다.
	//vecFullPath.reserve(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		if (Path)
			vecFullPath[i] = Path->Path;

		vecFullPath[i] += vecFileName[i];
	}

	return LoadTextureFullPath(vecInfo, vecFullPath);
}

bool CTexture::LoadTextureFullPath(std::vector<ImageInfo*>* vecInfo, const std::vector<std::string>& vecFullPath)
{
	m_Type = ETexture_Type::Frame;

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 화면DC를 넣고 메모리 DC를 얻는다.
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// 비트맵을 로딩한다.
		// string 이나 wstring 클래스의 c_str() 함수는 문자열 포인터를 얻어온다.
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		// 읽어온 비트맵을 메모리 DC에 지정한다.
		// 기존에 DC가 가지고 있던 도구를 반환한다.
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP	BmpInfo;

		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		ImageInfo* Info = *(vecInfo->begin() + i);

		Info->hMemDC = hDC;
		Info->hBmp = hBmp;
		Info->hPrevBmp = hPrevBmp;
		Info->BmpInfo = BmpInfo;
	}

	return true;
}

#endif // UNICODE

void CTexture::Save(FILE* File)
{
	CRef::Save(File);

	fwrite(&m_Type, sizeof(ETexture_Type), 1, File);

	int	Count = (int)m_vecImageInfo.size();

	fwrite(&Count, sizeof(int), 1, File);

	for (int i = 0; i < Count; ++i)
	{
		fwrite(&m_vecImageInfo[i]->EnableColorKey, sizeof(bool), 1, File);
		fwrite(&m_vecImageInfo[i]->ColorKey, sizeof(COLORREF), 1, File);

		fwrite(&m_vecImageInfo[i]->FileName, sizeof(TCHAR), MAX_PATH, File);
		fwrite(&m_vecImageInfo[i]->FullPath, sizeof(TCHAR), MAX_PATH, File);

		int Length = (int)m_vecImageInfo[i]->PathName.length();
		fwrite(&Length, sizeof(int), 1, File);
		fwrite(m_vecImageInfo[i]->PathName.c_str(), sizeof(char), Length, File);
	}
}

void CTexture::Load(FILE* File)
{
	CRef::Load(File);

	fread(&m_Type, sizeof(ETexture_Type), 1, File);

	int	Count = 0;

	fread(&Count, sizeof(int), 1, File);

	for (int i = 0; i < Count; ++i)
	{
		ImageInfo* Info = new ImageInfo;

		m_vecImageInfo.push_back(Info);

		fread(&Info->EnableColorKey, sizeof(bool), 1, File);
		fread(&Info->ColorKey, sizeof(COLORREF), 1, File);

		fread(&Info->FileName, sizeof(TCHAR), MAX_PATH, File);
		fread(&Info->FullPath, sizeof(TCHAR), MAX_PATH, File);

		int Length = 0;
		fread(&Length, sizeof(int), 1, File);
		char	PathName[256] = {};
		fread(PathName, sizeof(char), Length, File);
		Info->PathName = PathName;
	}

	if (m_vecImageInfo.size() == 1)
	{
		if (lstrlen(m_vecImageInfo[0]->FileName) > 0)
			LoadTexture(m_vecImageInfo[0], m_vecImageInfo[0]->FileName, m_vecImageInfo[0]->PathName);

		else
			LoadTextureFullPath(m_vecImageInfo[0], m_vecImageInfo[0]->FullPath);
	}

	else
	{
		if (lstrlen(m_vecImageInfo[0]->FileName) > 0)
		{
			std::vector<std::wstring>	vecFileName;

			size_t	Size = m_vecImageInfo.size();

			for (size_t i = 0; i < Size; ++i)
			{
				vecFileName.push_back(m_vecImageInfo[i]->FileName);
			}
			LoadTexture(&m_vecImageInfo, vecFileName, m_vecImageInfo[0]->PathName);
		}

		else
		{
			std::vector<std::wstring>	vecFileName;

			size_t	Size = m_vecImageInfo.size();

			for (size_t i = 0; i < Size; ++i)
			{
				vecFileName.push_back(m_vecImageInfo[i]->FullPath);
			}
			LoadTextureFullPath(&m_vecImageInfo, vecFileName);
		}
	}
}
