#pragma once
#include "GameObject.h"
class CMonsterEffect :
    public CGameObject
{

	friend class CScene;

protected:
	CMonsterEffect();
	CMonsterEffect(const CMonsterEffect& Obj);
	virtual ~CMonsterEffect();

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


private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

