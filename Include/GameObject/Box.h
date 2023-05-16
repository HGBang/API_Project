#pragma once
#include "CCharacter.h"
class CBox :
    public CCharacter
{
	friend class CScene;

protected:
	CBox();
	CBox(const CBox& Obj);
	virtual ~CBox();

private:
	int		m_HP;
	int		m_HPMax;
	float	m_Damage;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

	void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
	void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
};

