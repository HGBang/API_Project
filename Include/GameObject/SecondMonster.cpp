#include "SecondMonster.h"
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
#include "MonsterDieEffect.h"
#include "MonsterRealDieEffect.h"
#include "Monster2DieEffect.h"
#include "Monster2RealDieEffect.h"
#include <time.h>




CSecondMonster::CSecondMonster() :
	m_HP(50),
	m_HPMax(50)
{
	SetTypeID<CSecondMonster>();
}

CSecondMonster::CSecondMonster(const CSecondMonster& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir),
	m_FireTime(Obj.m_FireTime),
	m_FireCount(Obj.m_FireCount)
{
}

CSecondMonster::~CSecondMonster()
{
}



bool CSecondMonster::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 250.f;
	m_FireTime = 0.f;
	m_Dir = Vector2(0.f, 1.f);
	m_FireCount = 0;

	m_Monster = false;
	m_SecondMonster = true;
	SetSideWallCheck(true);
	SetPhysicsSimulate(true);
	m_DirLR = -1.f;
	m_StartMonster = true;
	m_Stop = false;

	//SetPos(500.f, 100.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("Monster", TEXT("teemo.bmp"));
	//SetColorKey(255, 0, 255);

	CreateAnimation();
	AddAnimation("Monster2Left");
	AddAnimation("Monster2Right");
	AddAnimation("Monster2Up");
	AddAnimation("Monster2Down");

	m_SecondMonsterCheck = true;


	m_BombCount = 1;

	m_PlayerCheck = false;

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(50.f, 50.f);
	Box->SetCollisionProfile("SecondMonster");
	Box->SetCollisionBeginFunction<CSecondMonster>(this, &CSecondMonster::CollisionBegin);
	Box->SetCollisionEndFunction<CSecondMonster>(this, &CSecondMonster::CollisionEnd);


	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	//Circle->SetRadius(50.f);
	//Circle->SetCollisionProfile("Monster");

	//Circle->SetCollisionBeginFunction<CSecondMonster>(this, &CSecondMonster::CollisionBegin);
	//Circle->SetCollisionEndFunction<CSecondMonster>(this, &CSecondMonster::CollisionEnd);

	//Circle->SetMouseCollisionBeginFunction<CSecondMonster>(this, &CSecondMonster::CollisionMouseBegin);
	//Circle->SetMouseCollisionEndFunction<CSecondMonster>(this, &CSecondMonster::CollisionMouseEnd);



	//m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");
	//m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar, "HPBar", TEXT("CharacterHPBar.bmp"));
	//m_HPBar->GetWidget<CProgressBar>()->SetSize(50.f, 10.f);
	//m_HPBar->SetPos(-25.f, -35.f);


	m_NameBar = CreateWidgetComponent<CText>("NameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("EliteMonster"));
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(-40.f, -45.f);



	return true;
}

void CSecondMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


	m_Pos.x += m_DirLR * DELTA_TIME * m_MoveSpeed;

	m_Pos.y += m_DirUP * DELTA_TIME * m_MoveSpeed;

	if (m_Move.x < 0.f)
		ChangeAnimation("Monster2Left");

	if (m_Move.x > 0.f)
		ChangeAnimation("Monster2Right");

	if (m_Move.y > 0.f)
		ChangeAnimation("Monster2Down");

	if (m_Move.y < 0.f)
		ChangeAnimation("Monster2Up");

	m_MoveTime += DeltaTime;


	if (m_MoveTime > 1.5f)
	{

		srand((int)time(0));
		rand();

		unsigned int i = (int)rand() % 4;

		if (i == 0)
		{
			SetDirLR(1.f);
			SetDirUP(0.f);
			m_MoveTime = 0.f;
		}

		if (i == 1)
		{
			SetDirLR(-1.f);
			SetDirUP(0.f);
			m_MoveTime = 0.f;
		}

		if (i == 2)
		{
			SetDirLR(0.f);
			SetDirUP(1.f);
			m_MoveTime = 0.f;
		}

		if (i == 3)
		{
			SetDirLR(0.f);
			SetDirUP(-1.f);
			m_MoveTime = 0.f;
		}

	}




	m_FireTime += DeltaTime;

	if (m_FireTime >= 10.f)
	{
		if (m_Scene->GetPlayer())
		{
			CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CSecondMonsterBomb");

			float	BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
				(1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

			Bullet->SetPos(m_Pos);
			Bullet->SetDamage(10.f);
						
			float Angle = Bullet->GetPos().Angle(m_Scene->GetPlayer()->GetPos());
			Bullet->SetAngle(Angle);

			m_FireTime = 0.f;
		}
	}

	m_Time += DELTA_TIME;

	if (m_Time > 2.f)
	{
		CBomb2* Bomb = m_Scene->CreateObject<CBomb2>("MonsterAttack");
		Bomb->AddAnimation("Bomb", true);
		Bomb->SetPhysicsSimulate(true);
		Bomb->SetSideWallCheck(true);
		Bomb->SetBomb(true);
		Bomb->SetPos(m_Pos - 25.f);
		Bomb->SetDuration(2.f);

		m_Time = 0.f;
	}


	if (m_BombCount == 0)
	{
		m_Time += DELTA_TIME;

		if (m_Time > 2.f)
		{
			m_BombCount = 1;

			m_Time = 0.f;
		}
	}



}

void CSecondMonster::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CSecondMonster::Render(HDC hDC, float DeltaTime)
{

	CCharacter::Render(hDC, DeltaTime);

	//Rectangle(hDC, 0, 100, 0, 100);
}

float CSecondMonster::InflictDamage(float Damage)
{

	Damage = CCharacter::InflictDamage(Damage);
	m_HP -= (int)Damage;
	//m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);

	if (m_HP <= 0)
	{
		SetActive(false);

		m_Scene->GetSceneResource()->SoundPlay("boom");

		CMonster2DieEffect* Effect = m_Scene->CreateObject<CMonster2DieEffect>("Monster2Die1");
		Effect->SetPivot(0.5f, 0.5f);
		Effect->SetPos(m_Pos.x, m_Pos.y - 25.f);
		Effect->AddAnimation("Monster2Die1", false, 2.5f);


	}

	return Damage;
}

void CSecondMonster::AddBombCount()
{
	++m_BombCount;
}

void CSecondMonster::CollisionBegin(CCollider* Src, CCollider* Dest)
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

void CSecondMonster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_Monster = true;
}

void CSecondMonster::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{




}

void CSecondMonster::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}