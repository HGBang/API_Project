#include"Talon.h"
#include"../Scene/Scene.h"
#include"../Collision/ColliderCircle.h"
#include"Effect.h"
#include"../Scene/SceneResource.h"
#include "Bomb.h"





CTalon::CTalon()
{
	SetTypeID<CTalon>();
}

CTalon::CTalon(const CTalon& Obj) :
	CGameObject(Obj),
	m_MoveSpeed(Obj.m_MoveSpeed),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance),
	m_FireTime(Obj.m_FireTime)

{
}

CTalon::~CTalon()
{
}



bool CTalon::Init()
{
	
	m_PhysicsSimulate = true;

	CreateAnimation();

	SetCurrentAnimationEndFunction<CTalon>(this, &CTalon::AnimationEnd);

	m_MoveSpeed = 200.f;
	
	return true;
}

void CTalon::Update(float DeltaTime)
{
	
	m_Pos.y = m_Pos.y *  DeltaTime * m_MoveSpeed;

	CGameObject::Update(DeltaTime);


}

void CTalon::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	


}

void CTalon::CollisionBegin(CCollider* Src, CCollider* Dest)
{

}

void CTalon::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CTalon::AnimationEnd()
{
	if (m_EffectType == EEffect_Type::Once)
		SetActive(false);


	

}
