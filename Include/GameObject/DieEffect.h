#pragma once
#include "GameObject.h"
class CDieEffect :
    public CGameObject
{

	friend class CScene;

protected:
	CDieEffect();
	CDieEffect(const CDieEffect& Obj);
	virtual ~CDieEffect();

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

	



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);


private:
	void AnimationEnd();
	void MoveFront();
	void MoveBack();
	void GunRotation();
	void GunRotationInv();
};

