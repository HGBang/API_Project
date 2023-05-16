#include "AngelCut.h"
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

CAngelCut::CAngelCut()

{
	SetTypeID<CAngelCut>();
}

CAngelCut::CAngelCut(const CAngelCut& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir)

{
}

CAngelCut::~CAngelCut()
{

}



bool CAngelCut::Init()
{
	CGameObject::Init();

    m_MoveSpeed = 1000.f;

	m_Angle = 180.f;

	m_Distance = 500.f;


	SetTexture("AngelCut", TEXT("Su.bmp"));
	SetColorKey(100, 100, 100);

	//SetPos(210.f, 480.f);
	//SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	//SetTexture("Monster", TEXT("teemo.bmp"));
	//SetColorKey(255, 0, 255);







	return true;
}

void CAngelCut::Update(float DeltaTime)
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

void CAngelCut::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);


}

void CAngelCut::Render(HDC hDC, float DeltaTime)
{

	CCharacter::Render(hDC, DeltaTime);





}

float CAngelCut::InflictDamage(float Damage)
{

	return Damage;
}