#pragma once
#include "Scene.h"
#include "../GameManager.h"
#include "../GameInfo.h"
#include "../Widget/WidgetWindow.h"

class CMainScene :
    public CScene
	
{
	friend class CSceneManager;


protected:
	CMainScene();
	virtual ~CMainScene();

private:
	//CSharedPtr<class CMonster>	m_Monster;
	CSharedPtr<class CBox> m_Box;
	float			m_TimeCheck;
	float			m_NpcTime;
	float			m_PlayerTimeCheck;
	float			m_MonsterTimeCheck;

public:
	bool Init();
	virtual void Update(float DeltaTime);

private:
	void CreateAnimationSequence();

private:
	void Cam1Key();
	void Cam2Key();

};

