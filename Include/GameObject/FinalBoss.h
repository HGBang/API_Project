#pragma once
#include "CCharacter.h"
#include "GameObject.h"
class CFinalBoss :
    public CCharacter
{
	friend class CScene;

protected:
	CFinalBoss();
	CFinalBoss(const CFinalBoss& Obj);
	virtual ~CFinalBoss();



private:
	Vector2		m_Dir;
	float	m_FireTime;
	int		m_FireCount;
	int		m_HP;
	int		m_HPMax;
	float	m_MoveTime;
	float	m_Distance;

	float	m_ClearTime;

	bool	m_PizzaSkillOn;


	float   m_PizzaTime;
	float	m_PizzaCoolTime;


	bool	m_Pizza1On;
	float   m_Pizza1Time;
	int		m_Pizza1Bullet;

	bool	m_Pizza2On;
	float   m_Pizza2Time;
	int		m_Pizza2Bullet;

	bool	m_Pizza3On;
	float   m_Pizza3Time;
	int		m_Pizza3Bullet;

	bool	m_Pizza4On;
	float   m_Pizza4Time;
	int		m_Pizza4Bullet;


	bool	m_DieSkillOn;
	float	m_DieSkillTime;


	float	m_DieTime;
	int		m_DieCount;
	float	m_DieOnTime;
	

	bool	m_CrossSkillOn;
	float	m_CrossSkillTime;
	float	m_CrossTime;
	int		m_CrossAngle;
	float	m_FinalBombTime;


	bool	m_TonadoSkillOn;
	float	m_TonadoSkillTime;
	bool	m_FinalCut;
	bool	m_FinalAttackOn;






public:
	CSharedPtr<class CWidgetComponent>	m_NameBar;



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

public:
	void PizzaSkill1();
	void PizzaSkill2();
	void PizzaSkill3();
	void PizzaSkill4();

public:
	void DeleteAngelNpc();



private:

};

