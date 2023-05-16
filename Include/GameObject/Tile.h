#pragma once

#include "../GameInfo.h"

class CTile
{
	friend class CTileMap;

private:
	CTile();
	~CTile();

private:
	class CScene* m_Scene;
	class CTileMap* m_Owner;
	CSharedPtr<class CTexture>	m_Texture;
	ETile_Option	m_Option;
	Vector2		m_Pos;
	Vector2		m_Size;
	int			m_IndexX;
	int			m_IndexY;
	int			m_Index;
	int			m_TileFrame;
	Vector2		m_StartFrame;
	Vector2		m_EndFrame;
	bool		m_Render;
	bool		m_SideCollision;

public:
	bool GetSideCollision()	const
	{
		return m_SideCollision;
	}

	ETile_Option GetOption()	const
	{
		return m_Option;
	}

	const Vector2& GetPos()	const
	{
		return m_Pos;
	}

	const Vector2& GetSize()	const
	{
		return m_Size;
	}

public:
	void SetRender(bool Render)
	{
		m_Render = Render;
	}

	void SetSideCollision(bool Side)
	{
		m_SideCollision = Side;
	}

	void SetTileInfo(const Vector2& Pos, const Vector2& Size,
		int IndexX, int IndexY, int Index, class CTexture* Texture);
	void SetFrame(const Vector2& Start, const Vector2& End)
	{
		m_StartFrame = Start;
		m_EndFrame = End;
	}

	void SetTileOption(ETile_Option Option)
	{
		m_Option = Option;
	}

public:
	void Render(HDC hDC);
	void Save(FILE* File);
	void Load(FILE* File);


};

