#pragma once
#include "GameObject.h"
class CBarrier :
    public CGameObject
{
	friend class CScene;

protected:
	CBarrier();
	CBarrier(const CBarrier& Obj);
	virtual ~CBarrier();

private:
	EEffect_Type	m_EffectType;
	float			m_Duration;
	float			m_Time;
	float			m_Damage;



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

