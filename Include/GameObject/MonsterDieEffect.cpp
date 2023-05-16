#include "MonsterDieEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Player.h"
#include "../GameObject/MonsterRealDieEffect.h"


CMonsterDieEffect::CMonsterDieEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CMonsterDieEffect::CMonsterDieEffect(const CMonsterDieEffect& Obj) :
	CGameObject(Obj)
{
}

CMonsterDieEffect::~CMonsterDieEffect()
{

}

bool CMonsterDieEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CMonsterDieEffect>(this, &CMonsterDieEffect::AnimationEnd);

	

	

	return true;
}

void CMonsterDieEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}


}

void CMonsterDieEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMonsterDieEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}



void CMonsterDieEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	CMonsterRealDieEffect* Effect = m_Scene->CreateObject<CMonsterRealDieEffect>("MonsterDie2");

	Effect->SetPivot(0.5f, 0.5f);
	Effect->SetPos(m_Pos.x, m_Pos.y - 15.f);
	Effect->AddAnimation("MonsterDie2", false, 1.f);


}