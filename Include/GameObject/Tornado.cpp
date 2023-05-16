#include"Tornado.h"
#include "Player.h"
#include"../Scene/Scene.h"
#include "Bullet.h"

CTornado::CTornado()
{
	SetTypeID<CTornado>();
}

CTornado::CTornado(const CTornado& Obj) :
	CGameObject(Obj),
	m_MoveSpeed(Obj.m_MoveSpeed),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance),
	m_RotationAngle(Obj.m_RotationAngle),
	m_LinePos(Obj.m_LinePos),
	m_Range(Obj.m_Range)

{
}

CTornado::~CTornado()
{
}



bool CTornado::Init()
{
	m_MoveSpeed = 600.f;
	m_Distance = 600.f;
	m_Angle = 180.f;
	m_RotationAngle = 0.f;
	m_Range = 100.f;


	SetPos(900.f, 100.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Tornado", TEXT("Tornado.bmp"));
	SetColorKey(255, 0, 255);
	

	return true;
}

void CTornado::Update(float DeltaTime)
{

	

	m_LinePos.x = m_LinePos.x + cosf(DegreeToRadian(m_Angle)) * m_MoveSpeed * DeltaTime;
	m_LinePos.y = m_LinePos.y + sinf(DegreeToRadian(m_Angle)) * m_MoveSpeed * DeltaTime;

	m_RotationAngle += 1440.f * DeltaTime;

	m_Pos.x = m_LinePos.x + cosf(DegreeToRadian(m_RotationAngle)) * m_Range;
	m_Pos.y = m_LinePos.y + sinf(DegreeToRadian(m_RotationAngle)) * m_Range;


	
	

	/*m_Distance -= m_MoveSpeed * DeltaTime;

	if (m_Distance <= 0.f)
		SetActive(false);*/
}

void CTornado::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	//Vector2 RenderLT;
	//RenderLT = m_Pos - m_Pivot * m_Size;


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}