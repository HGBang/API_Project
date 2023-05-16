#pragma once
#include "Widget.h"
class CText :
    public CWidget
{
    friend class CWidgetComponent;
    friend class CWidgetWindow;

protected:
    CText();
    CText(const CText& widget);
    virtual ~CText();

protected:
    TCHAR*     m_Text;
    int        m_Count;
    int        m_Capacity;
    COLORREF   m_TextColor;
    COLORREF   m_ShadowColor;
    bool       m_Shadow;
    Vector2    m_ShadowOffset;
    CSharedPtr<class CFont> m_Font;

public:
    void SetTextColor(unsigned char r, unsigned char g, unsigned char b)
    {
        m_TextColor = RGB(r, g, b);
    }

    void SetTextShadowColor(unsigned char r, unsigned char g, unsigned char b)
    {
        m_ShadowColor = RGB(r, g, b);
    }

    void EnableShadow(bool Shadow)
    {
        m_Shadow = Shadow;
    }

    void SetShadowOffset(float x, float y)
    {
        m_ShadowOffset = Vector2(x, y);
    }

    void SetText(const TCHAR* Text)
    {
        int Length = lstrlen(Text);
        
        if (Length + 1 > m_Capacity)
        {
            m_Capacity = Length + 1;

            SAFE_DELETE_ARRAY(m_Text);

            m_Text = new TCHAR[m_Capacity];
            memset(m_Text, 0, sizeof(TCHAR) * m_Capacity);
        }

        lstrcpy(m_Text, Text);

        m_Count = lstrlen(m_Text);
    }

    void AddText(const TCHAR Text)
    {
        int Length = m_Count + 1;

        if (Length + 1 > m_Capacity)
        {
            m_Capacity = Length + 1;

            TCHAR* NewText = new TCHAR[m_Capacity];
            memset(NewText, 0, sizeof(TCHAR) * m_Capacity);

            lstrcpy(NewText, m_Text);

            SAFE_DELETE_ARRAY(m_Text);

            m_Text = NewText;
        }

        m_Text[m_Count] = Text;

        ++m_Count;
    }

    void AddText(const TCHAR* Text)
    {
        int Length = m_Count + lstrlen(Text);

        if (Length + 1 > m_Capacity)
        {
            m_Capacity = Length + 1;
                      
            TCHAR* NewText = new TCHAR[m_Capacity];
            memset(NewText, 0, sizeof(TCHAR) * m_Capacity);

            lstrcpy(NewText, m_Text);

            SAFE_DELETE_ARRAY(m_Text);

            m_Text = NewText;
        }

        lstrcat(m_Text, Text);

        m_Count += lstrlen(Text);
    }

    void pop_back()
    {
        --m_Count;

        m_Text[m_Count] = 0;
    }

    void clear()
    {
        m_Count = 0;

        m_Text[m_Count] = 0;
    }

    void SetFont(const std::string& Name);



public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime);
};

