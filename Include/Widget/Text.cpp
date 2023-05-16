#include "Text.h"
#include "../Resource/Font/Font.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"


CText::CText()
{
	m_Count = 0;
	m_Capacity = 32;

	m_Text = new TCHAR[m_Capacity];

	memset(m_Text, 0, sizeof(TCHAR) * m_Capacity);

	m_TextColor = RGB(0, 0, 0);
	m_ShadowColor = RGB(30, 30, 30);
	m_Shadow = false;
	m_ShadowOffset = Vector2(1.f, 1.f);
}

CText::CText(const CText& widget) :
	CWidget(widget)
{
}

CText::~CText()
{
	SAFE_DELETE_ARRAY(m_Text);
}

void CText::SetFont(const std::string& Name)
{
	m_Font = m_Scene->GetSceneResource()->FindFont(Name);
}

bool CText::Init()
{
	m_Font = m_Scene->GetSceneResource()->FindFont("DefaultFont");
	return true;
}

void CText::Update(float DeltaTime)
{
}

void CText::PostUpdate(float DeltaTime)
{
}

void CText::Render(HDC hDC, float DeltaTime)
{

	m_Font->SetFont(hDC);

	Vector2	RenderPos = m_Pos + m_Owner->GetPos();

	SetBkMode(hDC, TRANSPARENT);

	//그림자를 출력해야 한다면 그림자 먼저 출력한다 . 
	if (m_Shadow)
	{
		Vector2 ShadowPos = RenderPos + m_ShadowOffset;
		::SetTextColor(hDC, m_ShadowColor);
		TextOut(hDC, (int)ShadowPos.x, (int)ShadowPos.y, m_Text, m_Count);
	}


	::SetTextColor(hDC, m_TextColor);
	TextOut(hDC, (int)RenderPos.x, (int)RenderPos.y, m_Text, m_Count);


	m_Font->ResetFont(hDC);

}

void CText::Render(HDC hDC, const Vector2& Pos, float DeltaTime)
{
	m_Font->SetFont(hDC);

	Vector2	RenderPos = Pos;

	SetBkMode(hDC, TRANSPARENT);

	//그림자를 출력해야 한다면 그림자 먼저 출력한다 . 
	if (m_Shadow)
	{
		Vector2 ShadowPos = RenderPos + m_ShadowOffset;
		::SetTextColor(hDC, m_ShadowColor);
		TextOut(hDC, (int)ShadowPos.x, (int)ShadowPos.y, m_Text, m_Count);
	}


	::SetTextColor(hDC, m_TextColor);
	TextOut(hDC, (int)RenderPos.x, (int)RenderPos.y, m_Text, m_Count);


	m_Font->ResetFont(hDC);
}