#pragma once
#include "GameObject.h"
class CBackObj :
    public CGameObject
{

	friend class CScene;

protected:
	CBackObj();
	CBackObj(const CBackObj& Obj);
	virtual ~CBackObj();



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};


