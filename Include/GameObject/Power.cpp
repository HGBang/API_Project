#include "Power.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include"../Collision/ColliderCircle.h"



CPower::CPower() :
	m_Damage(0.f)
{
	SetTypeID<CPower>();
}

CPower::CPower(const CPower& Obj) :
	CGameObject(Obj),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance)

{
}

CPower::~CPower()
{
}



bool CPower::Init()
{

	CGameObject::Init();

	m_MoveSpeed = 700.f;
	m_Distance = 90.f;
	m_Angle = 180.f;

	m_FireTime = 0.f;

	m_PlayerCheck = false;



	//SetPos(900.f, 100.f);
	SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("PBullet", TEXT("PBullet.bmp"));
	//SetColorKey(255, 0, 255);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetCollisionProfile("Power");
	Box->SetExtent(20.f, 20.f);
	Box->SetCollisionBeginFunction<CPower>(this, &CPower::CollisionBegin);
	Box->SetCollisionEndFunction<CPower>(this, &CPower::CollisionEnd);


	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	//Circle->SetRadius(25.f);
	//Circle->SetCollisionProfile("Monster");

	//Circle->SetCollisionBeginFunction<CPower>(this, &CPower::CollisionBegin);
	//Circle->SetCollisionEndFunction<CPower>(this, &CPower::CollisionEnd);


	//CreateAnimation();
	//SetCurrentAnimationEndFunction<CPower>(this, &CPower::AnimationEnd);

	//m_Bomb = true;


	return true;
}

void CPower::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(m_Angle);

	m_Distance -= m_MoveSpeed * DeltaTime;



	if (m_Distance <= 0.f)
		SetActive(false);
}

void CPower::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPower::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CPower::AnimationEnd()
{
}

void CPower::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetOwner()->GetPlayerCheck())
	{
		SetActive(false);

		Dest->GetOwner()->InflictDamage(m_Damage);
	}

	if (Dest->GetOwner()->GetMonsterCheck())
	{
		SetActive(false);

		Dest->GetOwner()->InflictDamage(m_Damage);
	}
}


void CPower::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	
	//SetActive(false);


}