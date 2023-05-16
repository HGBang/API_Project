#include "MonsterRealDieEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Player.h"


CMonsterRealDieEffect::CMonsterRealDieEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CMonsterRealDieEffect::CMonsterRealDieEffect(const CMonsterRealDieEffect& Obj) :
	CGameObject(Obj)
{
}

CMonsterRealDieEffect::~CMonsterRealDieEffect()
{
}

bool CMonsterRealDieEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CMonsterRealDieEffect>(this, &CMonsterRealDieEffect::AnimationEnd);





	return true;
}

void CMonsterRealDieEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}


}

void CMonsterRealDieEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMonsterRealDieEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}



void CMonsterRealDieEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	m_Scene->DeleteMonster();

}