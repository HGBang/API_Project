#include"BossMonster.h"
#include"../Scene/Scene.h"
#include "Bullet.h"
#include "../Collision/ColliderBox.h"
#include "../GameManager.h"
#include "Effect.h"
#include "GameObject.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/Text.h"
#include "Bomb.h"
#include "MonsterBomb.h"
#include "Bomb2.h"
#include "BossMonsterDieEffect.h"
#include "BossMonsterBomb.h"
#include <time.h>
#include "BossCrossBomb.h"
#include "BossLastBomb.h"

int i = 0;
int j = 0;

CBossMonster::CBossMonster() :
	m_HP(500),
	m_HPMax(500)
{
	SetTypeID<CBossMonster>();
}

CBossMonster::CBossMonster(const CBossMonster& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir),
	m_FireTime(Obj.m_FireTime),
	m_FireCount(Obj.m_FireCount)
{
}

CBossMonster::~CBossMonster()
{
}



bool CBossMonster::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 0.f;
	m_FireTime = 0.f;
	m_Dir = Vector2(0.f, 1.f);
	m_FireCount = 0;

	m_Monster = false;
	m_BossMonster = true;
	SetSideWallCheck(true);
	SetPhysicsSimulate(true);
	m_DirLR = -1.f;
	m_StartMonster = true;
	m_Stop = false;

	SetPos(870.f, 150.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("Monster", TEXT("teemo.bmp"));
	//SetColorKey(255, 0, 255);

	CreateAnimation();
	AddAnimation("BossStand" , true , 3.f);
	AddAnimation("BossDown");
	AddAnimation("BossRight");
	AddAnimation("BossUp");
	AddAnimation("BossLeft");

	m_Distance = 1000.f;

	m_BombCount = 1;

	m_PlayerCheck = false;

	
	

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(200.f, 200.f);
	Box->SetCollisionProfile("BossMonster");
	Box->SetCollisionBeginFunction<CBossMonster>(this, &CBossMonster::CollisionBegin);
	Box->SetCollisionEndFunction<CBossMonster>(this, &CBossMonster::CollisionEnd);


	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	//Circle->SetRadius(50.f);
	//Circle->SetCollisionProfile("Monster");

	//Circle->SetCollisionBeginFunction<CBossMonster>(this, &CBossMonster::CollisionBegin);
	//Circle->SetCollisionEndFunction<CBossMonster>(this, &CBossMonster::CollisionEnd);

	//Circle->SetMouseCollisionBeginFunction<CBossMonster>(this, &CBossMonster::CollisionMouseBegin);
	//Circle->SetMouseCollisionEndFunction<CBossMonster>(this, &CBossMonster::CollisionMouseEnd);



	m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");
	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar, "HPBar", TEXT("CharacterHPBar.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetSize(50.f, 10.f);
	m_HPBar->SetPos(-25.f, -65.f);


	m_NameBar = CreateWidgetComponent<CText>("NameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("BOSS"));
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(-25.f, -85.f);


	m_DieSkill = true;
	m_NormalAttack = false;
	m_PlayerAttack = false;


	
	m_Skill1 = true;
	m_Skill1Count = 20;

	m_Skill2 = false;
	m_Skill2Count = 20;

	m_Skill3 = false;
	m_Skill3Count = 20;

	m_Skill4 = false;
	m_Skill4Count = 20;

	m_Skill5 = false;
	m_Skill5Count = 20;

	m_Skill6 = false;
	m_Skill6Count = 20;

	m_Skill7 = false;
	m_Skill7Count = 20;

	m_Skill8 = false;
	m_Skill8Count = 20;

	m_Skill9 = false;
	m_Skill9Count = 20;

	m_HPSkill = false;




	return true;
}

void CBossMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	

	m_Pos.x += m_DirLR * DELTA_TIME * m_MoveSpeed;

	m_Pos.y += m_DirUP * DELTA_TIME * m_MoveSpeed;



	m_MoveTime += DELTA_TIME;

	if (m_MoveTime > 10.f)
	{
		m_MoveSpeed = 30.f;

	
		srand((int)time(0));
		rand();

		unsigned int i = (int)rand() % 4;

		if (i == 0)
		{
			SetDirLR(1.f);
			SetDirUP(0.f);
		
		}

		if (i == 1)
		{
			SetDirLR(-1.f);
			SetDirUP(0.f);
		
		}

		if (i == 2)
		{
			SetDirLR(0.f);
			SetDirUP(1.f);
			
		}

		if (i == 3)
		{
			SetDirLR(0.f);
			SetDirUP(-1.f);
		
		}

		if (m_MoveTime > 15.f)
		{
			m_MoveSpeed = 0.f;
			m_MoveTime = 0.f;
		}


	/*	if (m_MoveTime > 23.f)
		{
			m_MoveSpeed = 0.f;
			m_MoveTime = 0.f;
		}*/

	}

	if (m_Pos == m_PrevPos)
		ChangeAnimation("BossStand");

	if (m_Move.x < 0.f)
		ChangeAnimation("BossLeft");

	if (m_Move.x > 0.f)
		ChangeAnimation("BossRight");

	if (m_Move.y > 0.f)
		ChangeAnimation("BossDown");

	if (m_Move.y < 0.f)
		ChangeAnimation("BossUp");


	if (m_HP <= 250)
	{
		m_HPSkill = true;
	}


	if (m_HPSkill)
	{

		m_HPSkill = false;
		m_DieCoolTime = false;


		m_FireTime += DeltaTime;

		if (m_FireTime > 0.1f && m_Skill1)
		{
			Skill1();
			m_FireTime = 0.f;
			--m_Skill1Count;

			if (m_Skill1Count == 0)
			{
				m_Skill1 = false;
				m_Skill2 = true;
			}
		}

		if (m_FireTime > 0.1f && m_Skill2)
		{
			Skill2();
			m_FireTime = 0.f;
			--m_Skill2Count;

			if (m_Skill2Count == 0)
			{
				m_Skill2 = false;
				m_Skill3 = true;
			}
		}

		if (m_FireTime > 0.1f && m_Skill3)
		{
			Skill3();
			m_FireTime = 0.f;
			--m_Skill3Count;

			if (m_Skill3Count == 0)
			{
				m_Skill3 = false;
				m_Skill4 = true;
			}
		}

		if (m_FireTime > 0.1f && m_Skill4)
		{
			Skill4();
			m_FireTime = 0.f;
			--m_Skill4Count;

			if (m_Skill4Count == 0)
			{
				m_Skill4 = false;
				m_Skill5 = true;
			}
		}

		if (m_FireTime > 0.1f && m_Skill5)
		{
			Skill5();
			m_FireTime = 0.f;
			--m_Skill5Count;

			if (m_Skill5Count == 0)
			{
				m_Skill5 = false;
				m_Skill6 = true;
			}
		}

		if (m_FireTime > 0.1f && m_Skill6)
		{
			Skill6();
			m_FireTime = 0.f;
			--m_Skill6Count;

			if (m_Skill6Count == 0)
			{
				m_Skill6 = false;
				m_Skill7 = true;
			}
		}

		if (m_FireTime > 0.1f && m_Skill7)
		{
			Skill7();
			m_FireTime = 0.f;
			--m_Skill7Count;

			if (m_Skill7Count == 0)
			{
				m_Skill7 = false;
				m_Skill8 = true;
			}
		}

		if (m_FireTime > 0.1f && m_Skill8)
		{
			Skill8();
			m_FireTime = 0.f;
			--m_Skill8Count;

			if (m_Skill8Count == 0)
			{
				m_Skill8 = false;
				m_Skill9 = true;
			}
		}

		if (m_FireTime > 0.1f && m_Skill9)
		{
			Skill9();
			m_FireTime = 0.f;
			--m_Skill9Count;

			if (m_Skill9Count == 0)
			{
				m_Skill9 = false;
				m_BossLastAttack = true;
			}
		}

	}


	if (m_HP == 100)
	{
		m_BossCrossOn = true;

	}


	if (m_BossCrossOn)
	{

		m_BossCoolTime += DELTA_TIME;

		if (m_BossCoolTime < 9.f)
		{
			m_Time += DELTA_TIME;

			if (m_Time > 0.1f)
			{
				CBossCrossBomb* Bullet = m_Scene->CreateObject<CBossCrossBomb>("BossCrossBomb");
				Bullet->SetPos(m_Pos);
				Bullet->SetAngle(90.f + i + j);

				CBossCrossBomb* Bullet1 = m_Scene->CreateObject<CBossCrossBomb>("BossCrossBomb");
				Bullet1->SetPos(m_Pos);
				Bullet1->SetAngle(180.f + i + j);

				CBossCrossBomb* Bullet2 = m_Scene->CreateObject<CBossCrossBomb>("BossCrossBomb");
				Bullet2->SetPos(m_Pos);
				Bullet2->SetAngle(270.f + i + j);

				CBossCrossBomb* Bullet3 = m_Scene->CreateObject<CBossCrossBomb>("BossCrossBomb");
				Bullet3->SetPos(m_Pos);
				Bullet3->SetAngle(360.f + i + j);

				if (i < 90)
				{
					++i;
					++i;
					++i;
				}

				if (i == 90)
				{
					--j;
					--j;
					--j;
				}

				m_Time = 0.f;

			}
		}

		if (m_BossCoolTime > 9.5f)
		{
			m_BossCoolTime = 0.f;
			m_BossCrossOn = false;
		}
	}



	if (m_Scene->GetPlayer())
	{
		
		


		if (m_BossLastAttack)
		{
			m_BossLastAttackTime += DELTA_TIME;
			m_BossLastSkillTime += DELTA_TIME;

			if (m_BossLastAttackTime > 4.5f)
			{
				CBossLastBomb* LastBomb = m_Scene->CreateObject<CBossLastBomb>("BossLastBomb");
				CBossLastBomb* LastBomb1 = m_Scene->CreateObject<CBossLastBomb>("BossLastBomb");
				CBossLastBomb* LastBomb2 = m_Scene->CreateObject<CBossLastBomb>("BossLastBomb");

				float	LastBombX = m_Pos.x - m_Pivot.x * m_Size.x -
					(1.f - LastBomb->GetPivot().x) * LastBomb->GetSize().x;
				LastBomb->SetPos(m_Pos);
				LastBomb->SetDamage(10.f);

				float Angle = LastBomb->GetPos().Angle(m_Scene->GetPlayer()->GetPos());
				LastBomb->SetAngle(Angle);


				LastBomb1->SetPos(m_Pos);
				LastBomb1->SetDamage(10.f);
				LastBomb1->SetAngle(Angle - 10.f);

				LastBomb2->SetPos(m_Pos);
				LastBomb2->SetDamage(10.f);
				LastBomb2->SetAngle(Angle + 10.f);



				m_BossLastAttackTime = 0.f;
			}

			if (m_BossLastSkillTime > 10.f)
			{
				LastSkill();
				m_BossLastSkillTime = 0.f;
			}



		}




		m_DieSkillTime += DeltaTime;

		if (m_DieSkillTime > 3.f)
		{
			if (m_DieSkill)
			{
				if (m_Scene->GetPlayer())
				{
					CBossMonsterBomb* Bullet = m_Scene->CreateObject<CBossMonsterBomb>("CBossMonsterBomb");
						

					float	BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
						(1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

					Bullet->SetPos(m_Pos);
					Bullet->SetDamage(10.f);

					float Angle = Bullet->GetPos().Angle(m_Scene->GetPlayer()->GetPos());

					Bullet->SetAngle(Angle);

					m_DieSkill = false;
					m_DieSkillTime = 0.f;

					m_DieCoolTime = true;

				}
			}
		}


		if (m_DieCoolTime)
		{

			m_NormalAttackTime += DELTA_TIME;

			if (m_NormalAttackTime > 4.f)
			{
				m_NormalAttack = true;


				if (m_NormalAttack && m_Scene->GetPlayer())
				{
					CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
					CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
					CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");

					float	BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
						(1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

					Bullet->SetPos(m_Pos);
					Bullet->SetDamage(10.f);

					float Angle = Bullet->GetPos().Angle(m_Scene->GetPlayer()->GetPos());
					Bullet->SetAngle(Angle);
					Bullet->SetMoveSpeed(250.f);

					Bullet1->SetPos(m_Pos);
					Bullet1->SetDamage(10.f);
					Bullet1->SetAngle(Angle + 10.f);
					Bullet1->SetMoveSpeed(250.f);

					Bullet2->SetPos(m_Pos);
					Bullet2->SetDamage(10.f);
					Bullet2->SetAngle(Angle - 10.f);
					Bullet2->SetMoveSpeed(250.f);




					m_NormalAttackTime = 0.f;
					m_NormalAttack = false;

				}

			}


			m_PlayerAttackTime += DELTA_TIME;

			if (m_PlayerAttackTime > 7.f)
			{
				m_PlayerAttack = true;


				if (m_PlayerAttack && m_Scene->GetPlayer())
				{
					CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");

					float	BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
						(1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

					Bullet->SetPos(m_Pos);
					Bullet->SetDamage(10.f);

					float Angle = Bullet->GetPos().Angle(m_Scene->GetPlayer()->GetPos());
					Bullet->SetAngle(Angle);
					Bullet->SetMoveSpeed(350.f);

					m_PlayerAttackTime = 0.f;
					m_PlayerAttack = true;


				}

			}


		}
	}

}

void CBossMonster::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CBossMonster::Render(HDC hDC, float DeltaTime)
{

	CCharacter::Render(hDC, DeltaTime);

	//Rectangle(hDC, 0, 100, 0, 100);
}

float CBossMonster::InflictDamage(float Damage)
{

	Damage = CCharacter::InflictDamage(Damage);
	m_HP -= (int)Damage;

	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);

	if (m_HP <= 0)
	{
		SetActive(false);
		CBossMonsterDieEffect* Effect = m_Scene->CreateObject<CBossMonsterDieEffect>("BossDie1");
		Effect->SetPivot(0.5f, 0.5f);
		Effect->SetPos(m_Pos.x, m_Pos.y - 25.f);
		Effect->AddAnimation("BossDie1", false, 2.5f);

	}

	return Damage;
}

void CBossMonster::AddBombCount()
{
	++m_BombCount;
}

void CBossMonster::Skill1()
{

	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet25->SetPos(m_Pos);
	Bullet25->SetDamage(10.f);
	Bullet25->SetAngle(135.f);
	Bullet25->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet26->SetPos(m_Pos);
	//Bullet26->SetDamage(10.f);
	//Bullet26->SetAngle(140.f);
	//Bullet26->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet27->SetPos(m_Pos);
	//Bullet27->SetDamage(10.f);
	//Bullet27->SetAngle(145.f);
	//Bullet27->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet28->SetPos(m_Pos);
	Bullet28->SetDamage(10.f);
	Bullet28->SetAngle(150.f);
	Bullet28->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet29->SetPos(m_Pos);
	Bullet29->SetDamage(10.f);
	Bullet29->SetAngle(155.f);
	Bullet29->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);

	


}

void CBossMonster::Skill2()
{
	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet25->SetPos(m_Pos);
	Bullet25->SetDamage(10.f);
	Bullet25->SetAngle(135.f);
	Bullet25->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet26->SetPos(m_Pos);
	Bullet26->SetDamage(10.f);
	Bullet26->SetAngle(140.f);
	Bullet26->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet27->SetPos(m_Pos);
	//Bullet27->SetDamage(10.f);
	//Bullet27->SetAngle(145.f);
	//Bullet27->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet28->SetPos(m_Pos);
	//Bullet28->SetDamage(10.f);
	//Bullet28->SetAngle(150.f);
	//Bullet28->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet29->SetPos(m_Pos);
	Bullet29->SetDamage(10.f);
	Bullet29->SetAngle(155.f);
	Bullet29->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);

}

void CBossMonster::Skill3()
{
	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet25->SetPos(m_Pos);
	Bullet25->SetDamage(10.f);
	Bullet25->SetAngle(135.f);
	Bullet25->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet26->SetPos(m_Pos);
	Bullet26->SetDamage(10.f);
	Bullet26->SetAngle(140.f);
	Bullet26->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet27->SetPos(m_Pos);
	Bullet27->SetDamage(10.f);
	Bullet27->SetAngle(145.f);
	Bullet27->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet28->SetPos(m_Pos);
	//Bullet28->SetDamage(10.f);
	//Bullet28->SetAngle(150.f);
	//Bullet28->SetMoveSpeed(30.f);

	/*CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet29->SetPos(m_Pos);
	Bullet29->SetDamage(10.f);
	Bullet29->SetAngle(155.f);
	Bullet29->SetMoveSpeed(30.f);*/

	CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);

}

void CBossMonster::Skill4()
{
	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet25->SetPos(m_Pos);
	Bullet25->SetDamage(10.f);
	Bullet25->SetAngle(135.f);
	Bullet25->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet26->SetPos(m_Pos);
	Bullet26->SetDamage(10.f);
	Bullet26->SetAngle(140.f);
	Bullet26->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet27->SetPos(m_Pos);
	Bullet27->SetDamage(10.f);
	Bullet27->SetAngle(145.f);
	Bullet27->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet28->SetPos(m_Pos);
	Bullet28->SetDamage(10.f);
	Bullet28->SetAngle(150.f);
	Bullet28->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet29->SetPos(m_Pos);
	//Bullet29->SetDamage(10.f);
	//Bullet29->SetAngle(155.f);
	//Bullet29->SetMoveSpeed(30.f);

	/*CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);*/

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);
}

void CBossMonster::Skill5()
{
	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet25->SetPos(m_Pos);
	Bullet25->SetDamage(10.f);
	Bullet25->SetAngle(135.f);
	Bullet25->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet26->SetPos(m_Pos);
	Bullet26->SetDamage(10.f);
	Bullet26->SetAngle(140.f);
	Bullet26->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet27->SetPos(m_Pos);
	Bullet27->SetDamage(10.f);
	Bullet27->SetAngle(145.f);
	Bullet27->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet28->SetPos(m_Pos);
	Bullet28->SetDamage(10.f);
	Bullet28->SetAngle(150.f);
	Bullet28->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet29->SetPos(m_Pos);
	//Bullet29->SetDamage(10.f);
	//Bullet29->SetAngle(155.f);
	//Bullet29->SetMoveSpeed(30.f);

	/*CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);*/

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);
}

void CBossMonster::Skill6()
{
	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet25->SetPos(m_Pos);
	Bullet25->SetDamage(10.f);
	Bullet25->SetAngle(135.f);
	Bullet25->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet26->SetPos(m_Pos);
	Bullet26->SetDamage(10.f);
	Bullet26->SetAngle(140.f);
	Bullet26->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet27->SetPos(m_Pos);
	Bullet27->SetDamage(10.f);
	Bullet27->SetAngle(145.f);
	Bullet27->SetMoveSpeed(30.f);

	/*CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet28->SetPos(m_Pos);
	Bullet28->SetDamage(10.f);
	Bullet28->SetAngle(150.f);
	Bullet28->SetMoveSpeed(30.f);*/

	//CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet29->SetPos(m_Pos);
	//Bullet29->SetDamage(10.f);
	//Bullet29->SetAngle(155.f);
	//Bullet29->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);
}

void CBossMonster::Skill7()
{
	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet25->SetPos(m_Pos);
	Bullet25->SetDamage(10.f);
	Bullet25->SetAngle(135.f);
	Bullet25->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet26->SetPos(m_Pos);
	Bullet26->SetDamage(10.f);
	Bullet26->SetAngle(140.f);
	Bullet26->SetMoveSpeed(30.f);

	/*CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet27->SetPos(m_Pos);
	Bullet27->SetDamage(10.f);
	Bullet27->SetAngle(145.f);
	Bullet27->SetMoveSpeed(30.f);*/

	//CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet28->SetPos(m_Pos);
	//Bullet28->SetDamage(10.f);
	//Bullet28->SetAngle(150.f);
	//Bullet28->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet29->SetPos(m_Pos);
	Bullet29->SetDamage(10.f);
	Bullet29->SetAngle(155.f);
	Bullet29->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);
}

void CBossMonster::Skill8()
{
	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet25->SetPos(m_Pos);
	Bullet25->SetDamage(10.f);
	Bullet25->SetAngle(135.f);
	Bullet25->SetMoveSpeed(30.f);

	/*CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet26->SetPos(m_Pos);
	Bullet26->SetDamage(10.f);
	Bullet26->SetAngle(140.f);
	Bullet26->SetMoveSpeed(30.f);*/

	//CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet27->SetPos(m_Pos);
	//Bullet27->SetDamage(10.f);
	//Bullet27->SetAngle(145.f);
	//Bullet27->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet28->SetPos(m_Pos);
	Bullet28->SetDamage(10.f);
	Bullet28->SetAngle(150.f);
	Bullet28->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet29->SetPos(m_Pos);
	Bullet29->SetDamage(10.f);
	Bullet29->SetAngle(155.f);
	Bullet29->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);
}

void CBossMonster::Skill9()
{
	CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet->SetPos(m_Pos);
	Bullet->SetDamage(10.f);
	Bullet->SetAngle(10.f);
	Bullet->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet1->SetPos(m_Pos);
	Bullet1->SetDamage(10.f);
	Bullet1->SetAngle(15.f);
	Bullet1->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet2->SetPos(m_Pos);
	Bullet2->SetDamage(10.f);
	Bullet2->SetAngle(20.f);
	Bullet2->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet3->SetPos(m_Pos);
	Bullet3->SetDamage(10.f);
	Bullet3->SetAngle(25.f);
	Bullet3->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet4 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet4->SetPos(m_Pos);
	Bullet4->SetDamage(10.f);
	Bullet4->SetAngle(30.f);
	Bullet4->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet5 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet5->SetPos(m_Pos);
	Bullet5->SetDamage(10.f);
	Bullet5->SetAngle(35.f);
	Bullet5->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet6 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet6->SetPos(m_Pos);
	Bullet6->SetDamage(10.f);
	Bullet6->SetAngle(40.f);
	Bullet6->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet7 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet7->SetPos(m_Pos);
	Bullet7->SetDamage(10.f);
	Bullet7->SetAngle(45.f);
	Bullet7->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet8 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet8->SetPos(m_Pos);
	Bullet8->SetDamage(10.f);
	Bullet8->SetAngle(50.f);
	Bullet8->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet9 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet9->SetPos(m_Pos);
	Bullet9->SetDamage(10.f);
	Bullet9->SetAngle(55.f);
	Bullet9->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet10 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet10->SetPos(m_Pos);
	Bullet10->SetDamage(10.f);
	Bullet10->SetAngle(60.f);
	Bullet10->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet11 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet11->SetPos(m_Pos);
	Bullet11->SetDamage(10.f);
	Bullet11->SetAngle(65.f);
	Bullet11->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet12 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet12->SetPos(m_Pos);
	Bullet12->SetDamage(10.f);
	Bullet12->SetAngle(70.f);
	Bullet12->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet13 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet13->SetPos(m_Pos);
	Bullet13->SetDamage(10.f);
	Bullet13->SetAngle(75.f);
	Bullet13->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet14 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet14->SetPos(m_Pos);
	Bullet14->SetDamage(10.f);
	Bullet14->SetAngle(80.f);
	Bullet14->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet15 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet15->SetPos(m_Pos);
	Bullet15->SetDamage(10.f);
	Bullet15->SetAngle(85.f);
	Bullet15->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet16 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet16->SetPos(m_Pos);
	Bullet16->SetDamage(10.f);
	Bullet16->SetAngle(90.f);
	Bullet16->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet17 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet17->SetPos(m_Pos);
	Bullet17->SetDamage(10.f);
	Bullet17->SetAngle(95.f);
	Bullet17->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet18 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet18->SetPos(m_Pos);
	Bullet18->SetDamage(10.f);
	Bullet18->SetAngle(100.f);
	Bullet18->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet19 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet19->SetPos(m_Pos);
	Bullet19->SetDamage(10.f);
	Bullet19->SetAngle(105.f);
	Bullet19->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet20 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet20->SetPos(m_Pos);
	Bullet20->SetDamage(10.f);
	Bullet20->SetAngle(110.f);
	Bullet20->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet21 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet21->SetPos(m_Pos);
	Bullet21->SetDamage(10.f);
	Bullet21->SetAngle(115.f);
	Bullet21->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet22 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet22->SetPos(m_Pos);
	Bullet22->SetDamage(10.f);
	Bullet22->SetAngle(120.f);
	Bullet22->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet23 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet23->SetPos(m_Pos);
	Bullet23->SetDamage(10.f);
	Bullet23->SetAngle(125.f);
	Bullet23->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet24 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet24->SetPos(m_Pos);
	Bullet24->SetDamage(10.f);
	Bullet24->SetAngle(130.f);
	Bullet24->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet25 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet25->SetPos(m_Pos);
	//Bullet25->SetDamage(10.f);
	//Bullet25->SetAngle(135.f);
	//Bullet25->SetMoveSpeed(30.f);

	//CMonsterBomb* Bullet26 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	//Bullet26->SetPos(m_Pos);
	//Bullet26->SetDamage(10.f);
	//Bullet26->SetAngle(140.f);
	//Bullet26->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet27 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet27->SetPos(m_Pos);
	Bullet27->SetDamage(10.f);
	Bullet27->SetAngle(145.f);
	Bullet27->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet28 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet28->SetPos(m_Pos);
	Bullet28->SetDamage(10.f);
	Bullet28->SetAngle(150.f);
	Bullet28->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet29 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet29->SetPos(m_Pos);
	Bullet29->SetDamage(10.f);
	Bullet29->SetAngle(155.f);
	Bullet29->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet30 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet30->SetPos(m_Pos);
	Bullet30->SetDamage(10.f);
	Bullet30->SetAngle(160.f);
	Bullet30->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet31 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet31->SetPos(m_Pos);
	Bullet31->SetDamage(10.f);
	Bullet31->SetAngle(165.f);
	Bullet31->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet32 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet32->SetPos(m_Pos);
	Bullet32->SetDamage(10.f);
	Bullet32->SetAngle(170.f);
	Bullet32->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet33 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet33->SetPos(m_Pos);
	Bullet33->SetDamage(10.f);
	Bullet33->SetAngle(175.f);
	Bullet33->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet34 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet34->SetPos(m_Pos);
	Bullet34->SetDamage(10.f);
	Bullet34->SetAngle(180.f);
	Bullet34->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet35 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet35->SetPos(m_Pos);
	Bullet35->SetDamage(10.f);
	Bullet35->SetAngle(185.f);
	Bullet35->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet36 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet36->SetPos(m_Pos);
	Bullet36->SetDamage(10.f);
	Bullet36->SetAngle(190.f);
	Bullet36->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet37 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet37->SetPos(m_Pos);
	Bullet37->SetDamage(10.f);
	Bullet37->SetAngle(195.f);
	Bullet37->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet38 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet38->SetPos(m_Pos);
	Bullet38->SetDamage(10.f);
	Bullet38->SetAngle(200.f);
	Bullet38->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet39 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet39->SetPos(m_Pos);
	Bullet39->SetDamage(10.f);
	Bullet39->SetAngle(205.f);
	Bullet39->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet40 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet40->SetPos(m_Pos);
	Bullet40->SetDamage(10.f);
	Bullet40->SetAngle(210.f);
	Bullet40->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet41 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet41->SetPos(m_Pos);
	Bullet41->SetDamage(10.f);
	Bullet41->SetAngle(215.f);
	Bullet41->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet42 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet42->SetPos(m_Pos);
	Bullet42->SetDamage(10.f);
	Bullet42->SetAngle(220.f);
	Bullet42->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet43 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet43->SetPos(m_Pos);
	Bullet43->SetDamage(10.f);
	Bullet43->SetAngle(225.f);
	Bullet43->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet44 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet44->SetPos(m_Pos);
	Bullet44->SetDamage(10.f);
	Bullet44->SetAngle(230.f);
	Bullet44->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet45 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet45->SetPos(m_Pos);
	Bullet45->SetDamage(10.f);
	Bullet45->SetAngle(235.f);
	Bullet45->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet46 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet46->SetPos(m_Pos);
	Bullet46->SetDamage(10.f);
	Bullet46->SetAngle(240.f);
	Bullet46->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet47 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet47->SetPos(m_Pos);
	Bullet47->SetDamage(10.f);
	Bullet47->SetAngle(245.f);
	Bullet47->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet48 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet48->SetPos(m_Pos);
	Bullet48->SetDamage(10.f);
	Bullet48->SetAngle(250.f);
	Bullet48->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet49 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet49->SetPos(m_Pos);
	Bullet49->SetDamage(10.f);
	Bullet49->SetAngle(255.f);
	Bullet49->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet50 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet50->SetPos(m_Pos);
	Bullet50->SetDamage(10.f);
	Bullet50->SetAngle(260.f);
	Bullet50->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet51 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet51->SetPos(m_Pos);
	Bullet51->SetDamage(10.f);
	Bullet51->SetAngle(265.f);
	Bullet51->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet52 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet52->SetPos(m_Pos);
	Bullet52->SetDamage(10.f);
	Bullet52->SetAngle(270.f);
	Bullet52->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet53 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet53->SetPos(m_Pos);
	Bullet53->SetDamage(10.f);
	Bullet53->SetAngle(275.f);
	Bullet53->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet54 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet54->SetPos(m_Pos);
	Bullet54->SetDamage(10.f);
	Bullet54->SetAngle(280.f);
	Bullet54->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet55 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet55->SetPos(m_Pos);
	Bullet55->SetDamage(10.f);
	Bullet55->SetAngle(285.f);
	Bullet55->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet56 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet56->SetPos(m_Pos);
	Bullet56->SetDamage(10.f);
	Bullet56->SetAngle(290.f);
	Bullet56->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet57 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet57->SetPos(m_Pos);
	Bullet57->SetDamage(10.f);
	Bullet57->SetAngle(295.f);
	Bullet57->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet58 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet58->SetPos(m_Pos);
	Bullet58->SetDamage(10.f);
	Bullet58->SetAngle(300.f);
	Bullet58->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet59 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet59->SetPos(m_Pos);
	Bullet59->SetDamage(10.f);
	Bullet59->SetAngle(305.f);
	Bullet59->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet60 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet60->SetPos(m_Pos);
	Bullet60->SetDamage(10.f);
	Bullet60->SetAngle(310.f);
	Bullet60->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet61 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet61->SetPos(m_Pos);
	Bullet61->SetDamage(10.f);
	Bullet61->SetAngle(315.f);
	Bullet61->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet62 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet62->SetPos(m_Pos);
	Bullet62->SetDamage(10.f);
	Bullet62->SetAngle(320.f);
	Bullet62->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet63 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet63->SetPos(m_Pos);
	Bullet63->SetDamage(10.f);
	Bullet63->SetAngle(325.f);
	Bullet63->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet64 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet64->SetPos(m_Pos);
	Bullet64->SetDamage(10.f);
	Bullet64->SetAngle(330.f);
	Bullet64->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet65 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet65->SetPos(m_Pos);
	Bullet65->SetDamage(10.f);
	Bullet65->SetAngle(335.f);
	Bullet65->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet66 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet66->SetPos(m_Pos);
	Bullet66->SetDamage(10.f);
	Bullet66->SetAngle(340.f);
	Bullet66->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet67 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet67->SetPos(m_Pos);
	Bullet67->SetDamage(10.f);
	Bullet67->SetAngle(345.f);
	Bullet67->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet68 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet68->SetPos(m_Pos);
	Bullet68->SetDamage(10.f);
	Bullet68->SetAngle(350.f);
	Bullet68->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet69 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet69->SetPos(m_Pos);
	Bullet69->SetDamage(10.f);
	Bullet69->SetAngle(355.f);
	Bullet69->SetMoveSpeed(30.f);

	CMonsterBomb* Bullet70 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
	Bullet70->SetPos(m_Pos);
	Bullet70->SetDamage(10.f);
	Bullet70->SetAngle(360.f);
	Bullet70->SetMoveSpeed(30.f);
}

void CBossMonster::LastSkill()
{

	for (int i = 0; i < 36; ++i)
	{
		CBossLastBomb* LastBomb = m_Scene->CreateObject<CBossLastBomb>("BossLastBomb");
	

		float	LastBombX = m_Pos.x - m_Pivot.x * m_Size.x -
			(1.f - LastBomb->GetPivot().x) * LastBomb->GetSize().x;
		LastBomb->SetPos(m_Pos);
		LastBomb->SetDamage(10.f);

		float Angle = LastBomb->GetPos().Angle(m_Scene->GetPlayer()->GetPos());
		LastBomb->SetAngle(10.f * i );


		
	}


}

void CBossMonster::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	/*m_Scene->GetSceneResource()->SoundPlay("Hit");

	m_HP -= 50;

	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);

	if (m_HP == 0)
	{
		SetActive(false);

	}*/

	if (Dest->GetOwner()->GetPlayerCheck())

	{
		if (m_Monster)
		{
			if (m_BombCount > 0)
			{
				CBomb2* Bomb = m_Scene->CreateObject<CBomb2>("Bomb2");

				Bomb->SetPos(m_Pos.x - 25.f, m_Pos.y - 25.f);
				Bomb->SetDuration(2.f);

				Bomb->AddAnimation("Bomb", true);

				--m_BombCount;

				m_Monster = false;
			}
		}
	}

	else
	{

	}
}

void CBossMonster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_Monster = true;
}

void CBossMonster::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{




}

void CBossMonster::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}