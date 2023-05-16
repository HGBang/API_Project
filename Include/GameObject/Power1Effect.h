#pragma once
#include "GameObject.h"
class CPower1Effect :
    public CGameObject
{
	friend class CScene;

protected:
	CPower1Effect();
	CPower1Effect(const CPower1Effect& Obj);
	virtual ~CPower1Effect();

private:
	EEffect_Type	m_EffectType;
	float			m_Duration;
	float			m_Time;
	float			m_Damage;
	float		    m_Angle;
	float			m_MoveDistance;

public:
	EEffect_Type GetEffectType() const
	{
		return m_EffectType;
	}

	void SetDuration(float Duration)
	{
		m_Duration = Duration;
	}

	void SetDamage(float Damage)
	{
		Damage = m_Damage;
	}



	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}

	void SetDistance(float Distance)
	{
		m_MoveDistance = Distance;
	}


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

private:
	void AnimationEnd();


private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

