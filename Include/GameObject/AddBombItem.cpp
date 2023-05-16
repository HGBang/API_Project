#include"AddBombItem.h"
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



CAddBombItem::CAddBombItem() :
	m_ItemTime(0.f)
{
	SetTypeID<CAddBombItem>();
}

CAddBombItem::CAddBombItem(const CAddBombItem& Obj) :
	CGameObject(Obj),
	m_ItemTime(Obj.m_ItemTime)


{
}

CAddBombItem::~CAddBombItem()
{
}



bool CAddBombItem::Init()
{

	CGameObject::Init();



	m_PlayerCheck = false;


	//SetPos(500.f, 500.f);
	//SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("AddBombItem", TEXT("AddBombItem.bmp"));
	SetColorKey(100, 100, 100);

	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(50.f, 50.f);
	//Box->SetCollisionBeginFunction<CAddBombItem>(this, &CAddBombItem::CollisionBegin);
	//Box->SetCollisionEndFunction<CAddBombItem>(this, &CAddBombItem::CollisionEnd);


	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(10.f);
	Circle->SetCollisionProfile("AddBombItem");
	Circle->SetOffset(0.f, 5.f);
	Circle->SetCollisionBeginFunction<CAddBombItem>(this, &CAddBombItem::CollisionBegin);
	Circle->SetCollisionEndFunction<CAddBombItem>(this, &CAddBombItem::CollisionEnd);

	return true;
}

void CAddBombItem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_Time > 20.f)
		SetActive(false);

}

void CAddBombItem::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CAddBombItem::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);

	/*Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;*/


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CAddBombItem::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetOwner()->GetPlayerCheck())
	{

		m_Scene->GetSceneResource()->SoundPlay("item");

		Dest->GetOwner()->SetAddBombCount(1);
		

		SetActive(false);
	}

	else if(Dest->GetOwner()->GetMonsterCheck())
	{
		SetActive(false);
	}

	else if (Dest->GetOwner()->GetSecondMonsterCheck())
	{
		SetActive(false);
	}



}

void CAddBombItem::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}