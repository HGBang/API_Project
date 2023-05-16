#pragma once
#include "GameObject.h"
class CTalon :
	public CGameObject

{

	friend class CScene;

protected:
	CTalon();
	CTalon(const CTalon& Obj);
	virtual ~CTalon();

private:
	EEffect_Type	m_EffectType;
	float	m_MoveSpeed;
	float		m_Angle;
	float	m_Distance;
	int		m_Dir;
	float	m_FireTime;
	bool	m_Arrow;


public:
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
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

public:
	void AnimationEnd();
};

