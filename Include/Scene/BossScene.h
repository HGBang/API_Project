#pragma once
#include "Scene.h"
#include "../Widget/WidgetWindow.h"
class CBossScene :
    public CScene,
	public CWidgetWindow
{
	friend class CSceneManager;


protected:
	CBossScene();
	virtual ~CBossScene();

private:
	//CSharedPtr<class CMonster>	m_Monster;
	CSharedPtr<class CBox> m_Box;
	float			m_TimeCheck;
	float			m_BossNpcTime;
	float			m_FinalTime;
	bool			m_AngelOn;
	bool			m_BossNpcOn;
	float			m_Time;
	float			m_FinalBossTime;
	float			m_ClearTime;

	

public:
	bool Init();
	virtual void Update(float DeltaTime);

private:
	void CreateAnimationSequence();
};

