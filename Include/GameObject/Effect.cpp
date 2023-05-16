#include"Effect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "Tile.h"
#include "TileMap.h"


CEffect::CEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{
	
}

CEffect::CEffect(const CEffect& Obj) :
	CGameObject(Obj)
{
}

CEffect::~CEffect()
{
}

bool CEffect::Init()
{
	
	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CEffect>(this, &CEffect::AnimationEnd);

	m_Damage = 10.f;
	
	m_PhysicsSimulate = true;

	m_BombCheck = true;

	m_PlayerCheck = false;

	

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(35.f, 35.f);
	Box->SetOffset(20.f,22.f);
	Box->SetCollisionProfile("Effect");

	Box->SetCollisionBeginFunction<CEffect>(this, &CEffect::CollisionBegin);
	Box->SetCollisionEndFunction<CEffect>(this, &CEffect::CollisionEnd);

	
	//m_MoveDistance = 100.f;

	//m_Effect = true;
	
	//m_MoveSpeed = 3.f;

	return true;
}

void CEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}

	//Move(m_Angle);


	//m_MoveDistance -= m_MoveSpeed * DeltaTime;

	//if (m_MoveDistance <= 0.f)
	//	SetActive(false);


	if (m_Pos.x < 50.f)
		SetActive(false);

	if (m_Pos.x > 980.f)
		SetActive(false);

	if (m_Pos.y < 40.f)
		SetActive(false);

	if (m_Pos.y > 660)
		SetActive(false);
	
	


}

void CEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC , DeltaTime);
	
}

float CEffect::InflictDamage(float Damage)
{
	return 10.0f;
}

void CEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}



void CEffect::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->InflictDamage(m_Damage);
}

void CEffect::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
