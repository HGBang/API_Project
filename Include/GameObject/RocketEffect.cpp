#include "RocketEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"


CRocketEffect::CRocketEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CRocketEffect::CRocketEffect(const CRocketEffect& Obj) :
	CGameObject(Obj)
{
}

CRocketEffect::~CRocketEffect()
{
}

bool CRocketEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CRocketEffect>(this, &CRocketEffect::AnimationEnd);

	//m_Damage = 10.f;

	m_PhysicsSimulate = true;

	m_BombCheck = true;

	m_PlayerCheck = false;





	m_MoveSpeed = 150.f;

	return true;
}

void CRocketEffect::Update(float DeltaTime)
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

void CRocketEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CRocketEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}

float CRocketEffect::InflictDamage(float Damage)
{
	return 10.0f;
}

void CRocketEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);
}