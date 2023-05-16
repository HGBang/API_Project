#include "ClearSecondScene.h"
#include "MainScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Effect.h"
#include "SceneResource.h"
#include "../GameObject/BackObj.h"
#include "Camera.h"
#include "../GameInfo.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"
#include "../Widget/ClearWindow.h"
#include "../Widget/ClearSecondWindow.h"


CClearSecondScene::CClearSecondScene()
{
}

CClearSecondScene::~CClearSecondScene()
{
}

bool CClearSecondScene::Init()
{


	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CreateWidgetWindow<CClearSecondWindow>("ClearSecondScene");

	return true;
}