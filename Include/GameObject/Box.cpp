#include "Box.h"
#include"Monster.h"
#include"../Scene/Scene.h"
#include "Bullet.h"
#include "../Collision/ColliderBox.h"
#include "../GameManager.h"
#include "Effect.h"
#include "GameObject.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/Text.h"
#include "../Input.h"




CBox::CBox() :
	m_HP(10),
	m_HPMax(10)
{
	SetTypeID<CBox>();
}

CBox::CBox(const CBox& Obj) :
	CCharacter(Obj)

{
}

CBox::~CBox()
{
}



bool CBox::Init()
{
	CGameObject::Init();


	SetPos(300.f, 300.f);
	SetSize(60.f, 50.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Box", TEXT("Box.bmp"));
	SetColorKey(255, 0, 255);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(60.f, 50.f);
	Box->SetCollisionProfile("Box");
	Box->SetCollisionBeginFunction<CBox>(this, &CBox::CollisionBegin);
	Box->SetCollisionEndFunction<CBox>(this, &CBox::CollisionEnd);




	return true;
}

void CBox::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


}

void CBox::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CBox::Render(HDC hDC, float DeltaTime)
{

	CCharacter::Render(hDC, DeltaTime);



}

float CBox::InflictDamage(float Damage)
{

	Damage = CCharacter::InflictDamage(Damage);
	m_HP -= (int)Damage;

	if (m_HP <= 0)
	{
		SetActive(false);
	}

	return Damage;
}

void CBox::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	
	//Dest->GetOwner()->InflictDamage(m_Damage);

	Vector2 DestHitPoint = Dest->GetHitPoint();

	Vector2 DestPos = Dest->GetOwner()->GetPos();
	Vector2 DestSize = Dest->GetOwner()->GetSize();

	Vector2 SrcPos = Src->GetOwner()->GetPos();
	Vector2 SrcSize = Src->GetOwner()->GetSize();

	BoxInfo Player;
	BoxInfo Box;

	Player.LT = DestPos - DestSize / 2.f;
	Player.RB = DestPos + DestSize / 2.f;

	Box.LT = SrcPos - SrcSize / 2.f;
	Box.RB = SrcPos + SrcSize / 2.f;

	float Left = Box.LT.x > Player.LT.x ? Box.LT.x : Player.LT.x;
	float Top = Box.LT.y > Player.LT.y ? Box.LT.y : Player.LT.y;
	float Right = Box.RB.x < Player.RB.x ? Box.RB.x : Player.RB.x;
	float Bottom = Box.RB.y < Player.RB.y ? Box.RB.y : Player.RB.y;

	
    if (DestPos.x > SrcPos.x && GetAsyncKeyState('A') & 0x8000 )
	{
		Dest->GetOwner()->SetPos(DestPos.x + 2.0f, DestPos.y);
	}

    if (DestPos.x < SrcPos.x && GetAsyncKeyState('D') & 0x8000)
	{
		Dest->GetOwner()->SetPos(DestPos.x - 2.0f, DestPos.y);
	}

	 if (DestPos.y > SrcPos.y && GetAsyncKeyState('W') & 0x8000)
	{
		Dest->GetOwner()->SetPos(DestPos.x , DestPos.y + 2.0f);
	}
	
     if(DestPos.y < SrcPos.y && GetAsyncKeyState('S') &0x8000)
	{
		Dest->GetOwner()->SetPos(DestPos.x, DestPos.y - 2.0f);
	}

	


}

void CBox::CollisionEnd(CCollider* Src, CCollider* Dest)
{


}

void CBox::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{


}

void CBox::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}
