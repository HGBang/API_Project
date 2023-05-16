#pragma once
#include "WidgetWindow.h"
class CCharacterHUD :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CCharacterHUD();
    virtual ~CCharacterHUD();

protected:
    CSharedPtr<class CProgressBar>  m_HPBar;
    CSharedPtr<class CImage>  m_HPBarFrame;
    CSharedPtr<class CText>     m_FPSText;

public:
    void SetHP(float HP);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

