
#include "TileMap.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Tile.h"
#include "../Scene/Camera.h"
#include "../Scene/SceneManager.h"
#include "../Collision/ColliderBox.h"

CTileMap::CTileMap() :
	m_CountX(0),
	m_CountY(0),
	m_StartX(-1),
	m_StartY(-1),
	m_EndX(-1),
	m_EndY(-1)
{
	SetTypeID<CTileMap>();
	m_RenderLayer = ERender_Layer::Tile;
}

CTileMap::CTileMap(const CTileMap& Obj) :
	CGameObject(Obj)
{
}

CTileMap::~CTileMap()
{
	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}
}

void CTileMap::ChangeTileOption(const Vector2& Pos,
	ETile_Option Option)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile[Index]->SetTileOption(Option);
}

void CTileMap::SetTileFrame(const Vector2& Pos, const Vector2& Start,
	const Vector2& End)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile[Index]->SetFrame(Start, End);
}

void CTileMap::SetTileRender(const Vector2& Pos, bool Render)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile[Index]->SetRender(Render);
}

void CTileMap::SetTileSideCollision(const Vector2& Pos, bool Side)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile[Index]->SetSideCollision(Side);
}

CTile* CTileMap::GetTile(const Vector2& Pos)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return nullptr;

	return m_vecTile[Index];
}

CTile* CTileMap::GetTile(int Index)
{
	return m_vecTile[Index];
}

CTile* CTileMap::GetTile(int IndexX, int IndexY)
{
	return m_vecTile[IndexY * m_CountX + IndexX];
}

int CTileMap::GetTileIndexX(float x)
{
	int	IndexX = (int)(x / m_TileSize.x);

	if (IndexX < 0 || IndexX >= m_CountX)
		return -1;

	return IndexX;
}

int CTileMap::GetTileIndexY(float y)
{
	int	IndexY = (int)(y / m_TileSize.y);

	if (IndexY < 0 || IndexY >= m_CountY)
		return -1;

	return IndexY;
}

int CTileMap::GetTileIndex(const Vector2& Pos)
{
	int	IndexX = GetTileIndexX(Pos.x);
	int	IndexY = GetTileIndexY(Pos.y);

	if (IndexX == -1 || IndexY == -1)
		return -1;

	return IndexY * m_CountX + IndexX;
}

int CTileMap::GetTileOriginIndexX(float x)
{
	return (int)(x / m_TileSize.x);
}

int CTileMap::GetTileOriginIndexY(float y)
{
	return (int)(y / m_TileSize.y);
}

void CTileMap::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CTileMap::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

bool CTileMap::CreateTile(int CountX, int CountY,
	const Vector2& TileSize)
{
	m_CountX = CountX;
	m_CountY = CountY;
	m_TileSize = TileSize;

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}

	m_vecTile.clear();

	m_Size = m_TileSize * Vector2((float)m_CountX, (float)m_CountY);

	m_Scene->GetCamera()->SetWorldResolution(m_Size);

	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			CTile* Tile = new CTile;

			Tile->m_Scene = m_Scene;
			Tile->m_Owner = this;

			Vector2	Pos = m_TileSize * Vector2((float)j, (float)i);

			Tile->SetTileInfo(Pos, m_TileSize, j, i, i * m_CountX + j,
				m_TileTexture);

			m_vecTile.push_back(Tile);
		}
	}

	return true;
}

void CTileMap::SetTileTexture(const std::string& Name)
{
	m_TileTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

void CTileMap::SetTileTexture(CTexture* Texture)
{
	m_TileTexture = Texture;

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

void CTileMap::SetTileTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);

	m_TileTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

void CTileMap::SetTileTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);

	m_TileTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

#ifdef UNICODE

void CTileMap::SetTileTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);

	m_TileTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

void CTileMap::SetTileTextureFullPath(const std::string& Name,
	const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_TileTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

#else

void CTileMap::SetTileTexture(const std::string& Name,
	const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);

	m_TileTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

void CTileMap::SetTileTextureFullPath(const std::string& Name,
	const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_TileTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

#endif

bool CTileMap::SetTileColorKey(unsigned char r, unsigned char g, unsigned char b, int Index)
{
	if (!m_TileTexture)
		return false;

	m_TileTexture->SetColorKey(r, g, b, Index);

	return true;
}

bool CTileMap::SetTileColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_TileTexture)
		return false;

	m_TileTexture->SetColorKeyAll(r, g, b);

	return true;
}

bool CTileMap::Init()
{
	/*SetPos(0.f, 0.f);
	SetSize(1500.f, 1200.f);
	SetPivot(0.f, 0.f);

	SetTexture("Sky", TEXT("Sky.bmp"));*/
	m_Scene->SetTileMap(this);


	//CColliderBox* Box = AddCollider<CColliderBox>("Body");
	//Box->SetExtent(100.f, 100.f);
	//Box->SetCollisionProfile("BoxTile");
	//Box->SetCollisionBeginFunction<CTileMap>(this, &CTileMap::CollisionBegin);
	//Box->SetCollisionEndFunction<CTileMap>(this, &CTileMap::CollisionEnd);


	return true;
}

void CTileMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_vecTile.empty())
	{
		Vector2	Pos;
		Vector2	CameraPos;
		Vector2	Resolution;

		if (m_Scene)
		{
			CameraPos =  m_Scene->GetCamera()->GetPos();
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

		m_StartX = (int)(CameraPos.x / m_TileSize.x);
		m_StartY = (int)(CameraPos.y / m_TileSize.y);

		m_EndX = (int)((CameraPos.x + Resolution.x) / m_TileSize.x);
		m_EndY = (int)((CameraPos.y + Resolution.y) / m_TileSize.y);

		m_StartX = m_StartX < 0 ? 0 : m_StartX;
		m_StartY = m_StartY < 0 ? 0 : m_StartY;

		m_EndX = m_EndX >= m_CountX ? m_CountX - 1 : m_EndX;
		m_EndY = m_EndY >= m_CountY ? m_CountY - 1 : m_EndY;
	}
}

void CTileMap::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

	for (int i = m_StartY; i <= m_EndY; ++i)
	{
		for (int j = m_StartX; j <= m_EndX; ++j)
		{
			m_vecTile[i * m_CountX + j]->Render(hDC);
		}
	}
}

void CTileMap::Save(FILE* File)
{
	CGameObject::Save(File);

	bool	Texture = false;

	if (m_TileTexture)
		Texture = true;

	fwrite(&Texture, sizeof(bool), 1, File);

	if (m_TileTexture)
		m_TileTexture->Save(File);

	fwrite(&m_CountX, sizeof(int), 1, File);
	fwrite(&m_CountY, sizeof(int), 1, File);
	fwrite(&m_TileSize, sizeof(Vector2), 1, File);

	int	TileCount = (int)m_vecTile.size();

	fwrite(&TileCount, sizeof(int), 1, File);

	for (int i = 0; i < TileCount; ++i)
	{
		m_vecTile[i]->Save(File);
	}

	//m_Texture = m_Scene->GetSceneResource()->LoadTexture(File);
}

void CTileMap::Load(FILE* File)
{
	CGameObject::Load(File);

	bool	Texture = false;

	fread(&Texture, sizeof(bool), 1, File);

	if (Texture)
		m_TileTexture = m_Scene->GetSceneResource()->LoadTexture(File);

	fread(&m_CountX, sizeof(int), 1, File);
	fread(&m_CountY, sizeof(int), 1, File);
	fread(&m_TileSize, sizeof(Vector2), 1, File);

	int	TileCount = 0;

	fread(&TileCount, sizeof(int), 1, File);

	for (int i = 0; i < TileCount; ++i)
	{
		CTile* Tile = new CTile;

		Tile->m_Owner = this;
		Tile->m_Scene = m_Scene;
		Tile->Load(File);

		m_vecTile.push_back(Tile);
	}
}
