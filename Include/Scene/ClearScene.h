#pragma once
#include "Scene.h"
class CClearScene :
    public CScene
{
	friend class CSceneManager;


protected:
	CClearScene();
	virtual ~CClearScene();


public:
	bool Init();
};

