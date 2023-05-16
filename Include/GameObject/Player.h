#pragma once
#include "CCharacter.h"

struct SkillCoolDownInfo
{
	float CoolDown;
	bool CoolDownEnable;
};

class CPlayer :
    public CCharacter
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& Obj);
	virtual ~CPlayer();

private:
	float	m_GunAngle;
	float	m_GunLength;
	Vector2	m_GunPos;
	float	m_SolAngle[3];
	float   m_SolLengthMin;
	float   m_SolLengthMax;
	float   m_SolLength;
	float	m_SolRotationSpeed;
	float	m_SolSkillDir;
	bool	m_SolSkillOn;
	float	m_SolSkillTime;
	class CAurellionSol* m_Sol[3];
	int		m_PlayerDir;
	std::vector<std::string>		m_vecSequenceKey[4];
	float	m_Damage;
	float   m_DeadTime;
	float	m_RealDeadTime;

	bool	m_Dead;
	bool	MoveUpDown;
	bool	MoveLeftRight;

	bool	m_Attack;

	bool	m_Soul;
	float	m_SoulTime;
	float	m_RocketTime;

	float	m_NoDieTime;

	bool	m_RocketOn;


	std::vector<SkillCoolDownInfo> m_vecCoolDown;

	int		m_HP;
	int		m_HPMax;

	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_NameBar;

public:
		



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC,float DeltaTime);
	virtual float InflictDamage(float Damage);


private:
	void MoveFront();
	void MoveBack();
	void GunRotation();
	void GunRotationInv();
	void Fire();
	void Skill1();
	void Skill2();
	void Talon();
	void TalonM();
	void JumpKey();
	void Bomb();
	void Resurrection();
	void RocketBomb();

public:
	void SolSkill();

public:
	void Dead();


private:
	void AttackEnd();
	void Attack();
	void AddBombCount();
	

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

};

