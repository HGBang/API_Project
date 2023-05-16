#include "PlayerRocket.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include "../Collision/ColliderCircle.h"
#include "MonsterEffect.h"
#include "../Scene/SceneResource.h"
#include "RocketEffect.h"



CPlayerRocket::CPlayerRocket() :
	m_Damage(0.f)
{
	SetTypeID<CPlayerRocket>();
}

CPlayerRocket::CPlayerRocket(const CPlayerRocket& Obj) :
	CGameObject(Obj),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance)

{
}

CPlayerRocket::~CPlayerRocket()
{
}



bool CPlayerRocket::Init()
{


	//SetCurrentAnimationEndFunction<CPlayerRocket>(this, &CPlayerRocket::AnimationEnd);

	CGameObject::Init();

	CreateAnimation();

	AddAnimation("RocketBomb");

	m_MoveSpeed = 700.f;
	m_Distance = 2000.f;
	m_Angle = 180.f;

	m_FireTime = 0.f;

	m_PlayerCheck = false;

	m_Damage = 10;

	m_Rocket = true;

	//SetPos(900.f, 100.f);
	SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("PBullet", TEXT("PBullet.bmp"));
	//SetColorKey(255, 0, 255);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetCollisionProfile("PlayerRocket");
	Box->SetExtent(30.f, 30.f);
	Box->SetCollisionBeginFunction<CPlayerRocket>(this, &CPlayerRocket::CollisionBegin);
	Box->SetCollisionEndFunction<CPlayerRocket>(this, &CPlayerRocket::CollisionEnd);


	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	//Circle->SetRadius(25.f);
	//Circle->SetCollisionProfile("Monster");

	//Circle->SetCollisionBeginFunction<CPlayerRocket>(this, &CPlayerRocket::CollisionBegin);
	//Circle->SetCollisionEndFunction<CPlayerRocket>(this, &CPlayerRocket::CollisionEnd);

	return true;
}

void CPlayerRocket::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(m_Angle);

	m_Distance -= m_MoveSpeed * DeltaTime;

	if (m_Distance <= 0.f)
		SetActive(false);

	if (m_Pos.x < 90.f)
		SetActive(false);

	if (m_Pos.x > 980.f)
		SetActive(false);

	if (m_Pos.y < 60.f)
		SetActive(false);

	if (m_Pos.y > 650)
		SetActive(false);


}

void CPlayerRocket::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPlayerRocket::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;





}

void CPlayerRocket::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if(Dest->GetOwner()->GetPlayerCheck())
	{ 
	}

	else if (Dest->GetOwner()->GetRocketCheck())
	{

	}

	else
	{
		SetActive(false);

		Dest->GetOwner()->InflictDamage(m_Damage);
		//Vector2 Player = m_Scene->GetPlayer()->GetPos();
		//Vector2 Monster = m_Scene->GetMonster()->GetPos();

		m_Scene->GetSceneResource()->SoundPlay("Fire");

		CRocketEffect* BoomDie = m_Scene->CreateObject<CRocketEffect>("BombEffect");
		BoomDie->SetPivot(0.f, 0.f);
		BoomDie->SetPos(m_Pos.x -15.f , m_Pos.y - 15.f);
		BoomDie->AddAnimation("BoomDie", false, 0.2f);

		//SetActive(false);

		CRocketEffect* Effect = m_Scene->CreateObject<CRocketEffect>("BombEffect");
		Effect->SetPivot(0.f, 0.f);
		//Effect->SetDamage(10.f);
		Effect->SetPos(m_Pos.x -15.f , m_Pos.y + 25.f);
		Effect->AddAnimation("BoomDownEx", false, 0.3f);
		Effect->SetPhysicsSimulate(true);

		CRocketEffect* Effect1 = m_Scene->CreateObject<CRocketEffect>("BombEffect");
		Effect1->SetPivot(0.f, 0.f);
		//Effect1->SetDamage(10.f);
		Effect1->SetPos(m_Pos.x - 15.f , m_Pos.y - 55.f);
		Effect1->AddAnimation("BoomUpEx", false, 0.3f);
		Effect1->SetPhysicsSimulate(true);

		CRocketEffect* Effect2 = m_Scene->CreateObject<CRocketEffect>("BombEffect");
		Effect2->SetPivot(0.f, 0.f);
		//Effect2->SetDamage(10.f);
		Effect2->SetPos(m_Pos.x + 25.f, m_Pos.y - 15.f);
		Effect2->AddAnimation("BoomRightEx", false, 0.3f);
		Effect2->SetPhysicsSimulate(true);

		CRocketEffect* Effect3 = m_Scene->CreateObject<CRocketEffect>("BombEffect");
		Effect3->SetPivot(0.f, 0.f);
		//Effect3->SetDamage(10.f);
		Effect3->SetPos(m_Pos.x - 55.f, m_Pos.y - 15.f);
		Effect3->AddAnimation("BoomLeftEx", false, 0.3f);
		Effect3->SetPhysicsSimulate(true);

	}



}

void CPlayerRocket::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}

void CPlayerRocket::AnimationEnd()
{

	//SetActive(false);

}