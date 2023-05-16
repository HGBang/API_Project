#pragma once
#include "CCharacter.h"
class CAngelCut :
    public CCharacter
{
	friend class CScene;

protected:
	CAngelCut();
	CAngelCut(const CAngelCut& Obj);
	virtual ~CAngelCut();

private:
	Vector2		m_Dir;
	float	m_WorkTime;
	float	m_Distance;

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

