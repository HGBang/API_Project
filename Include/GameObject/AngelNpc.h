#pragma once
#include "CCharacter.h"
class CAngelNpc :
    public CCharacter
{
	friend class CScene;

protected:
	CAngelNpc();
	CAngelNpc(const CAngelNpc& Obj);
	virtual ~CAngelNpc();

private:
	Vector2		m_Dir;
	float	m_WorkTime;
	bool	m_Barrier;

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

