#include "Power1Effect.h"
#include"Effect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "Tile.h"
#include "TileMap.h"


CPower1Effect::CPower1Effect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CPower1Effect::CPower1Effect(const CPower1Effect& Obj) :
	CGameObject(Obj)
{
}

CPower1Effect::~CPower1Effect()
{
}

bool CPower1Effect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CPower1Effect>(this, &CPower1Effect::AnimationEnd);

	m_Damage = 10.f;

	m_PhysicsSimulate = true;

	m_BombCheck = true;

	m_PlayerCheck = false;

	//m_Bomb = true;


	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(35.f, 35.f);
	//Box->SetOffset(20.f, 22.f);
	//Box->SetCollisionProfile("Power1Effect");

	//Box->SetCollisionBeginFunction<CPower1Effect>(this, &CPower1Effect::CollisionBegin);
	//Box->SetCollisionEndFunction<CPower1Effect>(this, &CPower1Effect::CollisionEnd);


	//m_MoveDistance = 100.f;

	//m_Effect = true;

	m_MoveSpeed = 3.f;

	return true;
}

void CPower1Effect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}

	Move(m_Angle);


	m_MoveDistance -= m_MoveSpeed * DeltaTime;

	if (m_MoveDistance <= 0.f)
		SetActive(false);


	if (m_Pos.x < 50.f)
		SetActive(false);

	if (m_Pos.x > 980.f)
		SetActive(false);

	if (m_Pos.y < 40.f)
		SetActive(false);

	if (m_Pos.y > 660)
		SetActive(false);




}

void CPower1Effect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPower1Effect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}

float CPower1Effect::InflictDamage(float Damage)
{
	return 10.0f;
}

void CPower1Effect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}



void CPower1Effect::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->InflictDamage(m_Damage);
}

void CPower1Effect::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
