#pragma once

#include "Widget.h"

enum class EProgressBar_Texture_Type
{
    Back,
    Bar,
    End
};

enum class EProgressBar_Dir
{
    LeftToRight,
    RightToLeft,
    BottomToTop,
    TopToBottom,
    End
};

class CProgressBar :
    public CWidget
{
    friend class CWidgetComponent;
    friend class CWidgetWindow;

protected:
    CProgressBar();
    CProgressBar(const CProgressBar& widget);
    virtual ~CProgressBar();

protected:
    CSharedPtr<class CTexture>  m_Texture[(int)EProgressBar_Texture_Type::End];
    EProgressBar_Dir    m_Dir;
    float               m_Value;    // 0 ~ 1 사이의 값
    Vector2             m_BarSize;
    Vector2             m_BarPos;

public:
    void SetBarDir(EProgressBar_Dir Dir)
    {
        m_Dir = Dir;
    }

    void SetValue(float Value)
    {
        m_Value = Value;

        if (m_Value > 1.f)
            m_Value = 1.f;

        else if (m_Value < 0.f)
            m_Value = 0.f;
    }

    void AddValue(float Value)
    {
        m_Value += Value;

        if (m_Value > 1.f)
            m_Value = 1.f;

        else if (m_Value < 0.f)
            m_Value = 0.f;
    }

public:
    void SetTexture(EProgressBar_Texture_Type Type, const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type Type, const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE

    void SetTexture(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::wstring>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

    void SetTexture(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::string>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif

    void SetColorKey(EProgressBar_Texture_Type Type, unsigned char r, unsigned char g, unsigned char b);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime);
};

