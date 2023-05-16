#include "Timer.h"

CTimer::CTimer():
	m_Second{},
	m_Time{},
	m_DeltaTime(0.f),
	m_FPS(0.f),
	m_FPSTime(0.f),
	m_Tick(0)
{
}

CTimer::~CTimer()
{
}

void CTimer::Init()
{
	//Ÿ�̸Ӱ� 1�ʰ� �귶������ ���� ����
	QueryPerformanceFrequency(&m_Second);
	
	//���� Ÿ�̸��� ���� ���´�

	QueryPerformanceCounter(&m_Time);


}

void CTimer::Update()
{
	LARGE_INTEGER	Time;
	QueryPerformanceCounter(&Time);

	//DeltaTime�� ���Ѥ���.
	//���� Ÿ�̸Ӱ� - ���� ������ Ÿ�̸Ӱ� / �ʴ� Ÿ�̸Ӱ�
	m_DeltaTime = (Time.QuadPart - m_Time.QuadPart) / (float)m_Second.QuadPart;

	//���� Ÿ�̸Ӱ��� ����Ÿ�̸Ӱ����� ��ü�Ѵ�. 

	m_Time = Time;

	m_FPSTime += m_DeltaTime;
	++m_Tick;

	if (m_Tick == 60)
	{
		m_FPS = m_Tick / m_FPSTime;
		m_FPSTime = 0.f;
		m_Tick = 0;
	}
}
