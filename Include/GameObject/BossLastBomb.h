#pragma once
#include "GameObject.h"
class CBossLastBomb :
    public CGameObject
{
	friend class CScene;

protected:
	CBossLastBomb();
	CBossLastBomb(const CBossLastBomb& Obj);
	virtual ~CBossLastBomb();

private:
	float		m_Angle;
	float	m_Distance;
	float	m_FireTime;
	float	m_Damage;
	bool	m_Target;



public:
	void SetDamage(float Damage)
	{
		m_Damage = Damage;
	}
	void SetDistance(float Dist)
	{
		m_Distance = Dist;
	}

	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

private:
	void AnimationEnd();
};

