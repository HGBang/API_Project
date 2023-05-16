#include "GameManager.h"
#include "resource.h"
#include "Timer.h"
#include "GameObject/Player.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Scene/Scene.h"
#include "GameObject/GameObject.h"
#include "../Include/Resource/Texture/Texture.h"
#include "../Include/Scene/SceneResource.h"
#include "Collision/CollisionManager.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true;


CGameManager::CGameManager() : 
    m_EditMode(false)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(100);
}

CGameManager::~CGameManager()
{

    // delete m_Player;
    CSceneManager::DestoyInst();

    CPathManager::DestoyInst();

    CCollisionManager::DestoyInst();

    CInput::DestoyInst();

    CResourceManager::DestoyInst();

  

    SAFE_DELETE(m_Timer);

    SelectObject(m_hBackDC, m_hBackPrevBmp);
    DeleteObject(m_hBackBmp);
    DeleteDC(m_hBackDC);

    for (int i = 0; i < (int)EBrush_Type::Max; ++i)
    {
        DeleteObject(m_Brush[i]);
    }

    for (int i = 0; i < (int)EBrush_Type::Max; ++i)
    {
        DeleteObject(m_Pen[i]);
    }


    ReleaseDC(m_hWnd, m_hDC);
}

float CGameManager::GetFPS() const
{
    return m_Timer->GetFPS();
}

void CGameManager::Exit()
{
    DestroyWindow(m_hWnd);
}

bool CGameManager::Init(HINSTANCE hInst)
{
    m_hInst = hInst;

    m_RS.Width = 1280;
    m_RS.Height = 720;


   
   

    // ������ Ŭ���� ������ְ� ���

    Register();

    // ������ â�� �����ϰ� �����ش�

    Create();


   

    // ��� ������ �ʱ�ȭ
    if (!CPathManager::GetInst()->Init())
        return false;


    // ���ҽ� ������ �ʱ�ȭ
    if (!CResourceManager::GetInst()->Init())
        return false;


    // �浹������ �ʱ�ȭ
    if (!CCollisionManager::GetInst()->Init())
        return false;


    // �Է°����� �ʱ�ȭ
    if (!CInput::GetInst()->Init(m_hWnd))
        return false;



    // �������� ����
    if (!CSceneManager::GetInst()->Init())
        return false;


    // Ÿ�̸� ����
    m_Timer = new CTimer;

    m_Timer->Init();
    


    // DC�� ���´�

    m_hDC = GetDC(m_hWnd);

    m_FrameLimitTime = 1 / 60.f;


    // ����۸� ����� .

    m_hBackDC = CreateCompatibleDC(m_hDC);

    
    // ������â�� ũ��� ������ ũ���� ����ۿ� ��Ʈ���� ������ش�.
    m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_RS.Width, m_RS.Height);

    m_hBackPrevBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);

    
    m_TimeScale = 1.f;

    m_Brush[(int)EBrush_Type::Red] = CreateSolidBrush(RGB(255, 0, 0));
    m_Brush[(int)EBrush_Type::Green] = CreateSolidBrush(RGB(0, 255, 0));
    m_Brush[(int)EBrush_Type::Black] = CreateSolidBrush(RGB(0, 0, 0));
    m_Brush[(int)EBrush_Type::Blue] = CreateSolidBrush(RGB(0, 0, 255));
    m_Brush[(int)EBrush_Type::Yellow] = CreateSolidBrush(RGB(255, 255, 0));


    m_Pen[(int)EBrush_Type::Red] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    m_Pen[(int)EBrush_Type::Green] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    m_Pen[(int)EBrush_Type::Black] = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    m_Pen[(int)EBrush_Type::Blue] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    m_Pen[(int)EBrush_Type::Yellow] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));


   

	return true;
}

int CGameManager::Run()
{
    MSG msg;

    //GetMessage : �޽��� ť���� �޽����� �������� �Լ� �̴� .
    // �� , �޽��� ť�� ���������� �޽����� ���� ������ �� �Լ��� �������� �� ����.
    // �̷��� ���缭 ����ϰ� �ִ� ���� ���ŷ ����� �Ѵ� .
    // ť�� �� �����ִ� �ð��� �������� ����Ÿ���̶�� �θ���. 


    while (m_Loop)
    {

    if (PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE))
      {

      

        // �޼��� ť���� ������ �޼����� TranslteMessage �Լ��� �Ѱ��ָ� ���� Ű����
        // F1  ����� ���� Ű������ �Ǵ����ش�.
        // �̷��� Ű���� WM_KEYDOWN���� �޼����� �ν��� �ǰ� , 
        // ����Ű�� WM_CHAR�� �ν��� �ȴ�.
        // Ű�� ������ ����Ű�� ��� WM_CHAR �� ����������ϱ� ������ WM_KEYDOWN
        // �� �Ͼ�� ����Ű�� ��� WM_CHAR �޼����� �߰��� ���� �޼��� ť�� �־� �ش�. 
        TranslateMessage(&msg);

        //  DispatchMessage �Լ��� �޽���ť���� ������ �޼����� �޼��� ó�� �Լ��� �����ش� , WndProc�� �����ִ� ���̴� .
        DispatchMessage(&msg);
      }
    else
    {
        Logic();
    }


    }

    return (int)msg.wParam;
}

void CGameManager::Logic()
{

    //Ÿ�̸Ӹ� �����Ͽ� ��ŸŸ�� �� FPS�� ���Ѵ�.

    m_Timer->Update();

    float DeltaTime = m_Timer->GetDeltaTime() * m_TimeScale;


    m_DeltaTime = DeltaTime;

    Input(DeltaTime);


    if(Update(DeltaTime))
    return;

    if (PostUpdate(DeltaTime))
        return;


    Collision(DeltaTime);

    Render(DeltaTime);

    

}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
      
    //Rectangle(m_hBackDC, -1, -1, m_RS.Width + 1, m_RS.Height + 1);
    
    CSceneManager::GetInst()->Render(m_hBackDC, DeltaTime);

    CInput::GetInst()->Render(m_hBackDC, DeltaTime);


    //������ ����ۿ� ��� ������Ʈ�� ����� �Ǿ���
    // ���������� ����۸� ��ǥ�� ���ۿ� �׷�������.
    // BitBlt : �̹����� ���ϴ� DC�� ������ִ� �Լ�
    // 1������ : �̹�ġ ��� DC
    // 2������ : �ش� DC������ x��ǥ
    // 3������ : �ش� DC������ y��ǥ
    // 4������ : �׷��� �̹����� ����ũ��
    // 5������ : �׷��� �̹����� ����ũ��
    // 6������ : �̹����� ����� DC
    // 7������ : ����� DC�󿡼��� ���� x��ġ
    // 8������ : ����� DC�󿡼��� ���� y��ġ
    // 9������ : �׸��¹�� ����

    BitBlt(m_hDC, 0, 0, m_RS.Width, m_RS.Height, m_hBackDC, 0, 0, SRCCOPY);


    //m_Player->Render(m_hDC, DeltaTime);

   




 /*   m_TestRC.top += m_Dir;
    m_TestRC.bottom += m_Dir;

    if (m_TestRC.bottom >= 720)
    {
        m_Dir = -1;
    }
    else if (m_TestRC.top <= 0)
    {
        m_Dir = 1;
    }

    Rectangle(m_hDC, m_TestRC.left, m_TestRC.top, m_TestRC.right, m_TestRC.bottom);*/


}


void CGameManager::Input(float DeltaTime)
{

    CInput::GetInst()->Update(DeltaTime);
}

bool CGameManager::Update(float DeltaTime)
{
    CResourceManager::GetInst()->Update();

    //CInput::GetInst()->Update(DeltaTime);

    return CSceneManager::GetInst()->Update(DeltaTime);
}

bool CGameManager::PostUpdate(float DeltaTime)
{
    CInput::GetInst()->PostUpdate(DeltaTime);

    return CSceneManager::GetInst()->PostUpdate(DeltaTime);
}

void CGameManager::Register()
{
    // �������Ϳ� ����� ������ Ŭ���� ����ü�� ������ش�
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    //�޴��� ������� ���� �����Ѵ�,
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_MY220428);
    //����� �ڵ带 �����ڵ�� ���� �����Ѵ�.
    wcex.lpszClassName = TEXT("GameFramework");// szWindowClass;
    //������â �»�ܿ� ǥ���� ���� �������� ����Ѵ�.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
   

   //������ â�� �����Ѵ�.
   //1�� ���ڴ� ������ Ŭ������ ����� �̸��̴� .
   //2�� ���ڴ� Ÿ��Ʋ�ٿ� ǥ���� �̸��̴�.
   //3�����ڴ� �� ������â�� ��� ���������� �����ϴ� �ɼ��̴�.
   //4 , 5�� ���ڴ� ������â ��ǥ
   // �ȼ��� ���� ������� 1920,1080�ػ󵵶�� �ű⿡�� ���ϴ� ���� �־��ָ� �ش� ��ġ�� ������ �ȴ�.
   //6 , 7 ���� ���� ���� ũ��
   // 8�����ڴ� �θ������찡 ������ �θ��������� �ڵ��� ���� �Ѵ�.
   // ������ nullptr�� ����
   // 9�����ڴ� �޴��� �ִٸ� �޴��ڵ��� �־��ְ� ������ nullptr�� �����Ѵ�.
   // 10�����ڴ� ������ �ν��Ͻ��� �����Ͽ� �� ������ �ν��Ͻ��� ���� ������ â�� ������ְԵȴ� .
   // ������ â�� ������ְ� ������ ������ â�� �ڵ��� ��ȯ���ش�. 
   // HWND  �� ������ �ڵ��� �ǹ��Ѵ�. 

    m_hWnd = CreateWindowW(TEXT("GameFramework"), TEXT("GameFramework"), WS_OVERLAPPEDWINDOW,
        100, 0, 1280, 720, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return false;
    }


    RECT rc = { 0,0,m_RS.Width,m_RS.Height };

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    //������ ���� ũ��� ������â�� ũ�⸦ �����Ѵ�

    MoveWindow(m_hWnd, 50, 50, rc.right - rc.left, rc.bottom - rc.top, TRUE);


    ShowWindow(m_hWnd, SW_SHOW);

    // ���Լ��� ȣ���Ͽ� Ŭ���̾�Ʈ ������ ����� ���ŵǾ��ٸ� 0 �� �ƴѰ��� ��ȯ�ϰ� ,
    // ������ �������� ��� 0�� ��ȯ �Ѵ� .
    UpdateWindow(m_hWnd);


    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
  
    case WM_DESTROY:
        m_Loop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


