#pragma once
#include "GameObject.h"
class CAurellionSol :
    public CGameObject
{
	friend class CScene;

protected:
	CAurellionSol();
	CAurellionSol(const CAurellionSol& Obj);
	virtual ~CAurellionSol();

private:
	float	m_Damage;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

