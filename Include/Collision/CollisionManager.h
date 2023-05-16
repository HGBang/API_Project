#pragma once

#include "../GameInfo.h"
#include "../SingletonMacro.h"

class CCollisionManager
{
private:
	std::unordered_map<std::string, CollisionProfile*>	m_mapProfile;

public:
	bool Init();

	bool CreateProfile(const std::string& Name, ECollision_Channel Channel, bool Enable,
		ECollision_Interaction BaseIteraction = ECollision_Interaction::Collision);
	bool SetCollisionInteraction(const std::string& Name, ECollision_Channel Channel,
		ECollision_Interaction Iteraction);
	CollisionProfile* FindProfile(const std::string& Name);


public:
	bool CollisionBoxToBox(Vector2& HitPoint, class CColliderBox* Src, class CColliderBox* Dest);
	bool CollisionCircleToCircle(Vector2& HitPoint, class CColliderCircle* Src, class CColliderCircle* Dest);
	bool CollisionBoxToCircle(Vector2& HitPoint, class CColliderBox* Src, class CColliderCircle* Dest);
	bool CollisionPointToBox(Vector2& HitPoint, const Vector2& Src, class CColliderBox* Dest);
	bool CollisionPointToCircle(Vector2& HitPoint, const Vector2& Src, class CColliderCircle* Dest);

public:
	bool CollisionBoxToBox(Vector2& HitPoint, const BoxInfo& Src, const BoxInfo& Dest);
	bool CollisionCircleToCircle(Vector2& HitPoint, const CircleInfo& Src, const CircleInfo& Dest);
	bool CollisionBoxToCircle(Vector2& HitPoint, const BoxInfo& Src, const CircleInfo& Dest);
	bool CollisionPointToBox(Vector2& HitPoint, const Vector2& Src, const BoxInfo& Dest);
	bool CollisionPointToCircle(Vector2& HitPoint, const Vector2& Src, const CircleInfo& Dest);


	DECLARE_SINGLE(CCollisionManager)
};

