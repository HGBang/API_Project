#include "MonsterBomb.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include"../Collision/ColliderCircle.h"
#include"MonsterEffect.h"



CMonsterBomb::CMonsterBomb() :
	m_Damage(0.f)
{
	SetTypeID<CMonsterBomb>();
}

CMonsterBomb::CMonsterBomb(const CMonsterBomb& Obj) :
	CGameObject(Obj),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance)

{
}

CMonsterBomb::~CMonsterBomb()
{
}



bool CMonsterBomb::Init()
{


	//SetCurrentAnimationEndFunction<CMonsterBomb>(this, &CMonsterBomb::AnimationEnd);

	CGameObject::Init();

	CreateAnimation();

	AddAnimation("Bomb");

	m_MoveSpeed = 650.f;
	m_Distance = 2000.f;
	m_Angle = 180.f;

	m_FireTime = 0.f;

	m_PlayerCheck = false;

	m_Damage = 10;


	//SetPos(900.f, 100.f);
	SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("PBullet", TEXT("PBullet.bmp"));
	//SetColorKey(255, 0, 255);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetCollisionProfile("MonsterBomb");
	Box->SetExtent(30.f, 30.f);
	Box->SetCollisionBeginFunction<CMonsterBomb>(this, &CMonsterBomb::CollisionBegin);
	Box->SetCollisionEndFunction<CMonsterBomb>(this, &CMonsterBomb::CollisionEnd);


	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	//Circle->SetRadius(25.f);
	//Circle->SetCollisionProfile("Monster");

	//Circle->SetCollisionBeginFunction<CMonsterBomb>(this, &CMonsterBomb::CollisionBegin);
	//Circle->SetCollisionEndFunction<CMonsterBomb>(this, &CMonsterBomb::CollisionEnd);

	return true;
}

void CMonsterBomb::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(m_Angle);

	m_Distance -= m_MoveSpeed * DeltaTime;

	if (m_Distance <= 0.f)
		SetActive(false);

	if(m_Pos.x < 90.f)
		SetActive(false);

	if(m_Pos.x > 980.f)
		SetActive(false);

	if(m_Pos.y < 60.f)
		SetActive(false);

	if (m_Pos.y > 650)
		SetActive(false);


}

void CMonsterBomb::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMonsterBomb::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;





}

void CMonsterBomb::CollisionBegin(CCollider* Src, CCollider* Dest)
{


	if (Dest->GetOwner()->GetPlayerCheck())
	{
		SetActive(false);

		Dest->GetOwner()->InflictDamage(m_Damage);
		//Vector2 Player = m_Scene->GetPlayer()->GetPos();
		//Vector2 Monster = m_Scene->GetMonster()->GetPos();

		CMonsterEffect* BoomDie = m_Scene->CreateObject<CMonsterEffect>("BombEffect");
		BoomDie->SetPivot(0.f, 0.f);
		BoomDie->SetPos(m_Pos - 10.f);
		BoomDie->AddAnimation("BoomDie", false, 0.2f);

		CMonsterEffect* Effect = m_Scene->CreateObject<CMonsterEffect>("BombEffect");
		Effect->SetPivot(0.f, 0.f);
		Effect->SetDamage(10.f);
		Effect->SetPos(m_Pos.x - 10.f, m_Pos.y + 30.f);
		Effect->AddAnimation("BoomDownEx", false, 0.3f);
		Effect->SetPhysicsSimulate(false);

		CMonsterEffect* Effect1 = m_Scene->CreateObject<CMonsterEffect>("BombEffect");
		Effect1->SetPivot(0.f, 0.f);
		Effect1->SetDamage(10.f);
		Effect1->SetPos(m_Pos.x - 10.f, m_Pos.y - 50.f);
		Effect1->AddAnimation("BoomUpEx", false, 0.3f);
		Effect1->SetPhysicsSimulate(false);

		CMonsterEffect* Effect2 = m_Scene->CreateObject<CMonsterEffect>("BombEffect");
		Effect2->SetPivot(0.f, 0.f);
		Effect2->SetDamage(10.f);
		Effect2->SetPos(m_Pos.x + 30.f, m_Pos.y - 10.f);
		Effect2->AddAnimation("BoomRightEx", false, 0.3f);
		Effect2->SetPhysicsSimulate(false);

		CMonsterEffect* Effect3 = m_Scene->CreateObject<CMonsterEffect>("BombEffect");
		Effect3->SetPivot(0.f, 0.f);
		Effect3->SetDamage(10.f);
		Effect3->SetPos(m_Pos.x - 50.f, m_Pos.y - 10.f);
		Effect3->AddAnimation("BoomLeftEx", false, 0.3f);
		Effect3->SetPhysicsSimulate(false);
	}


	
}

void CMonsterBomb::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}

void CMonsterBomb::AnimationEnd()
{
	
		//SetActive(false);

}
