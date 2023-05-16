#pragma once
#include "GameObject.h"
class CTornado :
    public CGameObject
{
	friend class CScene;

protected:
	CTornado();
	CTornado(const CTornado& Obj);
	virtual ~CTornado();

private:
	float		m_MoveSpeed;
	float		m_Angle;
	float		m_RotationAngle;
	float		m_Distance;
	Vector2		m_LinePos;
	float		m_Range;


public:
	virtual void SetPos(float x, float y)
	{
		CGameObject::SetPos(x, y);
		m_LinePos = m_Pos;
		
	}

	virtual void SetPos(const Vector2& Pos)
	{
		CGameObject::SetPos(Pos);
		m_LinePos = m_Pos;
	
	}
	void SetDistance(float Dist)
	{
		m_Distance = Dist;
	}

	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}

	void SetRotation(float Rotation)
	{
		m_RotationAngle = Rotation;
	}



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

