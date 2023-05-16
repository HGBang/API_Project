#pragma once

#include<Windows.h>
#include<list>
#include<vector>
#include<unordered_map>
#include<crtdbg.h>
#include<typeinfo>
#include<string>
#include<functional>
#include<algorithm>
#include<stack>

#include"Vector2.h"
#include"SharedPtr.h"
#include"Flag.h"
#include"fmod.hpp"

#define GRAVITY 9.8f


#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "../Bin/fmod64_vc.lib")

#define ROOT_PATH		"RootPath"
#define TEXTURE_PATH	"TexturePath"
#define SOUND_PATH	    "SoundPath"
#define FONT_PATH		"FontPath"
#define MAP_PATH		"MapPath"

#define SAFE_DELETE(p) if(p) {delete p; p= nullptr;}
#define SAFE_DELETE_ARRAY(p) if (p) { delete[] p; p = nullptr; }
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr;}

float RadianToDegree(float Radian);
float DegreeToRadian(float Degree);

#define DELTA_TIME CGameManager::GetInst()->GetDeltaTime()

struct Resolution
{
	int Width;
	int Height;
};


struct AnimationFrameData
{
	Vector2 Start;
	Vector2 End;
};

struct CollisionProfile
{
	std::string							Name;
	ECollision_Channel					Channel;
	bool								Enable;
	std::vector<ECollision_Interaction> vecCollisionInteraction;

	CollisionProfile() :
		Enable(true)
	{
	}
};

struct BoxInfo
{
	Vector2 LT;
	Vector2 RB;
};

struct CircleInfo
{
	Vector2 Center;
	float	Radius;
};