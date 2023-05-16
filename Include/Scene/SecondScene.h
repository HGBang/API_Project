#pragma once
#include "Scene.h"
class CSecondScene :
    public CScene
{
	friend class CSceneManager;


protected:
	CSecondScene();
	virtual ~CSecondScene();

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
};

