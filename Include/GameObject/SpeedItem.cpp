#include "SpeedItem.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include"../Collision/ColliderCircle.h"
#include "../Scene/SceneResource.h"



CSpeedItem::CSpeedItem() :
	m_ItemTime(0.f)
{
	SetTypeID<CSpeedItem>();
}

CSpeedItem::CSpeedItem(const CSpeedItem& Obj) :
	CGameObject(Obj),
	m_ItemTime(Obj.m_ItemTime)
	

{
}

CSpeedItem::~CSpeedItem()
{
}



bool CSpeedItem::Init()
{

	CGameObject::Init();

	

	m_PlayerCheck = false;


	//SetPos(500.f, 500.f);
	//SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("SpeedItem", TEXT("SpeedItem.bmp"));
	SetColorKey(100, 100, 100);

	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(50.f, 50.f);
	//Box->SetCollisionBeginFunction<CSpeedItem>(this, &CSpeedItem::CollisionBegin);
	//Box->SetCollisionEndFunction<CSpeedItem>(this, &CSpeedItem::CollisionEnd);


	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(10.f);
	Circle->SetCollisionProfile("SpeedItem");
	Circle->SetOffset(0.f, 5.f);

	Circle->SetCollisionBeginFunction<CSpeedItem>(this, &CSpeedItem::CollisionBegin);
	Circle->SetCollisionEndFunction<CSpeedItem>(this, &CSpeedItem::CollisionEnd);

	return true;
}

void CSpeedItem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_Time > 20.f)
		SetActive(false);

}

void CSpeedItem::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CSpeedItem::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);

	/*Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;*/


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CSpeedItem::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetOwner()->GetPlayerCheck())
	{
		m_Scene->GetSceneResource()->SoundPlay("item");

		Dest->GetOwner()->SetMoveSpeed(50.f);

		SetActive(false);
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

void CSpeedItem::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}
