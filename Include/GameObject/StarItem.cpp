#include "StarItem.h"
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



CStarItem::CStarItem() :
	m_ItemTime(0.f)
{
	SetTypeID<CStarItem>();
}

CStarItem::CStarItem(const CStarItem& Obj) :
	CGameObject(Obj),
	m_ItemTime(Obj.m_ItemTime)


{
}

CStarItem::~CStarItem()
{
}



bool CStarItem::Init()
{

	CGameObject::Init();


	m_PlayerCheck = false;


	SetPos(200.f, 400.f);
	//SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Sol", TEXT("Sol.bmp"));
	SetColorKey(255, 0, 255);

	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(50.f, 50.f);
	//Box->SetCollisionBeginFunction<CStarItem>(this, &CStarItem::CollisionBegin);
	//Box->SetCollisionEndFunction<CStarItem>(this, &CStarItem::CollisionEnd);


	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(10.f);
	Circle->SetCollisionProfile("StarItem");
	Circle->SetOffset(0.f, 5.f);
	Circle->SetCollisionBeginFunction<CStarItem>(this, &CStarItem::CollisionBegin);
	Circle->SetCollisionEndFunction<CStarItem>(this, &CStarItem::CollisionEnd);

	return true;
}

void CStarItem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_Time > 20.f)
		SetActive(false);

}

void CStarItem::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CStarItem::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);

	/*Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;*/


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CStarItem::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetOwner()->GetPlayerCheck())
	{
		
		m_Scene->GetSceneResource()->SoundPlay("item");

		if (!Dest->GetOwner()->GetSolSKill())
			Dest->GetOwner()->SetSol(true);

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

void CStarItem::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}