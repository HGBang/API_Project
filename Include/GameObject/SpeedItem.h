#pragma once
#include "GameObject.h"
class CSpeedItem :
    public CGameObject
{
	friend class CScene;

protected:
	CSpeedItem();
	CSpeedItem(const CSpeedItem& Obj);
	virtual ~CSpeedItem();

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

