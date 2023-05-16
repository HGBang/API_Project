#pragma once
#include "WidgetWindow.h"
class CClearSecondWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CClearSecondWindow();
    virtual ~CClearSecondWindow();

private:
    CSharedPtr<class CText> m_Text;
    TCHAR       m_AddText[32];
    float       m_TextTime;
    int         m_AddCount;
    CSharedPtr<class CNumber>   m_Hour;
    CSharedPtr<class CNumber>   m_Minute;
    CSharedPtr<class CNumber>   m_Second;
    CSharedPtr<class CText>     m_FPSText;
    float       m_LoadingTime;


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void StartButtonCallback();
    void EditButtonCallback();
    void EndButtonCallback();
};

