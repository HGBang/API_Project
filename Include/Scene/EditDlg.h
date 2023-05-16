#pragma once

#include "../GameInfo.h"

enum class ETile_Brush
{
	Frame,
	Option
};

class CEditDlg
{
	friend class CEditScene;

private:
	CEditDlg();
	~CEditDlg();

private:
	class CEditScene* m_Scene;
	HWND	m_hDlg;
	HWND	m_hTextureListBox;
	HWND	m_hTextureFrameListBox;
	HWND	m_hBrushTypeCombo;
	HWND	m_hOptionCombo;
	HWND	m_hRenderCheckBox;
	HWND	m_hSideCollisionCheckBox;
	int		m_SelectTextureIndex;
	TCHAR	m_SelectTextureName[128];
	CSharedPtr<class CTexture>	m_SelectTexture;
	std::vector<std::vector<AnimationFrameData>>	m_vecTextureFrame;
	int		m_SelectTextureFrameIndex;

	ETile_Brush			m_BrushType;
	ETile_Option		m_SelectOption;

public:
	bool GetCheckRender()	const
	{
		return SendMessage(m_hRenderCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED;
	}

	bool GetCheckSideCollision()	const
	{
		return SendMessage(m_hSideCollisionCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED;
	}

	ETile_Brush GetBrushType()	const
	{
		return m_BrushType;
	}

	ETile_Option GetSelectOption()	const
	{
		return m_SelectOption;
	}

	const AnimationFrameData* GetTileFrameData()	const
	{
		if (m_SelectTextureIndex == -1 || m_SelectTextureFrameIndex == -1)
			return nullptr;

		return &m_vecTextureFrame[m_SelectTextureIndex][m_SelectTextureFrameIndex];
	}

public:
	bool Init();
	void CreateTileMap();
	void LoadTexture();
	void SelectTexture();
	void AddFrame();
	void SelectFrame();
	void SelectBrushType();
	void SelectOption();
	void Save();
	void Load();
	void LoadTextureBack();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

