#pragma once

#include "Scene.h"

class CStartScene :
    public CScene
{
	friend class CSceneManager;


protected:
	CStartScene();
	virtual ~CStartScene();


public:
	bool Init();
};

