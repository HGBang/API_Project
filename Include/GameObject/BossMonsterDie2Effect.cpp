#include "BossMonsterDie2Effect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Player.h"


CBossMonsterDie2Effect::CBossMonsterDie2Effect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CBossMonsterDie2Effect::CBossMonsterDie2Effect(const CBossMonsterDie2Effect& Obj) :
	CGameObject(Obj)
{
}

CBossMonsterDie2Effect::~CBossMonsterDie2Effect()
{
}

bool CBossMonsterDie2Effect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CBossMonsterDie2Effect>(this, &CBossMonsterDie2Effect::AnimationEnd);





	return true;
}

void CBossMonsterDie2Effect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}


}

void CBossMonsterDie2Effect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossMonsterDie2Effect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}



void CBossMonsterDie2Effect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	m_Scene->DeleteBossMonster();

}