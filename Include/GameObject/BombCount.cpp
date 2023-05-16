#include "BombCount.h"


CBombCount::CBombCount()
{
	SetTypeID<CBombCount>();
}

CBombCount::CBombCount(const CBombCount& Obj) :
	CGameObject(Obj)
{
}

CBombCount::~CBombCount()
{
}

bool CBombCount::Init()
{
	m_BombCount = 2;


	return true;
}

void CBombCount::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBombCount::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBombCount::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

float CBombCount::InflictDamage(float Damage)
{
	return CGameObject::InflictDamage(Damage);
}

void CBombCount::AddBombCount()
{
	++m_BombCount;
}
