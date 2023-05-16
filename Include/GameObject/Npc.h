#pragma once
#include "CCharacter.h"
class CNpc :
	public CCharacter
{
	friend class CScene;

protected:
	CNpc();
	CNpc(const CNpc& Obj);
	virtual ~CNpc();

private:
	Vector2		m_Dir;
	float	m_FireTime;
	int		m_FireCount;
	int		m_HP;
	int		m_HPMax;
	float	m_MoveTime;
	float	m_Distance;
	bool	m_SpeedItem;
	bool	m_StarItem;
	bool	m_AddBombItem;
	float	m_WorkTime;

public:
	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_NameBar;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);
};

