#include "GameClearScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Effect.h"
#include "SceneResource.h"
#include "../GameObject/BackObj.h"
#include "../GameInfo.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"
#include "../Widget/ClearWindow.h"
#include "../Widget/ClearSecondWindow.h"
#include "../Scene/Camera.h"
#include "../Widget/GameClearWindow.h"


CGameClearScene::CGameClearScene()
{
}

CGameClearScene::~CGameClearScene()
{
}

bool CGameClearScene::Init()
{


	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CreateWidgetWindow<CGameClearWindow>("GameClearScene");

	return true;
}