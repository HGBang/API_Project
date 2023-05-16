#pragma once
#include "../Ref.h"

class CWidgetComponent :
    public CRef
{
    friend class CGameObject;

protected:
    CWidgetComponent();
    CWidgetComponent(const CWidgetComponent& widget);
    virtual ~CWidgetComponent();

private:
    class CGameObject* m_Owner;
    class CScene* m_Scene;
    CSharedPtr<class CWidget>   m_Widget;
    Vector2     m_Pos;

public:
    Vector2 GetPos() const;
    float GetBottom() const;
    

    void SetPos(float x, float y)
    {
        m_Pos = Vector2(x, y);
    }

    void SetPos(const Vector2& Pos)
    {
        m_Pos = Pos;
    }

    void SetWidget(class CWidget* Widget);

    class CWidget* GetWidget() const
    {
        return m_Widget;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);

public:
    template <typename T>
    T* GetWidget() const
    {
        return (T*)m_Widget.Get();
    }


    template <typename T>
    T* CreateWidget(const std::string& Name)
    {
        T* Widget = new T;

        Widget->SetName(Name);
        Widget->m_Scene = m_Scene;
     
        if (!Widget->Init())
        {
            SAFE_DELETE(Widget);
            return nullptr;
        }

        m_Widget = Widget;

        return (T*)Widget;
    }
};

