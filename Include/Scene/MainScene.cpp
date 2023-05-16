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
#include "../Widget/CharacterHUD.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Box.h"
#include "../Resource/ResourceManager.h"
#include "../GameObject/SpeedItem.h"
#include "../GameObject/AddBombItem.h"
#include "../GameObject/StarItem.h"
#include "../Widget/Button.h"
#include "../Widget/WidgetWindow.h"
#include "../Scene/SceneManager.h"
#include "StartScene.h"
#include "../GameObject/Npc.h"
#include "../GameObject/PowerItem.h"
#include "../GameObject/ShoesItem.h"


#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/EditScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "../Scene/ClearScene.h"

#include "../GameManager.h"






CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CreateAnimationSequence();

	GetSceneResource()->LoadSound("BGM", "MainBGM", true, "CA.mp3");
	GetSceneResource()->LoadSound("BGM", "MainBGM2", false, "start.mp3");
	GetSceneResource()->LoadSound("BGM", "MainBGM3", false, "win.mp3");
	GetSceneResource()->LoadSound("Effect", "Fire", false, "Fire1.wav");
	GetSceneResource()->LoadSound("Effect", "Hit", false, "Stun.wav");
	GetSceneResource()->LoadSound("Effect", "Hit1", false, "TeemoSmile.mp3");
	GetSceneResource()->LoadSound("Effect", "Talon", false, "talon.wav");
	GetSceneResource()->LoadSound("Effect", "Bubble", false, "wooden.ogg");
	GetSceneResource()->LoadSound("Effect", "Bomb", false, "Boom.mp3");
	GetSceneResource()->LoadSound("Effect", "item", false, "item.mp3");
	GetSceneResource()->LoadSound("Effect", "boom", false, "boom.mp3");

	GetSceneResource()->SoundPlay("MainBGM2");

	GetSceneResource()->SoundPlay("MainBGM");

	GetSceneResource()->SetVolume(15);

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);


	CTileMap* TileMap = CreateObject<CTileMap>("TileMap");



	TileMap->LoadFileName("MainMap2.tmp", MAP_PATH);



	m_Player = CreateObject<CPlayer>("Player");

	m_Player->SetPos(100.f, 100.f);

	CreateObject<CBackObj>("BackGround");

	/*CPlayer* Player = CreateObject<CPlayer>("Player");
	
	SetPlayer(Player);*/


	

	//m_Monster = CreateObject<CMonster>("Monster");

	//SetMonster(m_Monster);

	//GetCamera()->SetTarget(m_Player);

	m_Monster = CreateObject<CMonster>("Monster");

	

	//CreateObject<CNpc>("Npc");

		

	/*CPowerItem* Item = CreateObject<CPowerItem>("PowerItem");

	Item->SetPos(150.f, 350.f);

	CPowerItem* Item2 = CreateObject<CPowerItem>("PowerItem");

	Item2->SetPos(350.f, 350.f);


	CreateObject<CShoesItem>("ShoesItem");*/


	


	CInput::GetInst()->AddBindFunction<CMainScene>("Cam1", Input_Type::Down, this, &CMainScene::Cam1Key);
	CInput::GetInst()->AddBindFunction<CMainScene>("Cam2", Input_Type::Down, this, &CMainScene::Cam2Key);

	//CreateWidgetWindow<CCharacterHUD>("CharacterHUD");
	

	//Vector2 Rect;
				
	return true;
}

void CMainScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);


	m_NpcTime += DELTA_TIME;
	if (m_NpcTime > 25.f)
	{
		m_Npc = CreateObject<CNpc>("Npc");

		m_NpcTime = 0.f;

	}


	if (m_Player == nullptr)
	{
		m_PlayerTimeCheck += DELTA_TIME;

		if (m_PlayerTimeCheck > 3.f)
		{
			m_Player = CreateObject<CPlayer>("Player");
			m_Player->SetPos(150.f, 150.f);
														
			m_PlayerTimeCheck = 0.f;

		/*	CInput::GetInst()->ClearCallback();
			CSceneManager::GetInst()->CreateScene<CClearScene>();*/

		}
	}

	if (m_Monster == nullptr)
	{
		m_MonsterTimeCheck += DELTA_TIME;
		
		DeletePlayer();

		if (m_MonsterTimeCheck > 3.f)
		{
			CInput::GetInst()->ClearCallback();
			CSceneManager::GetInst()->CreateScene<CClearScene>();

			m_MonsterTimeCheck = 0.f;
		}
	}

}

void CMainScene::CreateAnimationSequence()
{
	// ¿À¸¥ÂÊ ¸ØÃçÀÖ´Â»óÅÂ 
	GetSceneResource()->CreateAnimationSequence("PlayerRightIdle", "PlayerRightIdle", TEXT("astand.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRightIdle", 82.f * i, 0.f, 82.f, 73.f);
	}

	GetSceneResource()->SetColorKey("PlayerRightIdle" , 255, 0, 255);

	 // ¿À¸¥ÂÊ °È´Â »óÅÂ
		GetSceneResource()->CreateAnimationSequence("PlayerRightWalk", "PlayerRightWalk", TEXT("awalk.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRightWalk", 85.f * i, 0.f, 85.f, 75.f);
	}

	GetSceneResource()->SetColorKey("PlayerRightWalk", 255, 0, 255);

	// ¿ÞÂÊ ¸ØÃçÀÖ´Â»óÅÂ 
	GetSceneResource()->CreateAnimationSequence("PlayerLeftIdle", "PlayerLeftIdle", TEXT("Player/Left/astand_left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerLeftIdle", 82.f * i, 0.f, 82.f, 73.f);
	}

	GetSceneResource()->SetColorKey("PlayerLeftIdle", 255, 0, 255);

	// ¿ÞÂÊ °È´Â »óÅÂ
	GetSceneResource()->CreateAnimationSequence("PlayerLeftWalk", "PlayerLeftWalk", TEXT("Player/Left/awalk_left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerLeftWalk", 85.f * i, 0.f, 85.f, 75.f);
	}

	GetSceneResource()->SetColorKey("PlayerLeftWalk", 255, 0, 255);

	// ¿À¸¥ÂÊ °ø°Ý
	GetSceneResource()->CreateAnimationSequence("PlayerRightAttack", "PlayerRightAttack", TEXT("ashoot1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack", 70.f * i, 0.f, 70.f, 81.f);
	}

	GetSceneResource()->SetColorKey("PlayerRightAttack", 255, 0, 255);

	// ¿ÞÂÊ °ø°Ý

	GetSceneResource()->CreateAnimationSequence("PlayerLeftAttack", "PlayerLeftAttack", TEXT("Player/Left/ashoot1_left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack", 70.f * i, 0.f, 70.f, 81.f);
	}

	GetSceneResource()->SetColorKey("PlayerLeftAttack", 255, 0, 255);

	//¿ÞÂÊ °ø°Ý ÀÌÆåÆ®

	GetSceneResource()->CreateAnimationSequence("LeftHitEffect", "LeftHitEffect", TEXT("Hit.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("LeftHitEffect", 178.f * i, 0.f, 178.f, 164.f);
	}

	GetSceneResource()->SetColorKey("LeftHitEffect", 255, 0, 255);

	//¿À¸¥ÂÊ °ø°Ý ÀÌÆåÆ®

	GetSceneResource()->CreateAnimationSequence("RightHitEffect", "RightHitEffect", TEXT("Hit2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RightHitEffect", 178.f * i, 0.f, 178.f, 164.f);
	}

	GetSceneResource()->SetColorKey("RightHitEffect", 255, 0, 255);


	// ¿À¸¥ÂÊ 
	GetSceneResource()->CreateAnimationSequence("PlayerRight", "PlayerRight", TEXT("bazziright.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRight", 50.f * i, 0.f, 50.f, 40.f);
	}

	GetSceneResource()->SetColorKey("PlayerRight", 100, 100, 100);

	// ¿ÞÂÊ
	GetSceneResource()->CreateAnimationSequence("PlayerLeft", "PlayerLeft", TEXT("bazzileft.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerLeft", 50.f * i, 0.f, 50.f, 40.f);
	}

	GetSceneResource()->SetColorKey("PlayerLeft", 100, 100, 100);


	// À§
	GetSceneResource()->CreateAnimationSequence("PlayerUp", "PlayerUp", TEXT("bazziup.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerUp", 50.f * i, 0.f, 50.f, 40.f);
	}

	GetSceneResource()->SetColorKey("PlayerUp", 100, 100, 100);


	// ¾Æ·¡
	GetSceneResource()->CreateAnimationSequence("PlayerDown", "PlayerDown", TEXT("bazzidown.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerDown", 50.f * i, 0.f, 50.f, 40.f);
	}

	GetSceneResource()->SetColorKey("PlayerDown", 100, 100, 100);


	GetSceneResource()->CreateAnimationSequence("Bomb", "Bomb", TEXT("BlueBub.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Bomb", 50.f * i, 0.f, 50.f, 55.f);
	}

	GetSceneResource()->SetColorKey("Bomb", 0, 0, 0);


	GetSceneResource()->CreateAnimationSequence("BoomDownEx", "BoomDownEx", TEXT("BoomDownEx.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomDownEx", 40.f * i, 0.f, 40.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomDownEx", 0, 0, 0);


	GetSceneResource()->CreateAnimationSequence("BoomUpEx", "BoomUpEx", TEXT("BoomUpEx.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomUpEx", 40.f * i, 0.f, 40.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomUpEx", 0, 0, 0);


	GetSceneResource()->CreateAnimationSequence("BoomLeftEx", "BoomLeftEx", TEXT("BoomLeftEx.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomLeftEx", 40.f * i, 0.f, 40.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomLeftEx", 0, 0, 0);


	GetSceneResource()->CreateAnimationSequence("BoomRightEx", "BoomRightEx", TEXT("BoomRightEx.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomRightEx", 40.f * i, 0.f, 40.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomRightEx", 0, 0, 0);

	

	GetSceneResource()->CreateAnimationSequence("BoomDie", "BoomDie", TEXT("Boomcenter.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomDie", 40.f * i, 0.f, 40.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomDie", 0, 0, 0);

	GetSceneResource()->CreateAnimationSequence("PlayerDie", "PlayerDie", TEXT("PlayerDie.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerDie", 60.f * i, 0.f, 60.f, 65.f);
	}

	GetSceneResource()->SetColorKey("PlayerDie", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerDie1", "PlayerDie1", TEXT("PlayerDie1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerDie1", 60.f * i, 0.f, 60.f, 65.f);
	}

	GetSceneResource()->SetColorKey("PlayerDie1", 255, 0, 255);


	GetSceneResource()->CreateAnimationSequence("PlayerDie2", "PlayerDie2", TEXT("PlayerDie2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerDie2", 60.f * i, 0.f, 60.f, 65.f);
	}

	GetSceneResource()->SetColorKey("PlayerDie2", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerDie3", "PlayerDie3", TEXT("PlayerDie3.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerDie3", 70.f * i, 0.f, 70.f, 110.f);
	}

	GetSceneResource()->SetColorKey("PlayerDie3", 255, 0, 255);


	GetSceneResource()->CreateAnimationSequence("PlayerDieFull", "PlayerDieFull", TEXT("PlayerDieFull.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerDieFull", 60.f * i, 0.f, 60.f, 65.f);
	}

	GetSceneResource()->SetColorKey("PlayerDieFull", 255, 0, 255);


	GetSceneResource()->CreateAnimationSequence("Alive", "Alive", TEXT("Alive.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Alive", 60.f * i, 0.f, 60.f, 40.f);
	}

	GetSceneResource()->SetColorKey("Alive", 255, 0, 255);

	// ¿À¸¥ÂÊ
	GetSceneResource()->CreateAnimationSequence("MonsterRight", "MonsterRight", TEXT("uniright.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("MonsterRight", 50.f * i, 0.f, 50.f, 40.f);
	}

	GetSceneResource()->SetColorKey("MonsterRight", 100, 100, 100);

	// ¿ÞÂÊ
	GetSceneResource()->CreateAnimationSequence("MonsterLeft", "MonsterLeft", TEXT("unileft.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("MonsterLeft", 50.f * i, 0.f, 50.f, 40.f);
	}

	GetSceneResource()->SetColorKey("MonsterLeft", 100, 100, 100);


	// À§
	GetSceneResource()->CreateAnimationSequence("MonsterUp", "MonsterUp", TEXT("uniup.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("MonsterUp", 50.f * i, 0.f, 50.f, 40.f);
	}

	GetSceneResource()->SetColorKey("MonsterUp", 100, 100, 100);


	// ¾Æ·¡
	GetSceneResource()->CreateAnimationSequence("MonsterDown", "MonsterDown", TEXT("unidown.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("MonsterDown", 50.f * i, 0.f, 50.f, 40.f);
	}

	GetSceneResource()->SetColorKey("MonsterDown", 100, 100, 100);

	//¸ó½ºÅÍ Á×´Â ¸ð¼Ç 
	GetSceneResource()->CreateAnimationSequence("MonsterDie1", "MonsterDie1", TEXT("unidie1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("MonsterDie1", 68.f * i, 0.f, 68.f, 60.f);
	}

	GetSceneResource()->SetColorKey("MonsterDie1", 100, 100, 100);

	//¸ó½ºÅÍ Á×´Â ¸ð¼Ç 
	GetSceneResource()->CreateAnimationSequence("MonsterDie2", "MonsterDie2", TEXT("unidie2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 1; ++i)
	{
		GetSceneResource()->AddAnimationFrame("MonsterDie2", 47.f * i, 0.f, 47.f, 48.f);
	}

	GetSceneResource()->SetColorKey("MonsterDie2", 100, 100, 100);


	// NPC ¿À¸¥ÂÊ
	GetSceneResource()->CreateAnimationSequence("NpcRight", "NpcRight", TEXT("Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("NpcRight", 44.f * i, 0.f, 44.f, 62.f);
	}

	GetSceneResource()->SetColorKey("NpcRight", 255, 0, 255);

	// NPC ¿ÞÂÊ
	GetSceneResource()->CreateAnimationSequence("NpcLeft", "NpcLeft", TEXT("Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("NpcLeft", 44.f * i, 0.f, 44.f, 62.f);
	}

	GetSceneResource()->SetColorKey("NpcLeft", 255, 0, 255);


	GetSceneResource()->CreateAnimationSequence("BoomDownPower1", "BoomDownPower1", TEXT("BoomDownPower1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomDownPower1", 40.f * i, 0.f, 40.f, 80.f);
	}

	GetSceneResource()->SetColorKey("BoomDownPower1", 0, 0, 0);

	GetSceneResource()->CreateAnimationSequence("BoomDownPower2", "BoomDownPower2", TEXT("BoomDownPower2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomDownPower2", 40.f * i, 0.f, 40.f, 160.f);
	}

	GetSceneResource()->SetColorKey("BoomDownPower2", 0, 0, 0);

	GetSceneResource()->CreateAnimationSequence("BoomRightPower1", "BoomRightPower1", TEXT("BoomRightPower1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomRightPower1", 80.f * i, 0.f, 80.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomRightPower1", 0, 0, 0);

	GetSceneResource()->CreateAnimationSequence("BoomLeftPower1", "BoomLeftPower1", TEXT("BoomLeftPower1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomLeftPower1", 80.f * i, 0.f, 80.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomLeftPower1", 0, 0, 0);


	GetSceneResource()->CreateAnimationSequence("BoomUpPower1", "BoomUpPower1", TEXT("BoomUpPower1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomUpPower1", 40.f * i, 0.f, 40.f, 80.f);
	}

	GetSceneResource()->SetColorKey("BoomUpPower1", 0, 0, 0);


	GetSceneResource()->CreateAnimationSequence("BoomUpPower2", "BoomUpPower2", TEXT("BoomUpPower2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomUpPower2", 40.f * i, 0.f, 40.f, 160.f);
	}

	GetSceneResource()->SetColorKey("BoomUpPower2", 0, 0, 0);

	GetSceneResource()->CreateAnimationSequence("BoomLeftPower2", "BoomLeftPower2", TEXT("BoomLeftPower2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomLeftPower2", 120.f * i, 0.f, 120.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomLeftPower2", 0, 0, 0);

	GetSceneResource()->CreateAnimationSequence("BoomRightPower2", "BoomRightPower2", TEXT("BoomRightPower2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoomRightPower2", 120.f * i, 0.f, 120.f, 40.f);
	}

	GetSceneResource()->SetColorKey("BoomRightPower2", 0, 0, 0);










}

void CMainScene::Cam1Key()
{
	GetCamera()->SetTarget(m_Player);
}

void CMainScene::Cam2Key()
{
	GetCamera()->SetTarget(m_Monster);
}

