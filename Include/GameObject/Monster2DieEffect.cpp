#include "Monster2DieEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Player.h"
#include "../GameObject/MonsterRealDieEffect.h"
#include "../GameObject/Monster2RealDieEffect.h"



CMonster2DieEffect::CMonster2DieEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CMonster2DieEffect::CMonster2DieEffect(const CMonster2DieEffect& Obj) :
	CGameObject(Obj)
{
}

CMonster2DieEffect::~CMonster2DieEffect()
{

}

bool CMonster2DieEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CMonster2DieEffect>(this, &CMonster2DieEffect::AnimationEnd);





	return true;
}

void CMonster2DieEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}


}

void CMonster2DieEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMonster2DieEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}



void CMonster2DieEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	CMonster2RealDieEffect* Effect = m_Scene->CreateObject<CMonster2RealDieEffect>("Monster2Die2");

	Effect->SetPivot(0.5f, 0.5f);
	Effect->SetPos(m_Pos.x, m_Pos.y - 15.f);
	Effect->AddAnimation("Monster2Die2", false, 1.f);


}