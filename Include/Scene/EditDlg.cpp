
#include "EditDlg.h"
#include "../GameManager.h"
#include "../resource.h"
#include "EditScene.h"
#include "../PathManager.h"
#include "SceneResource.h"
#include "../Resource/Texture/Texture.h"
#include "../GameObject/TileMap.h"

CEditDlg* g_Dlg = nullptr;

CEditDlg::CEditDlg() :
	m_SelectTextureName{}
{
	g_Dlg = this;
	m_SelectTextureIndex = -1;
	m_SelectTextureFrameIndex = -1;
	m_BrushType = ETile_Brush::Frame;
	m_SelectOption = ETile_Option::Normal;
}

CEditDlg::~CEditDlg()
{
}

bool CEditDlg::Init()
{
	CGameManager::GetInst()->SetEditMode(true);

	// Modal : 부모윈도우는 멈추고 열리는 다이얼로그만 동작.
	// Modeless : 부모윈도우와 다이얼로그 모두 동작.
	m_hDlg = CreateDialog(CGameManager::GetInst()->GetWindowInstance(),
		MAKEINTRESOURCE(IDD_DIALOG_EDIT), CGameManager::GetInst()->GetWindowHandle(),
		CEditDlg::WndProc);

	ShowWindow(m_hDlg, SW_SHOW);

	SetDlgItemInt(m_hDlg, IDC_EDIT_COUNTX, 40, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_COUNTY, 40, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_SIZEX, 40, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_SIZEY, 53, TRUE);

	m_hTextureListBox = GetDlgItem(m_hDlg, IDC_LIST_TEXTURE);
	m_hTextureFrameListBox = GetDlgItem(m_hDlg, IDC_LIST_TEXTURE_FRAME);
	m_hBrushTypeCombo = GetDlgItem(m_hDlg, IDC_COMBO_BRUSH_TYPE);
	m_hOptionCombo = GetDlgItem(m_hDlg, IDC_COMBO_OPTION);
	m_hRenderCheckBox = GetDlgItem(m_hDlg, IDC_CHECK_RENDER);
	m_hSideCollisionCheckBox = GetDlgItem(m_hDlg, IDC_CHECK_SIDECOLLISION);

	SendMessage(m_hBrushTypeCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Frame"));
	SendMessage(m_hBrushTypeCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Option"));

	SendMessage(m_hOptionCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Normal"));
	SendMessage(m_hOptionCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("ImpossibleToMove"));

	SendMessage(m_hBrushTypeCombo, CB_SETCURSEL, 0, 0);

	SendMessage(m_hOptionCombo, CB_SETCURSEL, 0, 0);

	SendMessage(m_hRenderCheckBox, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

	return true;
}

void CEditDlg::CreateTileMap()
{
	BOOL	Transfer = FALSE;

	int	CountX = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNTX, &Transfer, TRUE);
	int	CountY = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNTY, &Transfer, TRUE);
	int	SizeX = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZEX, &Transfer, TRUE);
	int	SizeY = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZEY, &Transfer, TRUE);

	m_Scene->CreateTileMap(CountX, CountY, SizeX, SizeY);
}

void CEditDlg::LoadTexture()
{
	TCHAR	FilePath[MAX_PATH] = {};

	OPENFILENAME	OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = m_hDlg;
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0BmpFile\0*.bmp");
	OpenFile.lpstrFile = FilePath;	// FilePath 에 풀경로가 들어온다.
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		TCHAR	FileName[128] = {};

		_wsplitpath_s(FilePath, nullptr, 0, nullptr, 0, FileName, 128, nullptr, 0);

		char	TextureName[128] = {};

#ifdef UNICODE

		// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 수를
		// 얻어온다.
		int	PathLength = WideCharToMultiByte(CP_ACP, 0, FileName, -1,
			0, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, FileName, -1,
			TextureName, PathLength, 0, 0);

#else

		strcpy_s(TextureName, FileName);

#endif // UNICODE

		// ListBox에 Texture 이름을 추가한다.
		SendMessage(m_hTextureListBox, LB_ADDSTRING, 0, (LPARAM)FileName);

		if (!m_Scene->GetSceneResource()->LoadTextureFullPath(TextureName, FilePath))
			return;

		m_Scene->GetSceneResource()->SetColorKey(TextureName, 255, 0, 255);

		// 이 Texture에 대한 프레임 vector를 추가한다.
		std::vector<AnimationFrameData>	vecData;
		m_vecTextureFrame.push_back(vecData);
	}
}

void CEditDlg::SelectTexture()
{
	// 리스트박스에서 현재 선택된 셀의 인덱스를 얻어오도록 한다.
	m_SelectTextureIndex = (int)SendMessage(m_hTextureListBox, LB_GETCURSEL, 0, 0);

	if (m_SelectTextureIndex != -1)
	{
		memset(m_SelectTextureName, 0, sizeof(TCHAR) * 128);
		SendMessage(m_hTextureListBox, LB_GETTEXT, m_SelectTextureIndex, (LPARAM)m_SelectTextureName);

		char	TextureName[128] = {};

#ifdef UNICODE

		// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 수를
		// 얻어온다.
		int	PathLength = WideCharToMultiByte(CP_ACP, 0, m_SelectTextureName, -1,
			0, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, m_SelectTextureName, -1,
			TextureName, PathLength, 0, 0);

#else

		strcpy_s(TextureName, FileName);

#endif // UNICODE

		m_SelectTexture = m_Scene->GetSceneResource()->FindTexture(TextureName);

		m_Scene->SetTileTexture(m_SelectTexture);

		m_SelectTextureFrameIndex = -1;
	}
}

void CEditDlg::AddFrame()
{
	// 선택된 텍스쳐가 없으면 무시한다.
	if (m_SelectTextureIndex == -1)
		return;

	BOOL	Transfer = FALSE;

	int	StartX = GetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEX, &Transfer, TRUE);
	int	StartY = GetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEY, &Transfer, TRUE);
	int	EndX = GetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEX, &Transfer, TRUE);
	int	EndY = GetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEY, &Transfer, TRUE);

	AnimationFrameData	Data;
	Data.Start.x = (float)StartX;
	Data.Start.y = (float)StartY;
	Data.End.x = (float)EndX;
	Data.End.y = (float)EndY;

	TCHAR	ListData[32] = {};

	wsprintf(ListData, TEXT("%d"), (int)m_vecTextureFrame[m_SelectTextureIndex].size());

	SendMessage(m_hTextureFrameListBox, LB_ADDSTRING, 0, (LPARAM)ListData);

	m_vecTextureFrame[m_SelectTextureIndex].push_back(Data);
}

void CEditDlg::SelectFrame()
{
	if (m_SelectTextureIndex == -1)
		return;

	// 리스트박스에서 현재 선택된 셀의 인덱스를 얻어오도록 한다.
	m_SelectTextureFrameIndex = (int)SendMessage(m_hTextureFrameListBox, LB_GETCURSEL, 0, 0);

	if (m_SelectTextureFrameIndex != -1)
	{
		AnimationFrameData	Data = m_vecTextureFrame[m_SelectTextureIndex][m_SelectTextureFrameIndex];

		SetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEX, (int)Data.Start.x, TRUE);
		SetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEY, (int)Data.Start.y, TRUE);
		SetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEX, (int)Data.End.x, TRUE);
		SetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEY, (int)Data.End.y, TRUE);
	}
}

void CEditDlg::SelectBrushType()
{
	m_BrushType = (ETile_Brush)SendMessage(m_hBrushTypeCombo, CB_GETCURSEL, 0, 0);
}

void CEditDlg::SelectOption()
{
	m_SelectOption = (ETile_Option)SendMessage(m_hOptionCombo, CB_GETCURSEL, 0, 0);
}

void CEditDlg::Save()
{
	if (!m_Scene->GetTileMap())
		return;

	TCHAR	FilePath[MAX_PATH] = {};

	OPENFILENAME	OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = m_hDlg;
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0TileMapFile\0*.tmp");
	OpenFile.lpstrFile = FilePath;	// FilePath 에 풀경로가 들어온다.
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		char	FullPath[MAX_PATH] = {};

#ifdef UNICODE

		// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 수를
		// 얻어온다.
		int	PathLength = WideCharToMultiByte(CP_ACP, 0, FilePath, -1,
			0, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, FilePath, -1,
			FullPath, PathLength, 0, 0);

#else

		strcpy_s(FullPath, FilePath);

#endif // UNICODE

		m_Scene->GetTileMap()->SaveFullPath(FullPath);
	}
}

void CEditDlg::Load()
{
	TCHAR	FilePath[MAX_PATH] = {};

	OPENFILENAME	OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = m_hDlg;
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0TileMapFile\0*.tmp");
	OpenFile.lpstrFile = FilePath;	// FilePath 에 풀경로가 들어온다.
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		char	FullPath[MAX_PATH] = {};

#ifdef UNICODE

		// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 수를
		// 얻어온다.
		int	PathLength = WideCharToMultiByte(CP_ACP, 0, FilePath, -1,
			0, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, FilePath, -1,
			FullPath, PathLength, 0, 0);

#else

		strcpy_s(FullPath, FilePath);

#endif // UNICODE

		m_Scene->LoadTileMap(FullPath);
	}
}

void CEditDlg::LoadTextureBack()
{
	if (!m_Scene->GetTileMap())
		return;

	TCHAR	FilePath[MAX_PATH] = {};

	OPENFILENAME	OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = m_hDlg;
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0BmpFile\0*.bmp");
	OpenFile.lpstrFile = FilePath;	// FilePath 에 풀경로가 들어온다.
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		TCHAR	FileName[128] = {};

		_wsplitpath_s(FilePath, nullptr, 0, nullptr, 0, FileName, 128, nullptr, 0);

		char	TextureName[128] = {};

#ifdef UNICODE

		// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 수를
		// 얻어온다.
		int	PathLength = WideCharToMultiByte(CP_ACP, 0, FileName, -1,
			0, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, FileName, -1,
			TextureName, PathLength, 0, 0);

#else

		strcpy_s(TextureName, FileName);

#endif // UNICODE

		m_Scene->GetTileMap()->SetTextureFullPath(TextureName, FilePath);
		m_Scene->GetTileMap()->SetColorKey(255, 0, 255);
	}
}

LRESULT CEditDlg::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_CREATE_TILEMAP:
			g_Dlg->CreateTileMap();
			break;
		case IDC_BUTTON_LOADTEXTURE:
			g_Dlg->LoadTexture();
			break;
		case IDC_BUTTON_ADD_FRAME:
			g_Dlg->AddFrame();
			break;
		case IDC_BUTTON_LOADTEXTURE_BACK:
			g_Dlg->LoadTextureBack();
			break;
		case IDC_LIST_TEXTURE:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				g_Dlg->SelectTexture();
				break;
			}
			break;
		case IDC_LIST_TEXTURE_FRAME:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				g_Dlg->SelectFrame();
				break;
			}
			break;
		case IDC_COMBO_BRUSH_TYPE:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				g_Dlg->SelectBrushType();
				break;
			}
			break;
		case IDC_COMBO_OPTION:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				g_Dlg->SelectOption();
				break;
			}
			break;
		case IDC_BUTTON_SAVE:
			g_Dlg->Save();
			break;
		case IDC_BUTTON_LOAD:
			g_Dlg->Load();
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}
