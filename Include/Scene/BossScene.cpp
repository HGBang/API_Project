#include "BossScene.h"
#include "SecondScene.h"
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
#include "../GameObject/BossMonster.h"
#include "../GameObject/RocketItem.h"
#include "../GameObject/BossNpc.h"
#include "../GameObject/FinalBoss.h"
#include "../GameObject/AngelNpc.h"
#include <time.h>
#include "../Widget/Icon.h"
#include "../GameObject/AngelCut.h"
#include "../Scene/GameClearScene.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/EditScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "../Scene/ClearScene.h"
#include "../Scene/ClearSecondScene.h"

#include "../GameManager.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/EditScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Scene/SecondScene.h"
#include "../Scene/BossScene.h"
#include "../GameObject/FinalBomb.h"



CBossScene::CBossScene()
{
}

CBossScene::~CBossScene()
{
}

bool CBossScene::Init()
{
	CreateAnimationSequence();

	GetSceneResource()->LoadSound("BGM", "MainBGM", true, "CA.mp3");
	GetSceneResource()->LoadSound("BGM", "BossBGM", true, "Boss.mp3");
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
	GetSceneResource()->LoadSound("Effect", "Merci", false, "merci.mp3");
	GetSceneResource()->LoadSound("Effect", "Final", false, "Final.mp3");

	GetSceneResource()->SoundPlay("MainBGM2");

	GetSceneResource()->SoundPlay("BossBGM");

	GetSceneResource()->SetVolume(50);

	GetSceneResource()->SetVolume("Effect", 100);
	GetSceneResource()->SetVolume("BGM", 20);

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CreateObject<CBackObj>("BackGround");

	/*CPlayer* Player = CreateObject<CPlayer>("Player");

	SetPlayer(Player);*/

	m_Player = CreateObject<CPlayer>("Player");

	SetPlayer(m_Player);

	m_Player->SetMoveSpeed(400.f);

	m_Player->SetBossRound(true);

	m_BossMonster = CreateObject<CBossMonster>("BossMonster");

	//m_FinalBossMonster = CreateObject<CFinalBoss>("FinalBoss");


	m_BossNpcOn = true;
		

	m_AngelOn = true;

	//SetMonster(m_Monster);

	//GetCamera()->SetTarget(m_Player);

	//m_Monster = CreateObject<CMonster>("Monster");

	CTileMap* TileMap = CreateObject<CTileMap>("TileMap");

	//TileMap->CreateTile(100, 100, Vector2(40.f,53.f));
	//TileMap->SetTileTexture("Tile", TEXT("Stone.bmp"));
	//TileMap->SetTileColorKeyAll(255, 0, 255);

	TileMap->LoadFileName("BossMap.tmp", MAP_PATH);


	CreateObject<CRocketItem>("RocketItem");

	CreateObject<CStarItem>("StarItem");


	//CAngelCut* AngelCut = CreateObject<CAngelCut>("AngelCut");

	//AngelCut->SetPos(1600.f, 600.f);


	
	//CreateObject<CAngelNpc>("Angel");

	//CFinalBomb* Bomb = CreateObject<CFinalBomb>("FinalBomb");
	//Bomb->SetPos(290.f, 510.f);
	////Bomb->SetMoveSpeed(40.f);
	////Bomb->SetAngle(360.f);
	//Bomb->SetRound(true);


	//CFinalBomb* Bomb1 = CreateObject<CFinalBomb>("FinalBomb");
	//Bomb1->SetPos(290.f, 180.f);
	////Bomb1->SetMoveSpeed(40.f);
	//Bomb1->SetAngle(90.f);
	//Bomb1->SetNumber(50);


	//CFinalBomb* Bomb2 = CreateObject<CFinalBomb>("FinalBomb");
	//Bomb2->SetPos(780.f, 510.f);
	////Bomb2->SetMoveSpeed(40.f);
	////Bomb2->SetAngle(270.f);
	//Bomb2->SetNumber(90);
	//Bomb2->SetRound(true);


	//CFinalBomb* Bomb3 = CreateObject<CFinalBomb>("FinalBomb");
	//Bomb3->SetPos(780.f, 180.f);
	////Bomb3->SetMoveSpeed(40.f);
	////Bomb3->SetAngle(180.f);
	//Bomb3->SetNumber(130);
	//Bomb3->SetRound(false);




	//CreateWidgetWindow<CCharacterHUD>("CharacterHUD");


	//Vector2 Rect;

	return true;
}

void CBossScene::Update(float DeltaTime)
{

	CScene::Update(DeltaTime);

		

	if (m_BossNpcOn)
	{
		m_BossNpcTime += DeltaTime;

		if (m_BossNpcTime > 15.f)
		{
			m_BossNpc = CreateObject<CBossNpc>("BossNpc");

			m_BossNpc->SetDirLR(1.f);

			m_BossNpc->SetPos(70.f, 500.f);

			m_BossNpcTime = 0.f;
		}
	}


	if (m_Player == nullptr)
	{
			m_TimeCheck += DELTA_TIME;

			if (m_TimeCheck > 3.f)
			{
				m_Player = CreateObject<CPlayer>("Player");

				SetPlayer(m_Player);

				m_Player->SetBossRound(true);
														
				m_Player->SetMoveSpeed(400.f);
												
				m_TimeCheck = 0.f;

			}
	}

	if (!m_BossMonster)
	{
		m_FinalBossTime += DELTA_TIME;

		{
			if (m_FinalBossTime > 3.f)
			{

				if (m_BossMonster == nullptr && m_FinalBossMonster == nullptr)
				{
					m_BossNpcOn = false;
					m_FinalBossMonster = CreateObject<CFinalBoss>("FinalBoss");
					m_FinalBossTime = 0.f;
				}
			}
		}
	}
	if (m_FinalBossMonster)
	{

		if (m_FinalBossMonster->GetDieOn())
		{
			m_FinalTime += DELTA_TIME;

			srand((int)time(0));
			rand();

			unsigned int a = (int)rand() % 4;
				


			if (m_FinalTime > 2.f && m_AngelOn)
			{

				CAngelCut* AngelCut = CreateObject<CAngelCut>("AngelCut");

				AngelCut->SetPos(1600.f, 600.f);

				GetSceneResource()->SoundPlay("Merci");


				if (a == 0)
				{
					m_AngelNpc = CreateObject<CAngelNpc>("Angel");
					m_AngelNpc->SetPos(210.f, 510.f);
					m_AngelOn = false;
				}

				if (a == 1)
				{

					m_AngelNpc = CreateObject<CAngelNpc>("Angel");
					m_AngelNpc->SetPos(210.f, 180.f);
					m_AngelOn = false;
				}
				if (a == 2)
				{

					m_AngelNpc = CreateObject<CAngelNpc>("Angel");
					m_AngelNpc->SetPos(870.f, 510.f);
					m_AngelOn = false;
				}
				if (a == 3)
				{

					m_AngelNpc = CreateObject<CAngelNpc>("Angel");
					m_AngelNpc->SetPos(870.f, 180.f);
					m_AngelOn = false;
				}

			}


		}


	}






	//if (m_FinalBossMonster->GetClearOn() && !m_FinalBossMonster )
	//{
	//	m_Time += DELTA_TIME;

	//	if (m_Time > 3.f)
	//	{
	//		CInput::GetInst()->ClearCallback();
	//		CSceneManager::GetInst()->CreateScene<CGameClearScene>();
	//	}
	//}


	//if (m_FinalBossMonster->GetDieOn())
	//{

	//	m_FinalTime += DELTA_TIME;
	//			
	//	if (m_FinalTime > 3.f && m_AngelOn )
	//	{
	//		m_AngelNpc = CreateObject<CAngelNpc>("Angel");
	//		m_AngelNpc->SetPos(210.f, 480.f);

	//		m_AngelOn = false;
	//	}

	//}



}

void CBossScene::CreateAnimationSequence()
{
	// ¿À¸¥ÂÊ ¸ØÃçÀÖ´Â»óÅÂ 
	GetSceneResource()->CreateAnimationSequence("PlayerRightIdle", "PlayerRightIdle", TEXT("astand.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRightIdle", 82.f * i, 0.f, 82.f, 73.f);
	}

	GetSceneResource()->SetColorKey("PlayerRightIdle", 255, 0, 255);

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

	GetSceneResource()->CreateAnimationSequence("BossRight", "BossRight", TEXT("BossRight.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BossRight", 200.f * i, 0.f, 200.f, 200.f);
	}

	GetSceneResource()->SetColorKey("BossRight", 100, 100, 100);

	// ¿ÞÂÊ
	GetSceneResource()->CreateAnimationSequence("BossLeft", "BossLeft", TEXT("BossLeft.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BossLeft", 200.f * i, 0.f, 200.f, 200.f);
	}

	GetSceneResource()->SetColorKey("BossLeft", 100, 100, 100);


	// À§
	GetSceneResource()->CreateAnimationSequence("BossUp", "BossUp", TEXT("BossUp.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BossUp", 200.f * i, 0.f, 200.f, 200.f);
	}

	GetSceneResource()->SetColorKey("BossUp", 100, 100, 100);


	// ¾Æ·¡
	GetSceneResource()->CreateAnimationSequence("BossDown", "BossDown", TEXT("BossDown.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BossDown", 200.f * i, 0.f, 200.f, 200.f);
	}

	GetSceneResource()->SetColorKey("BossDown", 100, 100, 100);

	// º¸½º ½ºÅÄµù
	GetSceneResource()->CreateAnimationSequence("BossStand", "BossStand", TEXT("BossStand.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BossStand", 200.f * i, 0.f, 200.f, 200.f);
	}

	GetSceneResource()->SetColorKey("BossStand", 100, 100, 100);

	// º¸½ºÁ×À½
	GetSceneResource()->CreateAnimationSequence("BossDie1", "BossDie1", TEXT("BossDie1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BossDie1", 183.f * i, 0.f, 183.f, 200.f);
	}

	GetSceneResource()->SetColorKey("BossDie1", 100, 100, 100);


	// º¸½ºÁ×À½ 2
	GetSceneResource()->CreateAnimationSequence("BossDie2", "BossDie2", TEXT("BossDie2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 1; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BossDie2", 183.f * i, 0.f, 200.f, 200.f);
	}

	GetSceneResource()->SetColorKey("BossDie2", 100, 100, 100);

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

	GetSceneResource()->CreateAnimationSequence("RocketBomb", "RocketBomb", TEXT("RocketBomb.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RocketBomb", 50.f * i, 0.f, 50.f, 55.f);
	}

	GetSceneResource()->SetColorKey("RocketBomb", 0, 0, 0);


	GetSceneResource()->CreateAnimationSequence("Marid", "Marid", TEXT("Marid.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Marid", 250.f * i, 0.f, 250.f, 200.f);
	}

	GetSceneResource()->SetColorKey("Marid", 100, 100, 100);

	GetSceneResource()->CreateAnimationSequence("Angel", "Angel", TEXT("Angel.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Angel", 80.f * i, 0.f, 80.f, 70.f);
	}

	GetSceneResource()->SetColorKey("Angel", 100, 100, 100);

	GetSceneResource()->CreateAnimationSequence("Barrier", "Barrier", TEXT("Barrier1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Barrier", 200.f * i, 0.f, 200.f, 200.f);
	}

	GetSceneResource()->SetColorKey("Barrier", 100, 100, 100);



}
