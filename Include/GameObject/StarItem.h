#pragma once
#include "GameObject.h"
class CStarItem :
    public CGameObject
{
	friend class CScene;

protected:
	CStarItem();
	CStarItem(const CStarItem& Obj);
	virtual ~CStarItem();

private:
	float	m_ItemTime;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

