#pragma once
#include "Scene.h"
class CEditScene :
	public CScene
{
	friend class CSceneManager;

protected:
	CEditScene();
	virtual ~CEditScene();

private:
	class CEditDlg* m_TileMapDlg;

public:
	bool Init();

public:
	void CreateTileMap(int CountX, int CountY, int SizeX, int SizeY);
	void SetTileTexture(class CTexture* Texture);
	void LoadTileMap(const char* FullPath);

public:
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void OpenTileMapEditor();
	void MouseLButtonDrag();


private:
	void ChangeFrame();
	void ChangeOption();
};

