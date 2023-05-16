#include "Barrier.h"
#include"Effect.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Bullet.h"
#include "../Scene/SceneResource.h"
#include "../GameObject/CCharacter.h"


CBarrier::CBarrier()
{
	SetTypeID<CBarrier>();
}

CBarrier::CBarrier(const CBarrier& Obj)
{
}

CBarrier::~CBarrier()
{
}

bool CBarrier::Init()
{
	//SetTexture("Barrier", TEXT("Barrier.bmp"));
	//SetColorKey(100, 100, 100);

	CreateAnimation();
	AddAnimation("Barrier", true , 0.1f);



	SetPos(100.f, 100.f);

	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(100.f);
	Circle->SetCollisionProfile("Barrier");
	Circle->SetOffset(0.f, 5.f);
	Circle->SetCollisionBeginFunction<CBarrier>(this, &CBarrier::CollisionBegin);
	Circle->SetCollisionEndFunction<CBarrier>(this, &CBarrier::CollisionEnd);



	return true;
}

void CBarrier::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_Time > 10.5f)
	{
		SetActive(false);
		
	}




}

void CBarrier::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBarrier::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CBarrier::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetOwner()->GetPlayerCheck())
	{

	}

	else
		Dest->GetOwner()->SetActive(false);


}

void CBarrier::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
