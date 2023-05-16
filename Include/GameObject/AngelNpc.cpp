#include "AngelNpc.h"
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
#include "Barrier.h"
#include "FinalBoss.h"

CAngelNpc::CAngelNpc() 

{
	SetTypeID<CAngelNpc>();
}

CAngelNpc::CAngelNpc(const CAngelNpc& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir)

{
}

CAngelNpc::~CAngelNpc()
{

}



bool CAngelNpc::Init()
{
	CGameObject::Init();

	//m_MoveSpeed = 300.f;

	m_Dir = Vector2(0.f, 1.f);
	

	m_DirLR = -1.f;






	//SetPos(210.f, 480.f);
	//SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("Monster", TEXT("teemo.bmp"));
	//SetColorKey(255, 0, 255);

	CreateAnimation();
	AddAnimation("Angel");
	

	m_Barrier = true;


	m_BombCount = 1;

	m_PlayerCheck = false;


	m_NameBar = CreateWidgetComponent<CText>("NameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("AngelNPC"));
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(-40.f, -50.f);



	return true;
}

void CAngelNpc::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	
	m_Time += DELTA_TIME;

	if (m_Time > 1.f)
	{
		if (m_Barrier)

		{
			CBarrier* Barrier = m_Scene->CreateObject<CBarrier>("Barrier");
			Barrier->SetPivot(0.5f, 0.5f);
			Barrier->SetPos(m_Pos);

			m_Barrier = false;
		}
		
	}


	m_WorkTime += DELTA_TIME;

	if (m_WorkTime > 12.f)
	{
		SetActive(false);
		m_Scene->DeleteAngelNpc();
	}

	

	

}

void CAngelNpc::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	
}

void CAngelNpc::Render(HDC hDC, float DeltaTime)
{

	CCharacter::Render(hDC, DeltaTime);

	//Rectangle(hDC, 300, 300, 300, 300);

	


}

float CAngelNpc::InflictDamage(float Damage)
{



	return Damage;
}