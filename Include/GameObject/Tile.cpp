
#include "Tile.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Scene/SceneManager.h"
#include "../GameManager.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CTile::CTile() :
	m_Option(ETile_Option::Normal),
	m_Scene(nullptr),
	m_Owner(nullptr),
	m_IndexX(0),
	m_IndexY(0),
	m_Index(0),
	m_TileFrame(0),
	m_Render(true),
	m_SideCollision(false)
{
}

CTile::~CTile()
{
}

void CTile::SetTileInfo(const Vector2& Pos, const Vector2& Size,
	int IndexX, int IndexY, int Index, CTexture* Texture)
{
	m_Texture = Texture;
	m_Pos = Pos;
	m_Size = Size;
	m_IndexX = IndexX;
	m_IndexY = IndexY;
	m_Index = Index;
}

void CTile::Render(HDC hDC)
{
	Vector2	Pos;
	Vector2	CameraPos;
	Vector2	Resolution;

	


	if (m_Scene)
	{
		CameraPos = m_Scene->GetCamera()->GetPos();
		Resolution = m_Scene->GetCamera()->GetResolution();
		Pos = m_Pos - m_Scene->GetCamera()->GetPos();
	}

	else
	{
		CScene* Scene = CSceneManager::GetInst()->GetScene();
		Pos = m_Pos - Scene->GetCamera()->GetPos();
		CameraPos = Scene->GetCamera()->GetPos();
		Resolution = Scene->GetCamera()->GetResolution();
	}

	if (m_Render)
	{
		if (m_Texture)
		{
			if (m_Texture->GetEnableColorKey())
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					TransparentBlt(hDC, (int)Pos.x, (int)Pos.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
						(int)m_StartFrame.x, (int)m_StartFrame.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetColorKey());
				}

				else
				{
					TransparentBlt(hDC, (int)Pos.x, (int)Pos.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(m_TileFrame),
						0, 0,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetColorKey(m_TileFrame));
				}
			}

			else
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					BitBlt(hDC, (int)Pos.x, (int)Pos.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
						(int)m_StartFrame.x, (int)m_StartFrame.y, SRCCOPY);
				}

				else
				{
					BitBlt(hDC, (int)Pos.x, (int)Pos.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(m_TileFrame),
						0, 0, SRCCOPY);
				}
			}
		}
	}

	// EditModeÀÏ °æ¿ì
	if (CGameManager::GetInst()->GetEditMode())
	{
		HBRUSH	Brush = 0;

		switch (m_Option)
		{
		case ETile_Option::Normal:
			Brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Green);
			break;
		case ETile_Option::ImpossibleToMove:
			Brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Red);
			break;
		}

		RECT	rc = {};
		rc.left = (long)Pos.x;
		rc.top = (long)Pos.y;
		rc.right = (long)(Pos.x + m_Size.x);
		rc.bottom = (long)(Pos.y + m_Size.y);
		FrameRect(hDC, &rc, Brush);
	}
}

void CTile::Save(FILE* File)
{
	fwrite(&m_Option, sizeof(ETile_Option), 1, File);
	fwrite(&m_Pos, sizeof(Vector2), 1, File);
	fwrite(&m_Size, sizeof(Vector2), 1, File);

	fwrite(&m_Render, sizeof(bool), 1, File);
	fwrite(&m_SideCollision, sizeof(bool), 1, File);

	fwrite(&m_IndexX, sizeof(int), 1, File);
	fwrite(&m_IndexY, sizeof(int), 1, File);
	fwrite(&m_Index, sizeof(int), 1, File);
	fwrite(&m_TileFrame, sizeof(int), 1, File);

	fwrite(&m_StartFrame, sizeof(Vector2), 1, File);
	fwrite(&m_EndFrame, sizeof(Vector2), 1, File);

	bool	Texture = false;

	if (m_Texture)
		Texture = true;

	fwrite(&Texture, sizeof(bool), 1, File);

	if (m_Texture)
		m_Texture->Save(File);
}

void CTile::Load(FILE* File)
{
	fread(&m_Option, sizeof(ETile_Option), 1, File);
	fread(&m_Pos, sizeof(Vector2), 1, File);
	fread(&m_Size, sizeof(Vector2), 1, File);

	fread(&m_Render, sizeof(bool), 1, File);
	fread(&m_SideCollision, sizeof(bool), 1, File);

	fread(&m_IndexX, sizeof(int), 1, File);
	fread(&m_IndexY, sizeof(int), 1, File);
	fread(&m_Index, sizeof(int), 1, File);
	fread(&m_TileFrame, sizeof(int), 1, File);

	fread(&m_StartFrame, sizeof(Vector2), 1, File);
	fread(&m_EndFrame, sizeof(Vector2), 1, File);

	bool	Texture = false;

	fread(&Texture, sizeof(bool), 1, File);

	if (Texture)
		m_Texture = m_Scene->GetSceneResource()->LoadTexture(File);

	if (m_Texture)
		int a = 0;
}


