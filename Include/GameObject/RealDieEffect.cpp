#include "RealDieEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Player.h"


CRealDieEffect::CRealDieEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CRealDieEffect::CRealDieEffect(const CRealDieEffect& Obj) :
	CGameObject(Obj)
{
}

CRealDieEffect::~CRealDieEffect()
{
}

bool CRealDieEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CRealDieEffect>(this, &CRealDieEffect::AnimationEnd);

	



	return true;
}

void CRealDieEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}


}

void CRealDieEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CRealDieEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}



void CRealDieEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	m_Scene->DeletePlayer();

}