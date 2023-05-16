#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	std::vector<class CCollider*>	m_vecCollider;
	std::vector<class CWidgetWindow*>	m_vecWidgetWindow;
	class CCollider* m_MouseCollision;
	class CWidget* m_MouseCollisionWidget;

public:
	void AddCollider(class CCollider* Collider);
	void AddWidgetWindow(class CWidgetWindow* Window);
	void CollisionMouse(float DeltaTime);
	void Collision(float DeltaTime);

private:
	static bool SortY(class CCollider* Src, class CCollider* Dest);
	static bool SortWidget(class CWidgetWindow* Src, class CWidgetWindow* Dest);
};

