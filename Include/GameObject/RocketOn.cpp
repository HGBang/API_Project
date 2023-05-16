#include "RocketOn.h"
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

CRocketOn::CRocketOn()

{
	SetTypeID<CRocketOn>();
}

CRocketOn::CRocketOn(const CRocketOn& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir)

{
}

CRocketOn::~CRocketOn()
{

}



bool CRocketOn::Init()
{
	CGameObject::Init();




	SetTexture("RocketOn", TEXT("RocketOn.bmp"));
	SetColorKey(100, 100, 100);

	//SetPos(210.f, 480.f);
	//SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("Monster", TEXT("teemo.bmp"));
	//SetColorKey(255, 0, 255);







	return true;
}

void CRocketOn::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//SetPos(m_Scene->GetPlayer()->GetPos());

	//m_WorkTime += DELTA_TIME;

	//if (m_WorkTime > 7.5f)
	//{
	//	SetActive(false);
	//}

	m_Pos.x = m_Scene->GetPlayer()->GetPos().x - 40.f;
	m_Pos.y = m_Scene->GetPlayer()->GetPos().y;



		if (!m_Scene->GetPlayer()->GetRocket())
		{
			SetActive(false);
			
		}


}

void CRocketOn::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);


}

void CRocketOn::Render(HDC hDC, float DeltaTime)
{

	CCharacter::Render(hDC, DeltaTime);





}

float CRocketOn::InflictDamage(float Damage)
{

	return Damage;
}