#include"TalonM.h"
#include"../Scene/Scene.h"
#include"../Collision/ColliderCircle.h"



CTalonM::CTalonM()
{
	SetTypeID<CTalonM>();
}

CTalonM::CTalonM(const CTalonM& Obj) :
	CGameObject(Obj),
	m_MoveSpeed(Obj.m_MoveSpeed),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance),
	m_FireTime(Obj.m_FireTime)

{
}

CTalonM::~CTalonM()
{
}



bool CTalonM::Init()
{
	m_MoveSpeed = 1000.f;
	m_Distance = 1000.f;
	m_Angle = 180.f;
	m_Dir = 1;
	m_Arrow = false;
	m_fireTime = 0.f;

	SetPos(100.f, 100.f);

	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("TalonM", TEXT("Talon.bmp"));
	SetColorKey(255, 0, 255);


	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(25.f);
	Circle->SetCollisionProfile("PlayerAttack");

	Circle->SetCollisionBeginFunction<CTalonM>(this, &CTalonM::CollisionBegin);
	Circle->SetCollisionEndFunction<CTalonM>(this, &CTalonM::CollisionEnd);


	return true;
}

void CTalonM::Update(float DeltaTime)
{


	m_Pos.x = m_Pos.x + cosf(DegreeToRadian(m_Angle)) * m_Dir * m_MoveSpeed * DeltaTime;
	m_Pos.y = m_Pos.y + sinf(DegreeToRadian(m_Angle)) * m_Dir * m_MoveSpeed * DeltaTime;

	m_Distance -= m_MoveSpeed * DeltaTime;

	if (m_Distance <= 700)
	{
		m_Dir = 0;

		m_Distance += m_MoveSpeed * DeltaTime;

		m_fireTime += DeltaTime;

		if (m_fireTime >= 2.f)
		{
			m_Dir = 1;
			float Angle = GetPos().Angle(m_Scene->GetPlayer()->GetPos());
			SetAngle(Angle);

			
		}

		if (m_fireTime >= 3.f)
		{
			SetActive(false);
		}
	}

	

	




	if (m_Distance <= 0.f)
		SetActive(false);
}

void CTalonM::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	//Vector2 RenderLT;
	//RenderLT = m_Pos - m_Pivot * m_Size;


	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CTalonM::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CTalonM::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
