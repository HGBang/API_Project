
#include "WidgetWindow.h"

CWidgetWindow::CWidgetWindow() :
	m_Scene(nullptr),
	m_ZOrder(0)
{
}

CWidgetWindow::~CWidgetWindow()
{
}

bool CWidgetWindow::Init()
{
	return true;
}

void CWidgetWindow::Update(float DeltaTime)
{
	size_t	Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->Update(DeltaTime);
	}
}

void CWidgetWindow::PostUpdate(float DeltaTime)
{
	size_t	Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->PostUpdate(DeltaTime);
	}
}

void CWidgetWindow::Render(HDC hDC, float DeltaTime)
{
	size_t	Size = m_vecWidget.size();

	if (Size > 1)
	{
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), CWidgetWindow::SortWidget);
	}


	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->Render(hDC, DeltaTime);
	}
}

void CWidgetWindow::SortCollision()
{
	if (m_vecWidget.size() > 1)
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), CWidgetWindow::SortCollisionWidget);
}

bool CWidgetWindow::CollisionMouse(class CWidget** Widget, const Vector2& Pos)
{
	if (Pos.x < m_Pos.x)
		return false;

	else if (Pos.y < m_Pos.y)
		return false;

	else if (Pos.x > m_Pos.x + m_Size.x)
		return false;

	else if (Pos.y > m_Pos.y + m_Size.y)
		return false;

	size_t	WidgetCount = m_vecWidget.size();

	for (size_t i = 0; i < WidgetCount; ++i)
	{
		if (m_vecWidget[i]->CollisionMouse(Pos))
		{
			*Widget = m_vecWidget[i];
			return true;
		}
	}

	return false;
}

bool CWidgetWindow::SortCollisionWidget(const CSharedPtr<class CWidget>& Src,
	const CSharedPtr<class CWidget>& Dest)
{
	return Src->GetZOrder() > Dest->GetZOrder();;
}

bool CWidgetWindow::SortWidget(const CSharedPtr<class CWidget>& Src, const CSharedPtr<class CWidget>& Dest)
{
	return Src->GetZOrder() < Dest->GetZOrder();;
}
