
#include"AurellionSol.h"
#include"../Collision/ColliderCircle.h"
#include"../Scene/Scene.h"

CAurellionSol::CAurellionSol()
{
	SetTypeID<CAurellionSol>();
}

CAurellionSol::CAurellionSol(const CAurellionSol& Obj) :
	CGameObject(Obj)

{

}
	


CAurellionSol::~CAurellionSol()
{
}



bool CAurellionSol::Init()
{
	
	m_Damage = 10.f;
	
	SetSize(50.f, 50.f);
	

	SetTexture("Sol", TEXT("Sol.bmp"));
	SetColorKey(255, 0, 255);


	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(15.f);
	Circle->SetCollisionProfile("StarAttack");
	Circle->SetOffset(24.f, 24.f);

	Circle->SetCollisionBeginFunction<CAurellionSol>(this, &CAurellionSol::CollisionBegin);
	Circle->SetCollisionEndFunction<CAurellionSol>(this, &CAurellionSol::CollisionEnd);

	m_Rocket = true;



	return true;
}

void CAurellionSol::Update(float DeltaTime)
{

	if (m_Scene->GetPlayer())
	{
		if (!m_Scene->GetPlayer()->GetSolSKill())
			SetActive(false);

	}
	else
	{

	}

}

void CAurellionSol::Render(HDC hDC, float DeltaTime)
{

	CGameObject::Render(hDC, DeltaTime);
	//Vector2 RenderLT;
	//RenderLT = m_Pos - m_Pivot * m_Size;
	//m_Time += DeltaTime;

	//if (m_Time > 5.f)
		//SetActive(false);

	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));


}

void CAurellionSol::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	Dest->GetOwner()->InflictDamage(m_Damage);
}

void CAurellionSol::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
