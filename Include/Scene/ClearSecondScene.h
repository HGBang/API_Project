#pragma once
#include "Scene.h"
class CClearSecondScene :
    public CScene
{
	friend class CSceneManager;


protected:
	CClearSecondScene();
	virtual ~CClearSecondScene();


public:
	bool Init();
};

