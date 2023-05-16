#pragma once

#include "../GameObject/GameObject.h"

class CCamera
{
	friend class CScene;

private:
	CCamera();
	~CCamera();

protected:
	class CScene* m_Scene;

private:
	Vector2	m_Pos;
	Vector2	m_Resolution;
	Vector2	m_WorldResolution;
	CSharedPtr<CGameObject>	m_Target;
	Vector2	m_TargetOffset;
	Vector2	m_TargetPivot;
	float	m_CameraSpeed;
	float		m_Angle;


public:
	Vector2 GetPos()	const
	{
		return m_Pos;
	}

	Vector2 GetResolution()	const
	{
		return m_Resolution;
	}

	Vector2 GetWorldResolution()	const
	{
		return m_WorldResolution;
	}

	CGameObject* GetTarget()	const
	{
		return m_Target;
	}

	Vector2 GetTargetOffset()	const
	{
		return m_TargetOffset;
	}

	Vector2 GetTargetPivot()	const
	{
		return m_TargetPivot;
	}


public:
	void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}

	void SetPos(float x, float y)
	{
		m_Pos = Vector2(x, y);
	}

	void SetResolution(const Vector2& Resolution)
	{
		m_Resolution = Resolution;
	}

	void SetResolution(float x, float y)
	{
		m_Resolution = Vector2(x, y);
	}

	void SetWorldResolution(const Vector2& WorldResolution)
	{
		m_WorldResolution = WorldResolution;
	}

	void SetWorldResolution(float x, float y)
	{
		m_WorldResolution = Vector2(x, y);
	}

	void SetTargetOffset(const Vector2& TargetOffset)
	{
		m_TargetOffset = TargetOffset;
	}

	void SetTargetOffset(float x, float y)
	{
		m_TargetOffset = Vector2(x, y);
	}

	void SetTargetPivot(const Vector2& TargetPivot)
	{
		m_TargetPivot = TargetPivot;
	}

	void SetTargetPivot(float x, float y)
	{
		m_TargetPivot = Vector2(x, y);
	}

	void SetTarget(CGameObject* Target)
	{
		m_Target = Target;
	}
	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}

	


public:
	void Update(float DeltaTime);

};

