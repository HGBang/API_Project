#include "FinalBoss.h"
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
#include "AngelNpc.h"
#include "../Scene/SceneManager.h"
#include "Angre.h"
#include "BossFinalBomb.h"
#include "../Input.h"
#include"../Scene/GameClearScene.h"
#include "FinalCut.h"
#include "FinalBomb.h"



CFinalBoss::CFinalBoss() :
	m_HP(500),
	m_HPMax(500)
{
	SetTypeID<CFinalBoss>();
}


CFinalBoss::CFinalBoss(const CFinalBoss& Obj)
{
}

CFinalBoss::~CFinalBoss()
{
}

bool CFinalBoss::Init()
{

	CGameObject::Init();

	SetPos(530.f, 340.f);
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("Marid", true, 3.f);

	m_Pizza1Bullet = 20;
	m_Pizza2Bullet = 20;
	m_Pizza3Bullet = 20;
	m_Pizza4Bullet = 20;

	m_PizzaSkillOn = false;

	m_Pizza1On = true;
	m_Pizza2On = false;
	m_Pizza3On = false;
	m_Pizza4On = false;

	m_DieSkillOn = false;
	m_DieOn = false;


	m_DieCount = 15;


	m_CrossSkillOn = true;

	m_CrossAngle = 0;

	m_Clear = false;

	m_TonadoSkillOn = false;

	m_FinalCut = true;

	m_FinalAttackOn = true;

	return true;
}

void CFinalBoss::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


	
		if (m_CrossSkillOn)
		{
			m_CrossSkillTime += DELTA_TIME;



			if (m_CrossSkillTime > 2.f)
			{

				m_CrossTime += DELTA_TIME;


				if (m_CrossTime > 0.1f)
				{

					CBossCrossBomb* Bullet = m_Scene->CreateObject<CBossCrossBomb>("BossCrossBomb");
					Bullet->SetAngle(150.f + m_CrossAngle);
					Bullet->SetPos(m_Pos);
					Bullet->SetMoveSpeed(550.f);

					CBossCrossBomb* Bullet1 = m_Scene->CreateObject<CBossCrossBomb>("BossCrossBomb");
					Bullet1->SetAngle(270.f + m_CrossAngle);
					Bullet1->SetPos(m_Pos);
					Bullet1->SetMoveSpeed(550.f);

					CBossCrossBomb* Bullet2 = m_Scene->CreateObject<CBossCrossBomb>("BossCrossBomb");
					Bullet2->SetAngle(390.f + m_CrossAngle);
					Bullet2->SetPos(m_Pos);
					Bullet2->SetMoveSpeed(550.f);

					if (m_CrossSkillTime < 13.f)
					{
						++m_CrossAngle;
						++m_CrossAngle;
						++m_CrossAngle;
					}

					else
					{
						--m_CrossAngle;
						--m_CrossAngle;
						--m_CrossAngle;
					}


					m_CrossTime = 0.f;
				}


				m_FinalBombTime += DELTA_TIME;

				if (m_FinalBombTime > 3.f)
				{

					CBossFinalBomb* Bullet = m_Scene->CreateObject<CBossFinalBomb>("FinalBomb");
					Bullet->SetPos(m_Pos);


					m_FinalBombTime = 0.f;
				}




			}

			if (m_CrossSkillTime > 25.f)
			{
				m_CrossSkillOn = false;
				m_PizzaSkillOn = true;
			}

		}


		if (m_PizzaSkillOn)
		{

			m_PizzaTime += DELTA_TIME;


			if (m_PizzaTime > 3.f)
			{
				if (m_Pizza1On)
				{
					m_Pizza1Time += DELTA_TIME;

					if (m_Pizza1Time > 0.1f && m_Pizza1On)
					{
						PizzaSkill1();
						m_Pizza1Time = 0.f;
						--m_Pizza1Bullet;

						if (m_Pizza1Bullet == 0)
						{
							m_Pizza1On = false;
							m_Pizza2On = true;
						}
					}
				}


				if (m_Pizza2On)
				{
					m_PizzaCoolTime += DELTA_TIME;

					if (m_PizzaCoolTime > 0.7f)
					{
						m_Pizza2Time += DELTA_TIME;

						if (m_Pizza2Time > 0.1f && m_Pizza2On)
						{
							PizzaSkill2();
							m_Pizza2Time = 0.f;
							--m_Pizza2Bullet;

							if (m_Pizza2Bullet == 0)
							{
								m_Pizza2On = false;
								m_Pizza3On = true;
								m_PizzaCoolTime = 0.f;
							}
						}
					}
				}

				if (m_Pizza3On)
				{
					m_PizzaCoolTime += DELTA_TIME;

					if (m_PizzaCoolTime > 0.7f)
					{

						m_Pizza3Time += DELTA_TIME;

						if (m_Pizza3Time > 0.1f && m_Pizza3On)
						{
							PizzaSkill3();
							m_Pizza3Time = 0.f;
							--m_Pizza3Bullet;

							if (m_Pizza3Bullet == 0)
							{

								m_Pizza3On = false;
								m_Pizza4On = true;
								m_PizzaCoolTime = 0.f;

							}
						}

					}
				}

				if (m_Pizza4On)
				{
					m_PizzaCoolTime += DELTA_TIME;

					if (m_PizzaCoolTime > 0.7f)
					{

						m_Pizza4Time += DELTA_TIME;

						if (m_Pizza4Time > 0.1f && m_Pizza4On)
						{
							PizzaSkill4();
							m_Pizza4Time = 0.f;
							--m_Pizza4Bullet;

							if (m_Pizza4Bullet == 0)
							{

								m_Pizza4On = false;
								m_TonadoSkillOn = true;

								//m_DieSkillOn = true;
								m_PizzaCoolTime = 0.f;

							}
						}

					}
				}


			}
		}


		if (m_TonadoSkillOn)
		{
			m_TonadoSkillTime += DELTA_TIME;

			if (m_FinalCut)
			{
				CFinalCut* FinalCut = m_Scene->CreateObject<CFinalCut>("FinalCut");
				FinalCut->SetPos(-400.f, 600.f);

				m_Scene->GetSceneResource()->SoundPlay("Final");
				m_FinalCut = false;

			}
			if (m_TonadoSkillTime > 2.f && m_FinalAttackOn)
			{
				CFinalBomb* Bomb = m_Scene->CreateObject<CFinalBomb>("FinalBomb");
				Bomb->SetPos(290.f, 510.f);
				//Bomb->SetMoveSpeed(40.f);
				//Bomb->SetAngle(360.f);
				Bomb->SetRound(true);


				CFinalBomb* Bomb1 = m_Scene->CreateObject<CFinalBomb>("FinalBomb");
				Bomb1->SetPos(290.f, 180.f);
				//Bomb1->SetMoveSpeed(40.f);
				Bomb1->SetAngle(90.f);
				Bomb1->SetNumber(50);


				CFinalBomb* Bomb2 = m_Scene->CreateObject<CFinalBomb>("FinalBomb");
				Bomb2->SetPos(780.f, 510.f);
				//Bomb2->SetMoveSpeed(40.f);
				//Bomb2->SetAngle(270.f);
				Bomb2->SetNumber(90);
				Bomb2->SetRound(true);


				CFinalBomb* Bomb3 = m_Scene->CreateObject<CFinalBomb>("FinalBomb");
				Bomb3->SetPos(780.f, 180.f);
				//Bomb3->SetMoveSpeed(40.f);
				//Bomb3->SetAngle(180.f);
				Bomb3->SetNumber(130);
				Bomb3->SetRound(false);

				m_FinalAttackOn = false;

			}

			if (m_TonadoSkillTime > 15.f)
			{
				m_TonadoSkillOn = false;
				m_DieSkillOn = true;
			}



		}





		if (m_DieSkillOn)
		{
			m_DieSkillTime += DELTA_TIME;


			if (m_DieSkillTime > 5.f)
			{
				/*CAngelNpc* m_AngelNpc = m_Scene->CreateObject<CAngelNpc>("Angle");

				m_AngelNpc->SetPos(210.f, 480.f);*/



				m_DieSkillTime = 0.f;
				m_DieSkillOn = false;
				m_DieOn = true;
			}

		}

		if (m_DieOn)
		{
			m_DieOnTime += DELTA_TIME;

			CAngre* Angre = m_Scene->CreateObject<CAngre>("Angre");
			Angre->SetPos(m_Pos.x, m_Pos.y - 120);

			CAngre* Angre1 = m_Scene->CreateObject<CAngre>("Angre");
			Angre1->SetPos(m_Pos.x + 70, m_Pos.y - 110);

			CAngre* Angre2 = m_Scene->CreateObject<CAngre>("Angre");
			Angre2->SetPos(m_Pos.x - 70, m_Pos.y - 110);



			if (m_DieOnTime > 3.5f)
			{
				m_DieTime += DELTA_TIME;

				Angre->SetActive(false);
				Angre1->SetActive(false);
				Angre2->SetActive(false);

				if (m_Scene->GetPlayer())
				{
					if (m_DieTime > 0.5f)
					{
						CBossMonsterBomb* Bullet = m_Scene->CreateObject<CBossMonsterBomb>("CBossMonsterBomb");


						//CCollider* BulletCol = Bullet->FindCollider("Body");

						//BulletCol->SetCollisionProfile("MonsterAttack");

						float	BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
							(1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

						Bullet->SetPos(m_Pos);
						Bullet->SetDamage(10.f);


						// 플레이어 방향으로 나갈 각도를 구한다.
						float Angle = Bullet->GetPos().Angle(m_Scene->GetPlayer()->GetPos());

						Bullet->SetAngle(Angle);

						m_DieTime = 0.f;
						--m_DieCount;

					}

					if (m_DieCount == 0)
					{
						m_DieOn = false;
						m_Scene->DeleteAngelNpc();
						m_Clear = true;
					}
				}
			}
		}

		if (!m_DieOn)
		{
			m_Time += DELTA_TIME;

			if (m_Time > 2.f)
			{
				m_Scene->DeleteAngelNpc();
				m_Time = 0.f;
			}
		}


		if (m_DieCount == 0)
		{
			m_ClearTime += DELTA_TIME;

			if (m_ClearTime > 4.5f)
			{
				SetActive(false);
				m_Scene->DeleteFinalBoss();

				CInput::GetInst()->ClearCallback();
				CSceneManager::GetInst()->CreateScene<CGameClearScene>();
				m_ClearTime = 0.f;
			}
		}


	}


void CFinalBoss::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CFinalBoss::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CFinalBoss::InflictDamage(float Damage)
{
	return 0.0f;
}

void CFinalBoss::PizzaSkill1()
{

	for (int i = 0; i < 27; ++i)
	{
		CMonsterBomb* Bomb = m_Scene->CreateObject<CMonsterBomb>("Pizza");
		Bomb->SetAngle(140.f + (i * 10));
		Bomb->SetPos(m_Pos);
		Bomb->SetMoveSpeed(500.f);

	}

}

void CFinalBoss::PizzaSkill2()
{
	for (int i = 0; i < 27; ++i)
	{
		CMonsterBomb* Bomb = m_Scene->CreateObject<CMonsterBomb>("Pizza");
		Bomb->SetAngle(230.f + (i * 10));
		Bomb->SetPos(m_Pos);
		Bomb->SetMoveSpeed(500.f);
	}

}

void CFinalBoss::PizzaSkill3()
{

	for (int i = 0; i < 27; ++i)
	{
		CMonsterBomb* Bomb = m_Scene->CreateObject<CMonsterBomb>("Pizza");
		Bomb->SetAngle(320.f + (i * 10));
		Bomb->SetPos(m_Pos);
		Bomb->SetMoveSpeed(500.f);

	}
}

void CFinalBoss::PizzaSkill4()
{

	for (int i = 0; i < 27; ++i)
	{
		CMonsterBomb* Bomb = m_Scene->CreateObject<CMonsterBomb>("Pizza");
		Bomb->SetAngle(410.f + (i * 10));
		Bomb->SetPos(m_Pos);
		Bomb->SetMoveSpeed(500.f);

	}
}
