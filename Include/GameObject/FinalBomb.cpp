#include "FinalBomb.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include"../Collision/ColliderCircle.h"
#include"MonsterEffect.h"
#include "MonsterBomb.h"



CFinalBomb::CFinalBomb() :
	m_Damage(0.f)
{
	SetTypeID<CFinalBomb>();
}

CFinalBomb::CFinalBomb(const CFinalBomb& Obj) :
	CGameObject(Obj),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance)

{
}

CFinalBomb::~CFinalBomb()
{
}



bool CFinalBomb::Init()
{


	//SetCurrentAnimationEndFunction<CFinalBomb>(this, &CFinalBomb::AnimationEnd);

	CGameObject::Init();

	CreateAnimation();

	AddAnimation("Bomb");

	//m_MoveSpeed = 400.f;
	m_Distance = 2000.f;
	m_Angle = 180.f;

	m_FireTime = 0.f;

	m_PlayerCheck = false;

	m_Damage = 10;

	m_Number = 0;

	

	//SetPos(900.f, 100.f);
	SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("PBullet", TEXT("PBullet.bmp"));
	//SetColorKey(255, 0, 255);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetCollisionProfile("MonsterBomb");
	Box->SetExtent(30.f, 30.f);
	Box->SetCollisionBeginFunction<CFinalBomb>(this, &CFinalBomb::CollisionBegin);
	Box->SetCollisionEndFunction<CFinalBomb>(this, &CFinalBomb::CollisionEnd);


	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	//Circle->SetRadius(25.f);
	//Circle->SetCollisionProfile("Monster");

	//Circle->SetCollisionBeginFunction<CFinalBomb>(this, &CFinalBomb::CollisionBegin);
	//Circle->SetCollisionEndFunction<CFinalBomb>(this, &CFinalBomb::CollisionEnd);

	return true;
}

void CFinalBomb::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(m_Angle);

	m_FireTime += DELTA_TIME;

	if (m_FireTime > 15.f)
	{
		SetActive(false);
	}



	m_Distance -= m_MoveSpeed * DeltaTime;

	m_Time += DeltaTime;
	if (m_Round)
	{
		if (m_Time > 0.05f)
		{

			CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
			Bullet->SetPos(m_Pos);
			Bullet->SetAngle(90.f + (float)m_Number);
			Bullet->SetDistance(230.f);

			CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
			Bullet1->SetPos(m_Pos);
			Bullet1->SetAngle(180.f + (float)m_Number);
			Bullet1->SetDistance(230.f);

			CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
			Bullet2->SetPos(m_Pos);
			Bullet2->SetAngle(270.f + (float)m_Number);
			Bullet2->SetDistance(230.f);

			CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
			Bullet3->SetPos(m_Pos);
			Bullet3->SetAngle(360.f + (float)m_Number);
			Bullet3->SetDistance(230.f);

			--m_Number;
			--m_Number;
			//--m_Number;

			m_Time = 0.f;

		}
	}

	if (!m_Round)
	{
		if (m_Time > 0.05f)
		{

			CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
			Bullet->SetPos(m_Pos);
			Bullet->SetAngle(90.f + (float)m_Number);
			Bullet->SetDistance(230.f);

			CMonsterBomb* Bullet1 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
			Bullet1->SetPos(m_Pos);
			Bullet1->SetAngle(180.f + (float)m_Number);
			Bullet1->SetDistance(230.f);

			CMonsterBomb* Bullet2 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
			Bullet2->SetPos(m_Pos);
			Bullet2->SetAngle(270.f + (float)m_Number);
			Bullet2->SetDistance(230.f);

			CMonsterBomb* Bullet3 = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
			Bullet3->SetPos(m_Pos);
			Bullet3->SetAngle(360.f + (float)m_Number);
			Bullet3->SetDistance(230.f);

			++m_Number;
			++m_Number;
			++m_Number;

			m_Time = 0.f;

		}
	}

	//if (m_Distance <= 1600.f)
	//{
	//	SetActive(false);
	//	BombSkill();
	//	

	//	if (m_Distance <= 1000.f)
	//	{
	//		SetActive(false);
	//		BombSkill();
	//	}
	//}

	if (m_Pos.x < 90.f)
		SetActive(false);

	if (m_Pos.x > 980.f)
		SetActive(false);

	if (m_Pos.y < 60.f)
		SetActive(false);

	if (m_Pos.y > 650)
		SetActive(false);


}

void CFinalBomb::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CFinalBomb::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;





}

void CFinalBomb::CollisionBegin(CCollider* Src, CCollider* Dest)
{





}

void CFinalBomb::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}

void CFinalBomb::AnimationEnd()
{

	//SetActive(false);

}

void CFinalBomb::BombSkill()
{
	for (int i = 0; i < 36; ++i)
	{
		CMonsterBomb* Bullet = m_Scene->CreateObject<CMonsterBomb>("CMonsterBomb");
		Bullet->SetPos(m_Pos);
		Bullet->SetAngle(10.f * i);

	}
}
