#include "BossNpc.h"
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
#include "Bomb.h"
#include "MonsterBomb.h"
#include "Bomb2.h"
#include "MonsterDieEffect.h"
#include "MonsterRealDieEffect.h"
#include <time.h>
#include "SpeedItem.h"
#include "StarItem.h"
#include "AddBombItem.h"
#include "RocketItem.h"

CBossNpc::CBossNpc() :
	m_HP(10),
	m_HPMax(10)
{
	SetTypeID<CBossNpc>();
}

CBossNpc::CBossNpc(const CBossNpc& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir),
	m_FireTime(Obj.m_FireTime),
	m_FireCount(Obj.m_FireCount)
{
}

CBossNpc::~CBossNpc()
{

}



bool CBossNpc::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 300.f;
	m_FireTime = 0.f;
	m_Dir = Vector2(0.f, 1.f);
	m_FireCount = 0;

	m_DirLR = -1.f;

	m_Distance = 1000.f;

	m_SpeedItem = true;
	m_StarItem = true;
	m_RocketItem = true;




	SetPos(980.f, 480.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("Monster", TEXT("teemo.bmp"));
	//SetColorKey(255, 0, 255);

	CreateAnimation();
	AddAnimation("NpcRight");
	AddAnimation("NpcLeft");




	m_BombCount = 1;

	m_PlayerCheck = false;


	m_NameBar = CreateWidgetComponent<CText>("NameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("NPC"));
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(-15.f, -50.f);



	return true;
}

void CBossNpc::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


	m_Pos.x += m_DirLR * DELTA_TIME * m_MoveSpeed;

	m_Pos.y += m_DirUP * DELTA_TIME * m_MoveSpeed;

	if (m_Move.x < 0.f)
		ChangeAnimation("NpcLeft");

	if (m_Move.x > 0.f)
		ChangeAnimation("NpcRight");

	m_Distance -= m_MoveSpeed * DeltaTime;



	if (m_Distance < 800.f && m_StarItem)
	{
		CStarItem* Item = m_Scene->CreateObject<CStarItem>("StarItem");
		Item->SetPos(m_Pos);
		m_StarItem = false;
	}

	if (m_Distance < 500.f && m_SpeedItem)
	{
		CRocketItem* Item = m_Scene->CreateObject<CRocketItem>("AddBombItem");
		Item->SetPos(m_Pos);
		m_SpeedItem = false;
	}

	if (m_Distance < 200.f && m_RocketItem)
	{
		CRocketItem* Item = m_Scene->CreateObject<CRocketItem>("AddBombItem");
		Item->SetPos(m_Pos);
		m_RocketItem = false;
	}


	if (m_Pos.x < 70.f)
	{
		SetActive(false);
		m_Scene->DeleteNpc();
		m_NameBar->SetActive(false);
	}


	if (m_Pos.x > 985.f)
	{
		SetActive(false);
		m_Scene->DeleteNpc();
		m_NameBar->SetActive(false);
	}


	if (m_Pos.y < 40.f)
	{
		SetActive(false);
		m_Scene->DeleteNpc();
		m_NameBar->SetActive(false);
	}


	if (m_Pos.y > 660)
	{
		SetActive(false);
		m_Scene->DeleteNpc();
		m_NameBar->SetActive(false);
	}




}

void CBossNpc::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CBossNpc::Render(HDC hDC, float DeltaTime)
{

	CCharacter::Render(hDC, DeltaTime);

	//Rectangle(hDC, 0, 100, 0, 100);
}

float CBossNpc::InflictDamage(float Damage)
{



	return Damage;
}