#pragma once
#include "CCharacter.h"
class CSecondMonster :
    public CCharacter
{
	friend class CScene;

protected:
	CSecondMonster();
	CSecondMonster(const CSecondMonster& Obj);
	virtual ~CSecondMonster();

private:
	Vector2		m_Dir;
	float	m_FireTime;
	int		m_FireCount;
	int		m_HP;
	int		m_HPMax;
	float	m_MoveTime;

public:
	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_NameBar;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

public:
	void AddBombCount();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

	void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
	void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
};

