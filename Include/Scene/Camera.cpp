
#include "Camera.h"
#include "../GameInfo.h"
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../Input.h"


CCamera::CCamera() :
	m_CameraSpeed(0.f),
	m_Angle(0.f)
{
}

CCamera::~CCamera()
{
}

void CCamera::Update(float DeltaTime)
{
	if (m_Target)
	{
		if (!m_Target->GetActive())
			m_Target = nullptr;

		else
			m_Pos = m_Target->GetPos() - m_TargetPivot * m_Resolution + m_TargetOffset;
	}

	// 카메라가 월드를 벗어나지 못하도록 만들어준다.
	if (m_Pos.x < 0.f)
		m_Pos.x = 0.f;

	else if (m_Pos.x + m_Resolution.x > m_WorldResolution.x)
		m_Pos.x = m_WorldResolution.x - m_Resolution.x;

	if (m_Pos.y < 0.f)
		m_Pos.y = 0.f;

	else if (m_Pos.y + m_Resolution.y > m_WorldResolution.y)
		m_Pos.y = m_WorldResolution.y - m_Resolution.y;

	//MoveCamera(DeltaTime);

	CInput::GetInst()->ComputeWorldMousePos(m_Pos);

}

