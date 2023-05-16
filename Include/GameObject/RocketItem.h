#pragma once
#include "GameObject.h"
class CRocketItem :
    public CGameObject
{
	friend class CScene;

protected:
	CRocketItem();
	CRocketItem(const CRocketItem& Obj);
	virtual ~CRocketItem();

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

