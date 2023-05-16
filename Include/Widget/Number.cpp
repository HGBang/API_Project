
#include "Number.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

CNumber::CNumber() :
	m_Number(0)
{
}

CNumber::CNumber(const CNumber& widget) :
	CWidget(widget)
{
}

CNumber::~CNumber()
{
}

void CNumber::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CNumber::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#ifdef UNICODE


void CNumber::SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CNumber::SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#else

void CNumber::SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CNumber::SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#endif // UNICODE

void CNumber::SetColorKey(
	unsigned char r, unsigned char g, unsigned char b)
{
	if (m_Texture)
		m_Texture->SetColorKey(r, g, b);
}

bool CNumber::Init()
{
	return true;
}

void CNumber::Update(float DeltaTime)
{
	// 숫자를 각 자리별로 분할한다.
	if (m_Number == 0)
	{
		m_vecNumber.clear();
		m_vecNumber.push_back(0);
	}

	else
	{
		int	Number = m_Number;

		std::stack<int>	NumberStack;

		// 123 % 10 = 3    123 / 10 = 12   12 % 10 = 2  12 / 10 = 1   1 % 10 = 1   1 / 10 = 0
		while (Number > 0)
		{
			NumberStack.push(Number % 10);
			Number /= 10;
		}

		m_vecNumber.clear();

		while (!NumberStack.empty())
		{
			m_vecNumber.push_back(NumberStack.top());
			NumberStack.pop();
		}
	}
}

void CNumber::PostUpdate(float DeltaTime)
{
}

void CNumber::Render(HDC hDC, float DeltaTime)
{
	if (!m_vecNumber.empty())
	{
		Vector2	RenderPos = m_Pos + m_Owner->GetPos();

		if (m_Texture)
		{
			size_t	Size = m_vecNumber.size();

			for (size_t i = 0; i < Size; ++i)
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					if (m_Texture->GetEnableColorKey())
					{
						TransparentBlt(hDC, (int)RenderPos.x + (int)(i * m_Size.x), (int)RenderPos.y,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetDC(),
							(int)(m_vecNumber[i] * m_Size.x), 0,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetColorKey());
					}
					
					else
					{
						BitBlt(hDC, (int)RenderPos.x + (int)(i * m_Size.x), (int)RenderPos.y,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetDC(),
							(int)(m_vecNumber[i] * m_Size.x), 0, SRCCOPY);
					}
				}

				else
				{
					if (m_Texture->GetEnableColorKey())
					{
						TransparentBlt(hDC, (int)RenderPos.x + (int)(i * m_Size.x), (int)RenderPos.y,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetDC(m_vecNumber[i]),
							0, 0, (int)m_Size.x, (int)m_Size.y,
							m_Texture->GetColorKey());
					}

					else
					{
						BitBlt(hDC, (int)RenderPos.x + (int)(i * m_Size.x), (int)RenderPos.y,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetDC(m_vecNumber[i]),
							0, 0, SRCCOPY);
					}
				}
			}
		}
	}
}

void CNumber::Render(HDC hDC, const Vector2& Pos, float DeltaTime)
{
	if (!m_vecNumber.empty())
	{
		Vector2	RenderPos = Pos;

		if (m_Texture)
		{
			size_t	Size = m_vecNumber.size();

			for (size_t i = 0; i < Size; ++i)
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					if (m_Texture->GetEnableColorKey())
					{
						TransparentBlt(hDC, (int)RenderPos.x + (int)(i * m_Size.x), (int)RenderPos.y,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetDC(),
							(int)(m_vecNumber[i] * m_Size.x), 0,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetColorKey());
					}

					else
					{
						BitBlt(hDC, (int)RenderPos.x + (int)(i * m_Size.x), (int)RenderPos.y,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetDC(),
							(int)(m_vecNumber[i] * m_Size.x), 0, SRCCOPY);
					}
				}

				else
				{
					if (m_Texture->GetEnableColorKey())
					{
						TransparentBlt(hDC, (int)RenderPos.x + (int)(i * m_Size.x), (int)RenderPos.y,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetDC(m_vecNumber[i]),
							0, 0, (int)m_Size.x, (int)m_Size.y,
							m_Texture->GetColorKey());
					}

					else
					{
						BitBlt(hDC, (int)RenderPos.x + (int)(i * m_Size.x), (int)RenderPos.y,
							(int)m_Size.x, (int)m_Size.y,
							m_Texture->GetDC(m_vecNumber[i]),
							0, 0, SRCCOPY);
					}
				}
			}
		}
	}
}
