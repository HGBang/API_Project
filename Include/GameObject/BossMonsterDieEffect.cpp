#include "BossMonsterDieEffect.h"
#include "Monster2DieEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Player.h"
#include "BossMonsterDie2Effect.h"


CBossMonsterDieEffect::CBossMonsterDieEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CBossMonsterDieEffect::CBossMonsterDieEffect(const CBossMonsterDieEffect& Obj) :
	CGameObject(Obj)
{
}

CBossMonsterDieEffect::~CBossMonsterDieEffect()
{

}

bool CBossMonsterDieEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CBossMonsterDieEffect>(this, &CBossMonsterDieEffect::AnimationEnd);





	return true;
}

void CBossMonsterDieEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}


}

void CBossMonsterDieEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossMonsterDieEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}



void CBossMonsterDieEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	CBossMonsterDie2Effect* Effect = m_Scene->CreateObject<CBossMonsterDie2Effect>("BossDie2");

	Effect->SetPivot(0.5f, 0.5f);
	Effect->SetPos(m_Pos.x, m_Pos.y - 15.f);
	Effect->AddAnimation("BossDie2", false, 1.f);


}