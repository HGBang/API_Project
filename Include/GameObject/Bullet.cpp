
#include"Bullet.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameInfo.h"
#include "Effect.h"
#include "../GameManager.h"
#include"../Collision/ColliderCircle.h"



CBullet::CBullet() :
	m_Damage(0.f)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& Obj) :
	CGameObject(Obj),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance)
	
{
}

CBullet::~CBullet()
{
}



bool CBullet::Init()
{
	
	CGameObject::Init();

	m_MoveSpeed = 1000.f;
	m_Distance = 50.f;
	m_Angle = 180.f;

	m_FireTime = 0.f;

	m_PlayerCheck = false;
	

	//SetPos(900.f, 100.f);
	SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("PBullet", TEXT("PBullet.bmp"));
	//SetColorKey(255, 0, 255);
	
	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(50.f, 50.f);
	//Box->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
	//Box->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);


	//CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	//Circle->SetRadius(25.f);
	//Circle->SetCollisionProfile("Monster");

	//Circle->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
	//Circle->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);


	/*CreateAnimation();
	AddAnimation("BoomDownPower1",false);
	AddAnimation("BoomUpEx", false);
	AddAnimation("BoomLeftEx", false);
	AddAnimation("BoomRightEx", false);*/



	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(m_Angle);
	
	m_Distance -= m_MoveSpeed * DeltaTime;

	//if (m_Move.x < 0.f)
	//	ChangeAnimation("BoomLeftEx");

	//if (m_Move.x > 0.f)
	//	ChangeAnimation("BoomRightEx");

	//if (m_Move.y > 0.f)
	//	ChangeAnimation("BoomDownPower1");

	//if (m_Move.y < 0.f)
	//	ChangeAnimation("BoomUpEx");



	if (m_Distance <= 0.f)
		SetActive(false);
}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBullet::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	Vector2 RenderLT;
	RenderLT = m_Pos - m_Pivot * m_Size;


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CBullet::CollisionBegin(CCollider* Src, CCollider* Dest)
{

	SetActive(false);


	//Vector2 Player = m_Scene->GetPlayer()->GetPos();
	//Vector2 Monster = m_Scene->GetMonster()->GetPos();

		CEffect* Effect = m_Scene->CreateObject<CEffect>("HitEffect");

		Effect->SetPivot(0.5f, 0.5f);
		Effect->SetPos(Src->GetHitPoint());
		
		// 충돌체와 피충돌체 간의 위치에따라 이펙트 구별 
		// 충돌체가 피 충돌체 오른쪽에서 충돌하면 충돌체의 좌표가 피충돌체의 좌표보다 작으므로 , 오른쪽이펙트 출력
		if (Effect->GetPos().x < Dest->GetOwner()->GetPos().x)
		{
			Effect->AddAnimation("RightHitEffect", false, 0.3f);
		}
		// 그게 아니라면 왼쪽 이펙트가 출력된다
		else
		Effect->AddAnimation("LeftHitEffect", false , 0.3f);			

		

		//Dest->GetOwner()->InflictDamage(m_Damage);
}

void CBullet::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	

	
}
