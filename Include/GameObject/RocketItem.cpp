#include "RocketItem.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include"../Collision/ColliderCircle.h"
#include "Player.h"
#include "../Scene/SceneResource.h"
#include "RocketOn.h"



CRocketItem::CRocketItem() :
	m_ItemTime(0.f)
{
	SetTypeID<CRocketItem>();
}

CRocketItem::CRocketItem(const CRocketItem& Obj) :
	CGameObject(Obj),
	m_ItemTime(Obj.m_ItemTime)


{
}

CRocketItem::~CRocketItem()
{
}



bool CRocketItem::Init()
{

	CGameObject::Init();


	m_PlayerCheck = false;


	SetPos(200.f, 200.f);
	//SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Rocket", TEXT("Rocket.bmp"));
	SetColorKey(100, 100, 100);

	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(50.f, 50.f);
	//Box->SetCollisionBeginFunction<CRocketItem>(this, &CRocketItem::CollisionBegin);
	//Box->SetCollisionEndFunction<CRocketItem>(this, &CRocketItem::CollisionEnd);


	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(10.f);
	Circle->SetCollisionProfile("RocketItem");
	Circle->SetOffset(0.f, 5.f);
	Circle->SetCollisionBeginFunction<CRocketItem>(this, &CRocketItem::CollisionBegin);
	Circle->SetCollisionEndFunction<CRocketItem>(this, &CRocketItem::CollisionEnd);

	return true;
}

void CRocketItem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_Time > 20.f)
		SetActive(false);

}

void CRocketItem::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CRocketItem::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);

	/*Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;*/


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CRocketItem::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetOwner()->GetPlayerCheck())
	{
		m_Scene->GetSceneResource()->SoundPlay("item");
		Dest->GetOwner()->SetRocket(true);
		SetActive(false);

		CRocketOn* RocketOn = m_Scene->CreateObject<CRocketOn>("RocketOn");
		RocketOn->SetPos(m_Scene->GetPlayer()->GetPos());


	}

	else if (Dest->GetOwner()->GetMonsterCheck())
	{
		SetActive(false);
	}

	else if (Dest->GetOwner()->GetSecondMonsterCheck())
	{
		SetActive(false);
	}


}

void CRocketItem::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}