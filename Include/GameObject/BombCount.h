#pragma once
#include "GameObject.h"
class CBombCount :
    public CGameObject
{
	friend class CScene;

protected:
	CBombCount();
	CBombCount(const CBombCount& Obj);
	virtual ~CBombCount();


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

public:
	int GetBombCountNumber()
	{
		return m_BombCount;
	}

	void AddBombCount();


};

