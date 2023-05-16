
#include "EditScene.h"
#include "../GameObject/TileMap.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "Camera.h"
#include "../GameManager.h"
#include "EditDlg.h"
#include "../Resource/Texture/Texture.h"

CEditScene::CEditScene() :
	m_TileMapDlg(nullptr)
{
}

CEditScene::~CEditScene()
{
	CGameManager::GetInst()->SetEditMode(false);
	SAFE_DELETE(m_TileMapDlg);
}

bool CEditScene::Init()
{
	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CInput::GetInst()->AddBindFunction<CEditScene>("MoveFront",
		Input_Type::Push, this, &CEditScene::MoveUp);
	CInput::GetInst()->AddBindFunction<CEditScene>("MoveBack",
		Input_Type::Push, this, &CEditScene::MoveDown);
	CInput::GetInst()->AddBindFunction<CEditScene>("GunRotation",
		Input_Type::Push, this, &CEditScene::MoveRight);
	CInput::GetInst()->AddBindFunction<CEditScene>("GunRotationInv",
		Input_Type::Push, this, &CEditScene::MoveLeft);
	CInput::GetInst()->AddBindFunction<CEditScene>("OpenTileMapEditor",
		Input_Type::Down, this, &CEditScene::OpenTileMapEditor);
	CInput::GetInst()->AddBindFunction<CEditScene>("Fire",
		Input_Type::Push, this, &CEditScene::MouseLButtonDrag);

	CGameManager::GetInst()->SetEditMode(true);

	return true;
}

void CEditScene::CreateTileMap(int CountX, int CountY, int SizeX, int SizeY)
{
	if (!m_TileMap)
		m_TileMap = CreateObject<CTileMap>("TileMap");

	m_TileMap->CreateTile(CountX, CountY, Vector2((float)SizeX, (float)SizeY));
}

void CEditScene::SetTileTexture(CTexture* Texture)
{
	if (m_TileMap)
		m_TileMap->SetTileTexture(Texture);
}

void CEditScene::LoadTileMap(const char* FullPath)
{
	if (!m_TileMap)
		m_TileMap = CreateObject<CTileMap>("TileMap");

	m_TileMap->LoadFullPath(FullPath);
}

void CEditScene::MoveLeft()
{
	Vector2 CameraPos = GetCamera()->GetPos();

	GetCamera()->SetPos(CameraPos + Vector2(-500.f * DELTA_TIME, 0.f));
}

void CEditScene::MoveRight()
{
	Vector2 CameraPos = GetCamera()->GetPos();

	GetCamera()->SetPos(CameraPos + Vector2(500.f * DELTA_TIME, 0.f));
}

void CEditScene::MoveUp()
{
	Vector2 CameraPos = GetCamera()->GetPos();

	GetCamera()->SetPos(CameraPos + Vector2(0.f, -500.f * DELTA_TIME));
}

void CEditScene::MoveDown()
{
	Vector2 CameraPos = GetCamera()->GetPos();

	GetCamera()->SetPos(CameraPos + Vector2(0.f, 500.f * DELTA_TIME));
}

void CEditScene::OpenTileMapEditor()
{
	if (!m_TileMapDlg)
	{
		m_TileMapDlg = new CEditDlg;

		m_TileMapDlg->m_Scene = this;
		m_TileMapDlg->Init();
	}
}

void CEditScene::MouseLButtonDrag()
{
	if (!m_TileMap)
		return;

	Vector2	MousePos = CInput::GetInst()->GetMousePos();

	CCamera* Camera = GetCamera();

	if (MousePos.x < 0.f || MousePos.x > Camera->GetResolution().x ||
		MousePos.y < 0.f || MousePos.y > Camera->GetResolution().y)
		return;

	switch (m_TileMapDlg->GetBrushType())
	{
	case ETile_Brush::Frame:
		ChangeFrame();
		break;
	case ETile_Brush::Option:
		ChangeOption();
		break;
	}
}

void CEditScene::ChangeFrame()
{
	Vector2	MousePos = CInput::GetInst()->GetMouseWorldPos();

	const AnimationFrameData* Frame = m_TileMapDlg->GetTileFrameData();

	if (!Frame)
		return;

	m_TileMap->SetTileFrame(MousePos, Frame->Start, Frame->End);
	m_TileMap->SetTileRender(MousePos, m_TileMapDlg->GetCheckRender());
	m_TileMap->SetTileSideCollision(MousePos, m_TileMapDlg->GetCheckSideCollision());
}

void CEditScene::ChangeOption()
{
	Vector2	MousePos = CInput::GetInst()->GetMouseWorldPos();

	ETile_Option SelectOption = m_TileMapDlg->GetSelectOption();

	m_TileMap->ChangeTileOption(MousePos, SelectOption);
	m_TileMap->SetTileRender(MousePos, m_TileMapDlg->GetCheckRender());
	m_TileMap->SetTileSideCollision(MousePos, m_TileMapDlg->GetCheckSideCollision());
}
