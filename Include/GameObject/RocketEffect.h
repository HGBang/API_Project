#pragma once
#include "GameObject.h"
class CRocketEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CRocketEffect();
	CRocketEffect(const CRocketEffect& Obj);
	virtual ~CRocketEffect();

private:
	EEffect_Type	m_EffectType;
	float			m_Duration;
	float			m_Time;
	float			m_Damage;

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



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

private:
	void AnimationEnd();
};

