#pragma once
#include "GameObject.h"
class CBomb :
    public CGameObject
{
	friend class CScene;

protected:
	CBomb();
	CBomb(const CBomb& Obj);
	virtual ~CBomb();

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
		m_Damage = Damage;
	}





public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

private:
	void AnimationEnd();
};

