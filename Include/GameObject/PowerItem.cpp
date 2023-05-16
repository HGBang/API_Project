#include "PowerItem.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include"../Collision/ColliderCircle.h"
#include "../Scene/SceneResource.h"



CPowerItem::CPowerItem() :
	m_ItemTime(0.f)
{
	SetTypeID<CPowerItem>();
}

CPowerItem::CPowerItem(const CPowerItem& Obj) :
	CGameObject(Obj),
	m_ItemTime(Obj.m_ItemTime)


{
}

CPowerItem::~CPowerItem()
{
}



bool CPowerItem::Init()
{

	CGameObject::Init();



	m_PlayerCheck = false;


	//SetPos(200.f, 200.f);
	//SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("PowerItem", TEXT("Poweritem.bmp"));
	SetColorKey(100, 100, 100);

	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(50.f, 50.f);
	//Box->SetCollisionBeginFunction<CPowerItem>(this, &CPowerItem::CollisionBegin);
	//Box->SetCollisionEndFunction<CPowerItem>(this, &CPowerItem::CollisionEnd);


	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(10.f);
	Circle->SetCollisionProfile("PowerItem");
	Circle->SetOffset(0.f, 5.f);

	Circle->SetCollisionBeginFunction<CPowerItem>(this, &CPowerItem::CollisionBegin);
	Circle->SetCollisionEndFunction<CPowerItem>(this, &CPowerItem::CollisionEnd);

	return true;
}

void CPowerItem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_Time > 20.f)
		SetActive(false);

}

void CPowerItem::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPowerItem::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);

	/*Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;*/


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CPowerItem::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	if (Dest->GetOwner()->GetPlayerCheck())
	{
		if (Dest->GetOwner()->GetPower1())
		{
			Dest->GetOwner()->SetPower2(true);

			m_Scene->GetSceneResource()->SoundPlay("item");

			SetActive(false);
		}

		if (Dest->GetOwner()->GetPower2())
		{
			m_Scene->GetSceneResource()->SoundPlay("item");

			SetActive(false);
		}

		else
		{
			m_Scene->GetSceneResource()->SoundPlay("item");

			Dest->GetOwner()->SetPower1(true);

			SetActive(false);
		}
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

void CPowerItem::CollisionEnd(CCollider* Src, CCollider* Dest)
{



}
