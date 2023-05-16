#include "PowerBomb.h"
#include"Effect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "Effect.h"
#include "Bullet.h"
#include "../Scene/SceneResource.h"
#include "../GameObject/CCharacter.h"
#include "Power.h"
#include "Power1Effect.h"


CPowerBomb::CPowerBomb() :
	m_EffectType(EEffect_Type::Duration),
	m_Duration(0.f),
	m_Time(0.f)

{
	SetTypeID<CPowerBomb>();
}

CPowerBomb::CPowerBomb(const CPowerBomb& Obj) :
	CGameObject(Obj)
{
}

CPowerBomb::~CPowerBomb()
{
}

bool CPowerBomb::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CPowerBomb>(this, &CPowerBomb::AnimationEnd);


	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(50.f, 55.f);
	Box->SetOffset(25.f, 25.f);
	Box->SetCollisionProfile("BoxTile");
	Box->SetCollisionBeginFunction<CPowerBomb>(this, &CPowerBomb::CollisionBegin);
	Box->SetCollisionEndFunction<CPowerBomb>(this, &CPowerBomb::CollisionEnd);


	m_PlayerCheck = false;

	m_PhysicsSimulate = true;

	return true;
}

void CPowerBomb::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Duration <= m_Time)
		{

			m_Scene->GetSceneResource()->SoundPlay("Fire");

			CEffect* BoomDie = m_Scene->CreateObject<CEffect>("BombEffect");
			BoomDie->SetPivot(0.f, 0.f);
			BoomDie->SetPos(m_Pos +5.f);
			BoomDie->AddAnimation("BoomDie", false, 0.3f);

			SetActive(false);
					
			CPower1Effect* Effect1 = m_Scene->CreateObject<CPower1Effect>("BombEffect");
			Effect1->SetPivot(0.f, 0.f);
			Effect1->SetDamage(10.f);
			Effect1->SetPos(m_Pos.x, m_Pos.y - 30.f);
			Effect1->AddAnimation("BoomDownPower1", false, 0.4f);
			Effect1->SetPhysicsSimulate(true);
			Effect1->SetSideWallCheck(true);
			Effect1->SetBomb(true);
			Effect1->SetAngle(90.f);
			Effect1->SetMoveSpeed(800.f);
			Effect1->SetDistance(80.f);

			CPower1Effect* Effect2 = m_Scene->CreateObject<CPower1Effect>("BombEffect");
			Effect2->SetPivot(0.f, 0.f);
			Effect2->SetDamage(10.f);
			Effect2->SetPos(m_Pos.x, m_Pos.y - 30.f);
			Effect2->AddAnimation("BoomUpPower1", false, 0.3f);
			Effect2->SetPhysicsSimulate(true);
			Effect2->SetBomb(true);
			Effect2->SetSideWallCheck(true);
		    Effect2->SetAngle(270.f);
			Effect2->SetMoveSpeed(500.f);
			Effect2->SetDistance(70.f);
					
			CPower1Effect* Effect3 = m_Scene->CreateObject<CPower1Effect>("BombEffect");
			Effect3->SetPivot(0.f, 0.f);
			Effect3->SetDamage(10.f);
			Effect3->SetPos(m_Pos.x - 10.f , m_Pos.y + 5.5f);
			Effect3->AddAnimation("BoomRightPower1", false, 0.3f);
			Effect3->SetPhysicsSimulate(true);
			Effect3->SetBomb(true);
			Effect3->SetSideWallCheck(true);
			Effect3->SetAngle(360.f);
			Effect3->SetMoveSpeed(500.f);
			Effect3->SetDistance(70.f);
			
			CPower1Effect* Effect4 = m_Scene->CreateObject<CPower1Effect>("BombEffect");
			Effect4->SetPivot(0.f, 0.f);
			Effect4->SetDamage(10.f);
			Effect4->SetPos(m_Pos.x - 30.f, m_Pos.y + 5.5f);
			Effect4->AddAnimation("BoomLeftPower1", false, 0.3f);
			Effect4->SetPhysicsSimulate(true);
			Effect4->SetBomb(true);
			Effect4->SetSideWallCheck(true);
			Effect4->SetAngle(180.f);
			Effect4->SetMoveSpeed(500.f);
			Effect4->SetDistance(70.f);

	
			CPower* Bullet = m_Scene->CreateObject<CPower>("Bullet");

			Bullet->SetPos(m_Pos.x + 20.f, m_Pos.y + 10.f);
			Bullet->SetAngle(90.f);
			Bullet->SetDamage(10.f);
			Bullet->SetPhysicsSimulate(true);
			//Bullet->SetBomb(true);
			Bullet->SetSideWallCheck(true);



			CPower* Bullet1 = m_Scene->CreateObject<CPower>("Bullet");

			Bullet1->SetPos(m_Pos.x + 25.f, m_Pos.y + 20.f);
			Bullet1->SetDamage(10.f);
			Bullet1->SetAngle(180.f);
			Bullet1->SetPhysicsSimulate(true);
			//Bullet1->SetBomb(true);
			Bullet1->SetSideWallCheck(true);


			CPower* Bullet2 = m_Scene->CreateObject<CPower>("Bullet");

			Bullet2->SetPos(m_Pos.x + 20.f, m_Pos.y + 20.f);
			Bullet2->SetDamage(10.f);
			Bullet2->SetAngle(270.f);
			Bullet2->SetPhysicsSimulate(true);
			//Bullet2->SetBomb(true);
			Bullet2->SetSideWallCheck(true);

	

			CPower* Bullet3 = m_Scene->CreateObject<CPower>("Bullet");
			Bullet3->SetDamage(10.f);
			Bullet3->SetPos(m_Pos.x + 25.f, m_Pos.y + 20.f);
			Bullet3->SetAngle(360.f);
			Bullet3->SetPhysicsSimulate(true);
			//Bullet3->SetBomb(true);
			Bullet3->SetSideWallCheck(true);




			if (m_Scene->GetPlayer())
				m_Scene->GetPlayer()->AddBombCount();

			else
			{

			}

		}

	}



	//m_Scene->GetMonster()->AddBombCount();
}

void CPowerBomb::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPowerBomb::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}

void CPowerBomb::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetOwner()->GetBombCheck())
	{
		m_Time = 3.f;
	}

	Dest->GetOwner()->SetBombOK(false);

	if (Dest->GetOwner()->GetPlayerCheck())
	{

		//Dest->GetOwner()->SetBombOK(false);

		Vector2 DestHitPoint = Dest->GetHitPoint();

		Vector2 DestPos = Dest->GetOwner()->GetPos();
		Vector2 DestSize = Dest->GetOwner()->GetSize();

		Vector2 SrcPos = Src->GetOwner()->GetPos();
		Vector2 SrcSize = Src->GetOwner()->GetSize();

		BoxInfo Player;
		BoxInfo Box;

		Player.LT = DestPos - DestSize / 2.f;
		Player.RB = DestPos + DestSize / 2.f;

		Box.LT = SrcPos - SrcSize / 2.f;
		Box.RB = SrcPos + SrcSize / 2.f;

		float Left = Box.LT.x > Player.LT.x ? Box.LT.x : Player.LT.x;
		float Top = Box.LT.y > Player.LT.y ? Box.LT.y : Player.LT.y;
		float Right = Box.RB.x < Player.RB.x ? Box.RB.x : Player.RB.x;
		float Bottom = Box.RB.y < Player.RB.y ? Box.RB.y : Player.RB.y;


		if (DestPos.x > SrcPos.x && GetAsyncKeyState('A') & 0x8000)
		{
			Dest->GetOwner()->SetPos(DestPos.x + 3.0f, DestPos.y);
		}

		if (DestPos.x < SrcPos.x && GetAsyncKeyState('D') & 0x8000)
		{
			Dest->GetOwner()->SetPos(DestPos.x - 3.0f, DestPos.y);
		}

		if (DestPos.y > SrcPos.y && GetAsyncKeyState('W') & 0x8000)
		{
			Dest->GetOwner()->SetPos(DestPos.x, DestPos.y + 3.0f);
		}

		if (DestPos.y < SrcPos.y && GetAsyncKeyState('S') & 0x8000)
		{
			Dest->GetOwner()->SetPos(DestPos.x, DestPos.y - 3.0f);
		}
	}

	else
		return;


}

void CPowerBomb::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->SetBombOK(true);
}

void CPowerBomb::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);


}