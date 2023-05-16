#include "Bomb.h"
#include"Effect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "Effect.h"
#include "Bullet.h"
#include "../Scene/SceneResource.h"
#include "../GameObject/CCharacter.h"


CBomb::CBomb() :
	m_EffectType(EEffect_Type::Duration),
	m_Duration(0.f),
	m_Time(0.f)
	
{
	SetTypeID<CBomb>();
}

CBomb::CBomb(const CBomb& Obj) :
	CGameObject(Obj)
{
}

CBomb::~CBomb()
{
}

bool CBomb::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CBomb>(this, &CBomb::AnimationEnd);


	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(50.f, 55.f);
	Box->SetOffset(25.f, 25.f);
	Box->SetCollisionProfile("BoxTile");
	Box->SetCollisionBeginFunction<CBomb>(this, &CBomb::CollisionBegin);
	Box->SetCollisionEndFunction<CBomb>(this, &CBomb::CollisionEnd);
	
	m_MoveSpeed = 0.f;
	m_Angle = 0.f;


	m_PlayerCheck = true;

	m_PhysicsSimulate = true;

	m_SideWallCheck = true;

	return true;
}

void CBomb::Update(float DeltaTime)
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
			BoomDie->SetPos(m_Pos);
			BoomDie->AddAnimation("BoomDie", false, 0.2f);

			SetActive(false);

			CEffect* Effect31 = m_Scene->CreateObject<CEffect>("BombEffect");
			Effect31->SetPivot(0.f, 0.f);
			Effect31->SetDamage(10.f);
			Effect31->SetPos(m_Pos.x, m_Pos.y + 40.f);
			Effect31->AddAnimation("BoomDownEx", false, 0.5f);
			Effect31->SetPhysicsSimulate(true);
			Effect31->SetSideWallCheck(true);
			Effect31->SetAngle(360.f);
					
			

			CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

			Bullet->SetPos(m_Pos.x + 20.f, m_Pos.y + 10.f);
			Bullet->SetAngle(90.f);
			Bullet->SetPhysicsSimulate(true);
			Bullet->SetBomb(true);
			Bullet->SetSideWallCheck(true);
			

			CEffect* Effect1 = m_Scene->CreateObject<CEffect>("BombEffect");
			Effect1->SetPivot(0.f, 0.f);
			Effect1->SetDamage(10.f);
			Effect1->SetPos(m_Pos.x, m_Pos.y - 40.f);
			Effect1->AddAnimation("BoomUpEx", false, 0.3f);
			Effect1->SetPhysicsSimulate(true);
			//Effect1->SetBomb(true);
			Effect1->SetSideWallCheck(true);
			//Effect1->SetAngle(270.f);

			CBullet* Bullet1 = m_Scene->CreateObject<CBullet>("Bullet");

			Bullet1->SetPos(m_Pos.x + 25.f, m_Pos.y + 20.f);
			Bullet1->SetAngle(180.f);
			Bullet1->SetPhysicsSimulate(true);
			Bullet1->SetBomb(true);
			Bullet1->SetSideWallCheck(true);


			CEffect* Effect2 = m_Scene->CreateObject<CEffect>("BombEffect");
			Effect2->SetPivot(0.f, 0.f);
			Effect2->SetDamage(10.f);
			Effect2->SetPos(m_Pos.x + 40.f, m_Pos.y + 3.5f);
			Effect2->AddAnimation("BoomRightEx", false, 0.3f);
			Effect2->SetPhysicsSimulate(true);
			//Effect2->SetBomb(true);
			Effect2->SetSideWallCheck(true);
			//Effect2->SetAngle(360.f);
			//Effect2->SetMoveSpeed(150.f);
		

			CBullet* Bullet2 = m_Scene->CreateObject<CBullet>("Bullet");

			Bullet2->SetPos(m_Pos.x + 20.f, m_Pos.y + 20.f);
			Bullet2->SetAngle(270.f);
			Bullet2->SetPhysicsSimulate(true);
			Bullet2->SetBomb(true);
			Bullet2->SetSideWallCheck(true);

			CEffect* Effect3 = m_Scene->CreateObject<CEffect>("BombEffect");
			Effect3->SetPivot(0.f, 0.f);
			Effect3->SetDamage(10.f);
			Effect3->SetPos(m_Pos.x - 40.f, m_Pos.y +3.5f);
			Effect3->AddAnimation("BoomLeftEx", false, 0.3f);
			Effect3->SetPhysicsSimulate(true);
			//Effect3->SetBomb(true);
			Effect3->SetSideWallCheck(true);
			Effect3->SetAngle(180.f);

			CBullet* Bullet3 = m_Scene->CreateObject<CBullet>("Bullet");

			Bullet3->SetPos(m_Pos.x + 25.f, m_Pos.y + 20.f);
			Bullet3->SetAngle(360.f);
			Bullet3->SetPhysicsSimulate(true);
			Bullet3->SetBomb(true);
			Bullet3->SetSideWallCheck(true);

			if(m_Scene->GetPlayer())
			m_Scene->GetPlayer()->AddBombCount();
			
			else
			{

			}
			
		}
	
	}

	Move(m_Angle);
	

	//m_Scene->GetMonster()->AddBombCount();
}

void CBomb::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBomb::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}

void CBomb::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetOwner()->GetBombCheck())
	{
		m_Time = 3.f;
	}
		
	Dest->GetOwner()->SetBombOK(false);

	//if (Dest->GetOwner()->GetPlayerCheck())
	//{

	//	//Dest->GetOwner()->SetBombOK(false);

	//	Vector2 DestHitPoint = Dest->GetHitPoint();

	//	Vector2 DestPos = Dest->GetOwner()->GetPos();
	//	Vector2 DestSize = Dest->GetOwner()->GetSize();

	//	Vector2 SrcPos = Src->GetOwner()->GetPos();
	//	Vector2 SrcSize = Src->GetOwner()->GetSize();

	//	BoxInfo Player;
	//	BoxInfo Box;

	//	Player.LT = DestPos - DestSize / 2.f;
	//	Player.RB = DestPos + DestSize / 2.f;

	//	Box.LT = SrcPos - SrcSize / 2.f;
	//	Box.RB = SrcPos + SrcSize / 2.f;

	//	float Left = Box.LT.x > Player.LT.x ? Box.LT.x : Player.LT.x;
	//	float Top = Box.LT.y > Player.LT.y ? Box.LT.y : Player.LT.y;
	//	float Right = Box.RB.x < Player.RB.x ? Box.RB.x : Player.RB.x;
	//	float Bottom = Box.RB.y < Player.RB.y ? Box.RB.y : Player.RB.y;


	//	if (DestPos.x > SrcPos.x && GetAsyncKeyState('A') & 0x8000)
	//	{
	//		Dest->GetOwner()->SetPos(DestPos.x + 3.0f, DestPos.y);
	//	}

	//	if (DestPos.x < SrcPos.x && GetAsyncKeyState('D') & 0x8000)
	//	{
	//		Dest->GetOwner()->SetPos(DestPos.x - 3.0f, DestPos.y);
	//	}

	//	if (DestPos.y > SrcPos.y && GetAsyncKeyState('W') & 0x8000)
	//	{
	//		Dest->GetOwner()->SetPos(DestPos.x, DestPos.y + 3.0f);
	//	}

	//	if (DestPos.y < SrcPos.y && GetAsyncKeyState('S') & 0x8000)
	//	{
	//		Dest->GetOwner()->SetPos(DestPos.x, DestPos.y - 3.0f);
	//	}
	//}

	//else
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


		if(Dest->GetOwner()->GetShoesOn())
		{
			if (DestPos.x > SrcPos.x && GetAsyncKeyState('A') & 0x8000)
			{
				Dest->GetOwner()->SetPos(DestPos.x + 3.0f, DestPos.y);
				Src->GetOwner()->SetMoveSpeed(500.f);
				Src->GetOwner()->SetAngle(180.f);
			}

			if (DestPos.x < SrcPos.x && GetAsyncKeyState('D') & 0x8000)
			{
				Dest->GetOwner()->SetPos(DestPos.x - 3.0f, DestPos.y);
				Src->GetOwner()->SetMoveSpeed(500.f);
				Src->GetOwner()->SetAngle(360.f);
			}

			if (DestPos.y > SrcPos.y && GetAsyncKeyState('W') & 0x8000)
			{
				Dest->GetOwner()->SetPos(DestPos.x, DestPos.y + 3.0f);
				Src->GetOwner()->SetMoveSpeed(500.f);
				Src->GetOwner()->SetAngle(270.f);
			}

			if (DestPos.y < SrcPos.y && GetAsyncKeyState('S') & 0x8000)
			{
				Dest->GetOwner()->SetPos(DestPos.x, DestPos.y - 3.0f);
				Src->GetOwner()->SetMoveSpeed(500.f);
				Src->GetOwner()->SetAngle(90.f);
			}
		}

		else
		{
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


	}


}

void CBomb::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->SetBombOK(true);
}

void CBomb::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	
}
