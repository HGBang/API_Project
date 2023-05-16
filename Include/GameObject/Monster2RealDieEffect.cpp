#include "Monster2RealDieEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Player.h"


CMonster2RealDieEffect::CMonster2RealDieEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CMonster2RealDieEffect::CMonster2RealDieEffect(const CMonster2RealDieEffect& Obj) :
	CGameObject(Obj)
{
}

CMonster2RealDieEffect::~CMonster2RealDieEffect()
{
}

bool CMonster2RealDieEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CMonster2RealDieEffect>(this, &CMonster2RealDieEffect::AnimationEnd);





	return true;
}

void CMonster2RealDieEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}


}

void CMonster2RealDieEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMonster2RealDieEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}



void CMonster2RealDieEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	m_Scene->DeleteSecondMonster();

}