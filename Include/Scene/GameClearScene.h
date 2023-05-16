#pragma once
#include "Scene.h"
class CGameClearScene :
    public CScene
{
	friend class CSceneManager;


protected:
	CGameClearScene();
	virtual ~CGameClearScene();


public:
	bool Init();
};

