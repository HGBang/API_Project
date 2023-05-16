#include "Player.h"
#include "../Scene/Scene.h"
#include"Bullet.h"
#include "Tornado.h"
#include "AurellionSol.h"
#include"../Input.h"
#include"../GameManager.h"
#include "Talon.h"
#include "TalonM.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "Effect.h"
#include "GameObject.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/Text.h"
#include "Bomb.h"
#include "DieEffect.h"
#include "../Scene/MainScene.h"
#include "BombCount.h"
#include "../Resource/Animation/AnimationManager.h"
#include "PlayerRocket.h"
#include "PowerBomb.h"
#include "Power2Bomb.h"
#include "RocketOn.h"



CPlayer::CPlayer()
{
	SetTypeID<CPlayer>();
}

CPlayer::CPlayer(const CPlayer& Obj) :
	CCharacter(Obj)
{
}

CPlayer::~CPlayer()
{
	CInput::GetInst()->DeleteBindFunction<CPlayer>("MoveFront", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("MoveBack", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("GunRotation", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("GunRotationInv", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Fire", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Skill1", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Skill2", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Talon", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("TalonM", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("BombKey", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Resurrection", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Jump", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("RocketBomb", Input_Type::Down, this);

	
	
}





bool CPlayer::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 200.f;
	m_GunAngle = 0.f;
	m_GunLength = 70.f;

	SetPos(150.f, 550.f);
	//SetSize(85.f, 75.f);
	SetPivot(0.5f, 0.5f);


	m_SolAngle[0] = 0.f;
	m_SolAngle[1] = 120.f;
	m_SolAngle[2] = 240.f;


	m_SolLength = 60.f;
	m_SolRotationSpeed = 500.f;
	m_SolSkillOn = false;

	m_SolLengthMin = 100;
	m_SolLengthMax = 200;
	m_SolSkillTime = 0.f;
	m_SolSkillDir = 1.f;

	SkillCoolDownInfo Info = {};

	Info.CoolDown = 5.f;
	
	m_vecCoolDown.push_back(Info);

	Info.CoolDown = 10.f;

	m_vecCoolDown.push_back(Info);

	m_DeadTime = 0.f;

	m_Dead = false;

	m_Alive = true;

	MoveUpDown = false;
	MoveLeftRight = false;

	m_UpDown = true;

	m_PlayerCheck = true;

	m_BombCount = 2;

	m_BombOK = true;


	m_GetSoul = false;

	m_SoulSkill = false;

	//for (int i = 0; i < 3; ++i)
	//{
	//	m_Sol[i] = m_Scene->CreateObject<CAurellionSol>("Sol");

	//	Vector2 Pos;
	//	Pos.x = m_Pos.x + cosf(DegreeToRadian(m_SolAngle[i])) * m_SolLength;
	//	Pos.y = m_Pos.y + sinf(DegreeToRadian(m_SolAngle[i])) * m_SolLength;

	//	m_Sol[i]->SetPos(m_Pos);

	//}

	m_Soul = false;


	CreateAnimation();
	AddAnimation("PlayerRight");
	AddAnimation("PlayerLeft");
	AddAnimation("PlayerUp");
	AddAnimation("PlayerDown");
	AddAnimation("PlayerDie");
	AddAnimation("PlayerDie1");
	AddAnimation("PlayerDie2");
	AddAnimation("PlayerDie3");
	AddAnimation("PlayerDieFull", false, 2.5f);
	AddAnimation("Alive", false);
	

	//AddAnimation("PlayerRightIdle");
	//AddAnimation("PlayerRightWalk");
	//AddAnimation("PlayerRightAttack", false, 0.3f);
	//AddAnimation("PlayerLeftIdle");
	//AddAnimation("PlayerLeftWalk");
	//AddAnimation("PlayerLeftAttack", false, 0.3f);

	//SetEndFunction<CPlayer>("PlayerRightAttack", this, &CPlayer::AttackEnd);
	//SetEndFunction<CPlayer>("PlayerLeftAttack", this, &CPlayer::AttackEnd);

	//AddNotify<CPlayer>("PlayerRightAttack", 2, this, &CPlayer::Attack);
	//AddNotify<CPlayer>("PlayerLeftAttack", 2, this, &CPlayer::Attack);

	//m_vecSequenceKey[0].push_back("PlayerRightIdle");
	//m_vecSequenceKey[0].push_back("PlayerRightWalk");
	//m_vecSequenceKey[0].push_back("PlayerRightAttack");

	//m_vecSequenceKey[1].push_back("PlayerLeftIdle");
	//m_vecSequenceKey[1].push_back("PlayerLeftWalk");
	//m_vecSequenceKey[1].push_back("PlayerLeftAttack");

	/*AddAnimation("PlayerRightIdle");
	AddAnimation("PlayerRight");
	AddAnimation("PlayerRightAttack", false, 0.3f);
	AddAnimation("PlayerLeftIdle");
	AddAnimation("PlayerLeft");
	AddAnimation("PlayerLeftAttack", false, 0.3f);

	SetEndFunction<CPlayer>("PlayerRightAttack", this, &CPlayer::AttackEnd);
    SetEndFunction<CPlayer>("PlayerLeftAttack", this, &CPlayer::AttackEnd);

	AddNotify<CPlayer>("PlayerRightAttack", 2, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerLeftAttack", 2, this, &CPlayer::Attack);

	m_vecSequenceKey[0].push_back("PlayerRight");
	m_vecSequenceKey[0].push_back("PlayerRight");
    m_vecSequenceKey[0].push_back("PlayerRightAttack");

	m_vecSequenceKey[1].push_back("PlayerLeft");
	m_vecSequenceKey[1].push_back("PlayerLeft");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack");

	m_vecSequenceKey[2].push_back("PlayerUp");
	m_vecSequenceKey[2].push_back("PlayerUp");
	m_vecSequenceKey[2].push_back("PlayerRightAttack");

	m_vecSequenceKey[3].push_back("PlayerDown");
	m_vecSequenceKey[3].push_back("PlayerDown");
	m_vecSequenceKey[3].push_back("PlayerLeftAttack");*/

	m_RealDeadTime = 0.f;


	// 오른쪽 보고 있음.
	m_PlayerDir = 1;

	// 공격중이 아닐때.
	m_Attack = false;

	m_GetRocket = false;

	//충돌체 추가

	//CColliderBox* Box = AddCollider<CColliderBox>("Head");

	//Box->SetExtent(56.f, 42.f);
	//Box->SetOffset(7.f, -52.f);
	//Box->SetCollisionProfile("Player");

	//Box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	//Box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(45.f, 50.f);
	Box->SetOffset(0.f, 0.f);
	Box->SetCollisionProfile("Player");

	Box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	Box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);


	/*CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	

	Circle->SetRadius(50.f);
	Circle->SetCollisionProfile("Player");

	Circle->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	Circle->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);*/


	CInput::GetInst()->AddBindFunction<CPlayer>("MoveFront", Input_Type::Push, this, &CPlayer::MoveFront);
	CInput::GetInst()->AddBindFunction<CPlayer>("MoveBack", Input_Type::Push, this, &CPlayer::MoveBack);
	CInput::GetInst()->AddBindFunction<CPlayer>("GunRotation", Input_Type::Push, this, &CPlayer::GunRotation);
	CInput::GetInst()->AddBindFunction<CPlayer>("GunRotationInv", Input_Type::Push, this, &CPlayer::GunRotationInv);
	CInput::GetInst()->AddBindFunction<CPlayer>("Fire", Input_Type::Down, this, &CPlayer::Fire);
	CInput::GetInst()->AddBindFunction<CPlayer>("Skill1", Input_Type::Down, this, &CPlayer::Skill1);
	CInput::GetInst()->AddBindFunction<CPlayer>("Skill2", Input_Type::Down, this, &CPlayer::Skill2);
	CInput::GetInst()->AddBindFunction<CPlayer>("Talon", Input_Type::Down, this, &CPlayer::Talon);
	CInput::GetInst()->AddBindFunction<CPlayer>("RocketBomb", Input_Type::Down, this, &CPlayer::RocketBomb);
	CInput::GetInst()->AddBindFunction<CPlayer>("BombKey", Input_Type::Down, this, &CPlayer::Bomb);
	CInput::GetInst()->AddBindFunction<CPlayer>("Resurrection",Input_Type::Down, this, &CPlayer::Resurrection);

	

	m_HP = 100000;
	m_HPMax = 100000;

	m_Power1On = false;
	m_Power2On = false;
	m_ShoesOn = false;

	m_NoDie = true;

	m_BossRound = false;

	m_RocketOn = false;

	//m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");
	//m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar, "HPBar", TEXT("CharacterHPBar.bmp"));
	//m_HPBar->GetWidget<CProgressBar>()->SetSize(50.f, 10.f);
	//m_HPBar->SetPos(-20.f, -90.f);

	m_NameBar = CreateWidgetComponent<CText>("NameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("Player"));
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(-25.f, -40.f);

	SetSideWallCheck(true);
	SetPhysicsSimulate(true);
	//SetJumpVelocity(60.f);

	return true;
}

void CPlayer::Update(float DeltaTime)
{

	CCharacter::Update(DeltaTime);

	if (m_PrevPos.y == m_Pos.y)
		MoveUpDown = false;

	if (m_PrevPos.x == m_Pos.x)
		MoveLeftRight = false;

	DeltaTime *= m_TimeScale;


	//if (m_NoDie)
	//{
	//	m_NoDieTime += DELTA_TIME;

	//	m_HP = 100000;

	//	if (m_NoDieTime > 3.f)
	//	{
	//		m_HP = 10;
	//		m_NoDie = false;
	//		m_NoDieTime = 0.f;

	//	}

	//}

	if (m_NoDie)
	{
		m_NoDieTime += DELTA_TIME;

		if(m_NoDieTime > 2.5f)
		{
			m_HP = 50;
			m_NoDie = false;
			m_NoDieTime = 0.f;
		}
	}


	if (m_MoveSpeed > 500.f)
	{
		m_MoveSpeed = 500.f;
	}




	if (m_GetRocket)
	{
		m_RocketTime += DeltaTime;
				

		if (m_RocketTime > 7.5f)
		{
			m_GetRocket = false;
			m_RocketTime = 0.f;
		}
					
	}

	size_t Size = m_vecCoolDown.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecCoolDown[i].CoolDownEnable)
		{
			m_vecCoolDown[i].CoolDown -= DeltaTime;

			if (m_vecCoolDown[i].CoolDown <= 0.f)
				m_vecCoolDown[i].CoolDownEnable = false;
		}
	}


	if (m_Power2On)
	{
		m_Power1On = false;
	}



	m_GunPos.x = m_Pos.x + cosf(DegreeToRadian(m_GunAngle)) * m_GunLength;
	m_GunPos.y = m_Pos.y + sinf(DegreeToRadian(m_GunAngle)) * m_GunLength;


	
	if (m_SolSkillOn)
	{
		m_SolLength += m_SolSkillDir *(m_SolLengthMax - m_SolLengthMin) / 2.f * DeltaTime;

		if (m_SolLength >= m_SolLengthMax)
			m_SolLength = m_SolLengthMax;

		else if (m_SolLength <= m_SolLengthMin)
		{
			m_SolRotationSpeed = 60.f;
			m_SolLength = m_SolLengthMin;
			m_SolSkillOn = false;
		}


		m_SolSkillTime += DeltaTime;
		if (m_SolSkillTime >= 5.f)
		{
			m_SolSkillDir = -1.f;
		}
	}


	if (m_Dead)
	{
		
		SetActive(false);
		m_Alive = false;
		m_PlayerCheck = false;
		m_NameBar->SetActive(false);
		//m_Scene->DeletePlayer();
		m_GetRocket = false;
												
		m_Scene->GetSceneResource()->SoundPlay("boom");

		CDieEffect* Effect = m_Scene->CreateObject<CDieEffect>("PlayerDieFull");
		Effect->SetPivot(0.5f, 0.5f);
		Effect->SetPos(m_Pos.x, m_Pos.y - 25.f);
		Effect->AddAnimation("PlayerDieFull", false, 2.5f);

	}


	if (m_GetSoul)
	{
		SolSkill();
		m_GetSoul = false;
		m_SoulSkill = true;
	}


	if (!m_BombOK)
	{
		m_Time += DELTA_TIME;

		if (m_Time > 1.f)
		{
			m_BombOK = true;
			m_Time = 0.f;
		}
	}


	if (m_Soul)
	{
						
		m_HP = 10000;

			for (int i = 0; i < 3; ++i)
			{

				m_SolAngle[i] += m_SolRotationSpeed * DeltaTime;

				Vector2 Pos;
				Pos.x = m_Pos.x - 20.f + cosf(DegreeToRadian(m_SolAngle[i])) * m_SolLength;
				Pos.y = m_Pos.y - 25.f + sinf(DegreeToRadian(m_SolAngle[i])) * m_SolLength;

				m_Sol[i]->SetPos(Pos);
				
				m_SoulTime += DELTA_TIME;

				if (m_SoulTime > 10.f)
				{
					m_Soul = false;
					m_SoulTime = 0.f;
					m_SoulSkill = false;
					m_HP = 100;
					
				}

				

			}
		
	}
	
}

void CPlayer::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);


	/*if (m_Move.x < 0.f || m_Move.x > 0.f)
	{
		MoveLeftRight = false;
	}

	if (m_Move.y < 0.f || m_Move.y > 0.f)
	{
		MoveUpDown = false;
	}*/





	
	/*if (m_PlayerDir == 1)
	{
		 0일 경우라면 오른쪽으로 이동중 멈췄다는 것이다.
		if (m_Move.x < 0.f)
			m_PlayerDir = -1;
	}

	else
	{
		if (m_Move.x > 0.f)
			m_PlayerDir = 1;
	}

	int	AnimDirIndex = 0;

	if (m_PlayerDir == -1)
		AnimDirIndex = 1;

	if (m_Move.x != 0.f || m_Move.y != 0.f)
	{
		 이동을 할 경우 공격중이더라도 공격을 취소한다.
		m_Attack = false;
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
	}

	else if (!m_Attack)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);*/


}

void CPlayer::Render(HDC hDC,float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

	Vector2 Pos = m_Pos - m_Scene->GetCamera()->GetPos();
	//Vector2 GunPos = m_GunPos - m_Scene->GetCamera()->GetPos();

	//MoveToEx(hDC, (int)Pos.x, (int)Pos.y, nullptr);
	//LineTo(hDC, (int)GunPos.x, (int)GunPos.y);

	


	/*if (m_DeadT)
	{
		CPlayer* Player = m_Scene->CreateObject<CPlayer>("Player");
		m_Scene->SetPlayer(Player);
	}*/


}

float CPlayer::InflictDamage(float Damage)
{
	Damage = CCharacter::InflictDamage(Damage);
	m_HP -= (int)Damage;

	if(m_HP == 0)
	m_Dead = true;
	
	return Damage;

}

void CPlayer::MoveFront()
{
	if (m_Alive)
	{
		if (!MoveLeftRight)
		{

			MoveUpDown = true;
			MoveDir(Vector2(0.f, -1.f));

			m_GunAngle = 270.f;

			//GetPos().Angle(m_Scene->GetPlayer()->GetPos());

			ChangeAnimation("PlayerUp");


		}

	}
	
}


void CPlayer::MoveBack()
{
	if (m_Alive)
	{
		if (!MoveLeftRight)
		{
			MoveUpDown = true;
			MoveDir(Vector2(0.f, 1.f));
			m_GunAngle = 90.f;

			ChangeAnimation("PlayerDown");
		}

	}

}

void CPlayer::GunRotation()
{

	if (m_Alive)
	{
		if (!MoveUpDown)
		{
			MoveDir(Vector2(1.f, 0.f));
			m_GunAngle = 360.f;

			ChangeAnimation("PlayerRight");

			MoveLeftRight = true;
		}
	}
}

void CPlayer::GunRotationInv()
{
	if (m_Alive)
	{
		if (!MoveUpDown)
		{

			MoveDir(Vector2(-1.f, 0.f));
			m_GunAngle = 180.f;

			

			ChangeAnimation("PlayerLeft");

			MoveLeftRight = true;
		}

	}
}

void CPlayer::Fire()
{
	
}


void CPlayer::Skill1()
{
	if (m_vecCoolDown[0].CoolDownEnable)
		return;

	m_vecCoolDown[0].CoolDownEnable = true;
	m_vecCoolDown[0].CoolDown = 5.f;

	CTornado* Bullet = m_Scene->CreateObject<CTornado>("Tornado");

	Bullet->SetAngle(m_GunAngle);

	Bullet->SetPos(m_GunPos);
}

void CPlayer::Skill2()
{

	if (m_vecCoolDown[1].CoolDownEnable)
		return;

	m_vecCoolDown[1].CoolDownEnable = true;
	m_vecCoolDown[1].CoolDown = 10.f;

	m_SolSkillOn = true;

	m_SolRotationSpeed = 180.f;

	m_SolSkillTime = 0.f;

	m_SolSkillDir = 1.f;
}

void CPlayer::Talon()
{
	CTalon* Bomb = m_Scene->CreateObject<CTalon>("Bomb");

	Bomb->SetPos(m_Scene->GetPlayer()->GetPos().x - 25.f, m_Scene->GetPlayer()->GetPos().y + 50.f);

	Bomb->AddAnimation("Bomb", true);
		
}

void CPlayer::TalonM()
{
	CTalonM* Bullet1 = m_Scene->CreateObject<CTalonM>("TalonM");
	CTalonM* Bullet2 = m_Scene->CreateObject<CTalonM>("TalonM");
	CTalonM* Bullet3 = m_Scene->CreateObject<CTalonM>("TalonM");

	Bullet1->SetAngle(0.f);
	Bullet2->SetAngle(120.f);
	Bullet3->SetAngle(240.f);

	Bullet1->SetPos(m_Pos);
	Bullet2->SetPos(m_Pos);
	Bullet3->SetPos(m_Pos);
}

void CPlayer::JumpKey()
{
	Jump();
}

void CPlayer::Bomb()
{
	if (!m_BossRound)
	{
		if (m_BombCount > 0)
		{
			if (m_BombOK)
			{
				if (m_Alive)
				{

					if (m_Power1On)
					{
						CPowerBomb* Bomb = m_Scene->CreateObject<CPowerBomb>("Bomb");

						Bomb->SetPos(m_Scene->GetPlayer()->GetPos().x - 25.f, m_Scene->GetPlayer()->GetPos().y - 25.f);
						Bomb->SetDuration(2.f);

						Bomb->AddAnimation("Bomb", true);

						m_Scene->GetSceneResource()->SoundPlay("Bubble");

						--m_BombCount;

					}

					else if (m_Power2On)
					{
						CPower2Bomb* Bomb = m_Scene->CreateObject<CPower2Bomb>("Bomb");

						Bomb->SetPos(m_Scene->GetPlayer()->GetPos().x - 25.f, m_Scene->GetPlayer()->GetPos().y - 25.f);
						Bomb->SetDuration(2.f);

						Bomb->AddAnimation("Bomb", true);

						m_Scene->GetSceneResource()->SoundPlay("Bubble");

						--m_BombCount;
					}

					else
					{
						CBomb* Bomb = m_Scene->CreateObject<CBomb>("Bomb");

						Bomb->SetPos(m_Scene->GetPlayer()->GetPos().x - 25.f, m_Scene->GetPlayer()->GetPos().y - 25.f);
						Bomb->SetDuration(2.f);

						Bomb->AddAnimation("Bomb", true);

						m_Scene->GetSceneResource()->SoundPlay("Bubble");

						--m_BombCount;
					}


					//Bomb->SetDamage(10.f);
				}
			}

		}
	}
	
}

void CPlayer::Resurrection()
{
	
	m_Soul = true;

	for (int i = 0; i < 3; ++i)
	{
		m_Sol[i] = m_Scene->CreateObject<CAurellionSol>("Sol");

		Vector2 Pos;
		Pos.x = m_Pos.x + cosf(DegreeToRadian(m_SolAngle[i])) * m_SolLength;
		Pos.y = m_Pos.y + sinf(DegreeToRadian(m_SolAngle[i])) * m_SolLength;

		m_Sol[i]->SetPos(m_Pos);

	}


}

void CPlayer::RocketBomb()
{
	if (m_GetRocket)
	{
		   
	
		CPlayerRocket* Bullet = m_Scene->CreateObject<CPlayerRocket>("CPlayerRocket");
		Bullet->SetPos(m_Pos);
		Bullet->SetAngle(m_GunAngle);
				
		
	}
	
}

void CPlayer::SolSkill()
{

	m_Soul = true;

	for (int i = 0; i < 3; ++i)
	{
		m_Sol[i] = m_Scene->CreateObject<CAurellionSol>("Sol");

		Vector2 Pos;
		Pos.x = m_Pos.x + cosf(DegreeToRadian(m_SolAngle[i])) * m_SolLength;
		Pos.y = m_Pos.y + sinf(DegreeToRadian(m_SolAngle[i])) * m_SolLength;

		m_Sol[i]->SetPos(m_Pos);

	}


}

void CPlayer::Dead()
{
	
}

void CPlayer::AttackEnd()
{
	m_Attack = false;
}

void CPlayer::Attack()
{
	CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

	Bullet->SetAngle(m_GunAngle);

	Bullet->SetPos(m_GunPos);

	Bullet->SetDamage(0.f);

	CCollider* BulletCol = Bullet->FindCollider("Body");

	BulletCol->SetCollisionProfile("PlayerAttack");

}

void CPlayer::AddBombCount()
{
	++m_BombCount;
}

void CPlayer::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//m_Scene->GetSceneResource()->SoundPlay("Hit1");

	//m_HP -= 10;

	//m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->SetHP(m_HP / (float)m_HPMax);

	//m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);


	//Dest->GetOwner()->InflictDamage(m_Damage);
		
}

void CPlayer::CollisionEnd(CCollider* Src, CCollider* Dest)
{

}

  