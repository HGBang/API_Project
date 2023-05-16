#include "DieEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Player.h"
#include "../GameObject/RealDieEffect.h"


CDieEffect::CDieEffect() :
	m_EffectType(EEffect_Type::Once),
	m_Duration(0.f),
	m_Time(0.f)
{

}

CDieEffect::CDieEffect(const CDieEffect& Obj) :
	CGameObject(Obj)
{
}

CDieEffect::~CDieEffect()
{
	CInput::GetInst()->DeleteBindFunction<CDieEffect>("MoveFront", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CDieEffect>("MoveBack", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CDieEffect>("GunRotation", Input_Type::Push, this);
	CInput::GetInst()->DeleteBindFunction<CDieEffect>("GunRotationInv", Input_Type::Push, this);
}

bool CDieEffect::Init()
{

	// 애니메이션 1개를 무조건 가지고 있게 해준다.

	CreateAnimation();

	SetCurrentAnimationEndFunction<CDieEffect>(this, &CDieEffect::AnimationEnd);

	m_MoveSpeed = 100.f;

	CInput::GetInst()->AddBindFunction<CDieEffect>("MoveFront", Input_Type::Push, this, &CDieEffect::MoveFront);
	CInput::GetInst()->AddBindFunction<CDieEffect>("MoveBack", Input_Type::Push, this, &CDieEffect::MoveBack);
	CInput::GetInst()->AddBindFunction<CDieEffect>("GunRotation", Input_Type::Push, this, &CDieEffect::GunRotation);
	CInput::GetInst()->AddBindFunction<CDieEffect>("GunRotationInv", Input_Type::Push, this, &CDieEffect::GunRotationInv);
	m_PhysicsSimulate = true;
	m_SideWallCheck = true;


	return true;
}

void CDieEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_EffectType == EEffect_Type::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time <= m_Duration)
			SetActive(false);
	}


}

void CDieEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CDieEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);

}



void CDieEffect::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);

	CRealDieEffect* Effect = m_Scene->CreateObject<CRealDieEffect>("PlayerDie3");

	Effect->SetPivot(0.5f, 0.5f);
	Effect->SetPos(m_Pos.x, m_Pos.y - 15.f);
	Effect->AddAnimation("PlayerDie3", false, 1.f);


}

void CDieEffect::MoveFront()
{
	MoveDir(Vector2(0.f, -1.f));
}

void CDieEffect::MoveBack()
{
	MoveDir(Vector2(0.f, 1.f));
}

void CDieEffect::GunRotation()
{
	MoveDir(Vector2(1.f, 0.f));
}

void CDieEffect::GunRotationInv()
{
	MoveDir(Vector2(-1.f, 0.f));
}

