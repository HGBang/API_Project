#include "FinalCut.h"
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

CFinalCut::CFinalCut()

{
	SetTypeID<CFinalCut>();
}

CFinalCut::CFinalCut(const CFinalCut& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir)

{
}

CFinalCut::~CFinalCut()
{

}



bool CFinalCut::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 1000.f;

	m_Angle = 360.f;

	m_Distance = 500.f;


	SetTexture("FinalCut", TEXT("FinalCut.bmp"));
	SetColorKey(100, 100, 100);

	//SetPos(210.f, 480.f);
	//SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("Monster", TEXT("teemo.bmp"));
	//SetColorKey(255, 0, 255);







	return true;
}

void CFinalCut::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(m_Angle);

	m_Distance -= m_MoveSpeed * DeltaTime;

	if (m_Distance <= 0)
	{
		m_MoveSpeed = 0.f;
	}



	m_WorkTime += DELTA_TIME;

	if (m_WorkTime > 2.5f)
	{
		SetActive(false);
	}



}

void CFinalCut::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);


}

void CFinalCut::Render(HDC hDC, float DeltaTime)
{

	CCharacter::Render(hDC, DeltaTime);





}

float CFinalCut::InflictDamage(float Damage)
{

	return Damage;
}