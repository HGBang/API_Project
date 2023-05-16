#pragma once
#include "CCharacter.h"
class CBossMonster :
    public CCharacter
{
	friend class CScene;

protected:
	CBossMonster();
	CBossMonster(const CBossMonster& Obj);
	virtual ~CBossMonster();

private:
	Vector2		m_Dir;
	float	m_FireTime;
	int		m_FireCount;
	int		m_HP;
	int		m_HPMax;
	float	m_MoveTime;
	float	m_Distance;
	bool	m_DieSkill;
	float	m_DieSkillTime;

	bool	m_DieCoolTime;
	
	bool	m_HPSkill;


	bool	m_NormalAttack;
	float	m_NormalAttackTime;

	bool	m_PlayerAttack;
	float	m_PlayerAttackTime;

	bool	m_BossCrossOn;
	float	m_BossCrossTime;


	float	m_BossCoolTime;


	bool	m_BossLastAttack;
	float	m_BossLastAttackTime;
	float	m_BossLastSkillTime;






	bool m_Skill1;
	int m_Skill1Count;

	bool m_Skill2;
	int m_Skill2Count;

	bool m_Skill3;
	int m_Skill3Count;

	bool m_Skill4;
	int m_Skill4Count;

	bool m_Skill5;
	int m_Skill5Count;

	bool m_Skill6;
	int m_Skill6Count;

	bool m_Skill7;
	int m_Skill7Count;

	bool m_Skill8;
	int m_Skill8Count;

	bool m_Skill9;
	int m_Skill9Count;




public:
	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_NameBar;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

public:
	void AddBombCount();
	void Skill1();
	void Skill2();
	void Skill3();
	void Skill4();
	void Skill5();
	void Skill6();
	void Skill7();
	void Skill8();
	void Skill9();
	void LastSkill();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

	void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
	void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
};

