#include "MonsterEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"


CMonsterEffect::CMonsterEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CMonsterEffect::CMonsterEffect(const CMonsterEffect& Obj) :
	CGameObject(Obj)
{
}

CMonsterEffect::~CMonsterEffect()
{
}

bool CMonsterEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CMonsterEffect>(this, &CMonsterEffect::AnimationEnd);

	m_Damage = 10.f;

	m_PhysicsSimulate = true;

	m_BombCheck = true;

	m_PlayerCheck = false;

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(35.f, 35.f);
	Box->SetOffset(20.f, 22.f);
	Box->SetCollisionProfile("MonsterEffect");

	Box->SetCollisionBeginFunction<CMonsterEffect>(this, &CMonsterEffect::CollisionBegin);
	Box->SetCollisionEndFunction<CMonsterEffect>(this, &CMonsterEffect::CollisionEnd);



	m_MoveSpeed = 150.f;

	return true;
}

void CMonsterEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}

	if (m_Pos.x < 50.f)
		SetActive(false);

	if (m_Pos.x > 980.f)
		SetActive(false);

	if (m_Pos.y < 40.f)
		SetActive(false);

	if (m_Pos.y > 660)
		SetActive(false);

}

void CMonsterEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMonsterEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}

float CMonsterEffect::InflictDamage(float Damage)
{
	return 10.0f;
}

void CMonsterEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}



void CMonsterEffect::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetOwner()->GetPlayerCheck())
	{
		Dest->GetOwner()->InflictDamage(m_Damage);
	}

}

void CMonsterEffect::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}