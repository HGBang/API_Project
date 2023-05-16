#include "ShoesItem.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include"../Collision/ColliderCircle.h"
#include "../Scene/SceneResource.h"



CShoesItem::CShoesItem() :
	m_ItemTime(0.f)
{
	SetTypeID<CShoesItem>();
}

CShoesItem::CShoesItem(const CShoesItem& Obj) :
	CGameObject(Obj),
	m_ItemTime(Obj.m_ItemTime)


{
}

CShoesItem::~CShoesItem()
{
}



bool CShoesItem::Init()
{

	CGameObject::Init();



	m_PlayerCheck = false;


	SetPos(200.f, 200.f);
	//SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("ShoesItem", TEXT("Shoesitem.bmp"));
	SetColorKey(100, 100, 100);

	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(50.f, 50.f);
	//Box->SetCollisionBeginFunction<CShoesItem>(this, &CShoesItem::CollisionBegin);
	//Box->SetCollisionEndFunction<CShoesItem>(this, &CShoesItem::CollisionEnd);


	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(10.f);
	Circle->SetCollisionProfile("ShoesItem");
	Circle->SetOffset(0.f, 5.f);

	Circle->SetCollisionBeginFunction<CShoesItem>(this, &CShoesItem::CollisionBegin);
	Circle->SetCollisionEndFunction<CShoesItem>(this, &CShoesItem::CollisionEnd);

	return true;
}

void CShoesItem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_Time > 20.f)
		SetActive(false);

}

void CShoesItem::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CShoesItem::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);

	/*Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;*/


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CShoesItem::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetOwner()->GetPlayerCheck())
	{
		m_Scene->GetSceneResource()->SoundPlay("item");

		Dest->GetOwner()->SetShoesOn(true);
		

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

void CShoesItem::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}