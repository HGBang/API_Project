#pragma once

#include "GameObject.h"

class CTileMap :
	public CGameObject
{
	friend class CScene;

protected:
	CTileMap();
	CTileMap(const CTileMap& Obj);
	virtual ~CTileMap();

private:
	std::vector<class CTile*>	m_vecTile;
	CSharedPtr<class CTexture>	m_TileTexture;
	int		m_CountX;
	int		m_CountY;
	Vector2	m_TileSize;
	int		m_StartX;
	int		m_StartY;
	int		m_EndX;
	int		m_EndY;

public:
	int GetCountX()	const
	{
		return m_CountX;
	}

	int GetCountY()	const
	{
		return m_CountY;
	}

public:
	void ChangeTileOption(const Vector2& Pos, ETile_Option Option);
	void SetTileFrame(const Vector2& Pos, const Vector2& Start,
		const Vector2& End);
	void SetTileRender(const Vector2& Pos, bool Render);
	void SetTileSideCollision(const Vector2& Pos, bool Side);
	class CTile* GetTile(const Vector2& Pos);
	class CTile* GetTile(int Index);
	class CTile* GetTile(int IndexX, int IndexY);
	int GetTileIndexX(float x);
	int GetTileIndexY(float y);
	int GetTileIndex(const Vector2& Pos);
	int GetTileOriginIndexX(float x);
	int GetTileOriginIndexY(float y);
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);


public:
	bool CreateTile(int CountX, int CountY, const Vector2& TileSize);
	void SetTileTexture(const std::string& Name);
	void SetTileTexture(class CTexture* Texture);
	void SetTileTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTileTextureFullPath(const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE

	void SetTileTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTileTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

	void SetTileTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTileTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif // UNICODE

	bool SetTileColorKey(unsigned char r, unsigned char g, unsigned char b,
		int Index = 0);
	bool SetTileColorKeyAll(unsigned char r, unsigned char g, unsigned char b);


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

