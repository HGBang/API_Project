
#include "CharacterHUD.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ProgressBar.h"
#include "Image.h"
#include "Text.h"

CCharacterHUD::CCharacterHUD()
{
}

CCharacterHUD::~CCharacterHUD()
{
}

void CCharacterHUD::SetHP(float HP)
{
	m_HPBar->SetValue(HP);
}

bool CCharacterHUD::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	/*m_Scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"1Up.wav");
	m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Stun.wav");*/

	//SetSize(210.f, 110.f);
	//SetPos(50.f, 50.f);

	//m_HPBarFrame = CreateWidget<CImage>("HPBarFrame");

	//m_HPBarFrame->SetTexture("BarFrame", TEXT("BarBack.bmp"));
	//m_HPBarFrame->SetColorKey(255, 0, 255);

	//m_HPBarFrame->SetSize(220.f, 50.f);

	//m_HPBar = CreateWidget<CProgressBar>("HPBar");

	//m_HPBar->SetTexture(EProgressBar_Texture_Type::Bar, "HUDHPBar", TEXT("BarDefault.bmp"));

	//m_HPBar->SetSize(200.f, 30.f);
	//m_HPBar->SetPos(10.f, 10.f);
	//m_HPBar->SetBarDir(EProgressBar_Dir::LeftToRight);

	m_FPSText = CreateWidget<CText>("Text");

	m_FPSText->SetText(TEXT("FPS"));
	m_FPSText->SetPos(900.f, -50.f);
	m_FPSText->SetTextColor(255, 255, 255);
	m_FPSText->EnableShadow(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);

	return true;
}

void CCharacterHUD::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	float FPS = CGameManager::GetInst()->GetFPS();

	char Text[256] = {};
	sprintf_s(Text, "FPS : %.5f", FPS);

	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	m_FPSText->SetText(Unicode);
}
