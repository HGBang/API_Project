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


   
   

    // 윈도우 클래스 만들어주고 등록

    Register();

    // 윈도우 창을 생성하고 보여준다

    Create();


   

    // 경로 관리자 초기화
    if (!CPathManager::GetInst()->Init())
        return false;


    // 리소스 관리자 초기화
    if (!CResourceManager::GetInst()->Init())
        return false;


    // 충돌관리자 초기화
    if (!CCollisionManager::GetInst()->Init())
        return false;


    // 입력관리자 초기화
    if (!CInput::GetInst()->Init(m_hWnd))
        return false;



    // 장면관리자 생성
    if (!CSceneManager::GetInst()->Init())
        return false;


    // 타이머 생성
    m_Timer = new CTimer;

    m_Timer->Init();
    


    // DC를 얻어온다

    m_hDC = GetDC(m_hWnd);

    m_FrameLimitTime = 1 / 60.f;


    // 백버퍼를 만든다 .

    m_hBackDC = CreateCompatibleDC(m_hDC);

    
    // 윈도우창의 크기와 동일한 크기의 백버퍼용 비트맵을 만들어준다.
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

    //GetMessage : 메시지 큐에서 메시지를 꺼내오는 함수 이다 .
    // 단 , 메시지 큐가 비어있을경우 메시지가 들어올 때까지 이 함수를 빠져나올 수 없다.
    // 이렇게 멈춰서 대기하고 있는 것을 블로킹 모드라고 한다 .
    // 큐가 비어서 멈춰있는 시간을 윈도우의 데드타임이라고 부른다. 


    while (m_Loop)
    {

    if (PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE))
      {

      

        // 메세지 큐에서 꺼내온 메세지를 TranslteMessage 함수로 넘겨주면 문자 키인지
        // F1  방향기 같은 키인지를 판단해준다.
        // 이러한 키들은 WM_KEYDOWN으로 메세지가 인식이 되고 , 
        // 문자키는 WM_CHAR로 인식이 된다.
        // 키를 누르면 문자키의 경우 WM_CHAR 도 만들어져야하기 때문에 WM_KEYDOWN
        // 이 일어나면 문자키의 경우 WM_CHAR 메세지를 추가로 만들어서 메세지 큐에 넣어 준다. 
        TranslateMessage(&msg);

        //  DispatchMessage 함수는 메시지큐에서 꺼내온 메세지를 메세지 처리 함수에 보내준다 , WndProc로 보내주는 것이다 .
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

    //타이머를 갱신하여 델타타임 및 FPS를 구한다.

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


    //위에서 백버퍼에 모든 오브젝트가 출력이 되었다
    // 마지막으로 백버퍼를 주표면 버퍼에 그려ㅐㄴ다.
    // BitBlt : 이미지를 원하는 DC에 출력해주는 함수
    // 1번인자 : 이미치 출력 DC
    // 2번인자 : 해당 DC에서의 x좌표
    // 3번인자 : 해당 DC에서의 y좌표
    // 4번인자 : 그려낼 이미지의 가로크기
    // 5번인자 : 그려낼 이미지의 세로크기
    // 6번인자 : 이미지를 출력할 DC
    // 7번인자 : 출력할 DC상에서의 시작 x위치
    // 8번인자 : 출력할 DC상에서의 시작 y위치
    // 9번인자 : 그리는방법 지정

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
    // 레지스터에 등록할 윈도우 클래스 구조체를 만들어준다
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

    //메뉴를 사용할지 말지 결정한다,
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_MY220428);
    //등록할 코드를 유니코드로 할지 결정한다.
    wcex.lpszClassName = TEXT("GameFramework");// szWindowClass;
    //윈도우창 좌상단에 표시할 작은 아이콘을 등록한다.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
   

   //윈도우 창을 생성한다.
   //1번 인자는 윈도우 클래스에 등로한 이름이다 .
   //2번 인자는 타이틀바에 표시할 이름이다.
   //3번인자는 이 윈도우창이 어떻게 생성될지를 지정하는 옵션이다.
   //4 , 5번 인자는 윈도우창 좌표
   // 픽셀로 지정 예를들어 1920,1080해상도라면 거기에서 원하는 값을 넣어주면 해당 위치에 나오게 된다.
   //6 , 7 번은 가로 세로 크기
   // 8번인자는 부모윈도우가 있으면 부모윈도우의 핸들을 지정 한다.
   // 없으면 nullptr로 지정
   // 9번인자는 메뉴가 있다면 메뉴핸들을 넣어주고 없으면 nullptr을 지정한다.
   // 10번인자는 윈도우 인스턴스를 지정하여 이 윈도우 인스턴스에 속한 윈도우 창을 만들어주게된다 .
   // 윈도우 창을 만들어주고 생성된 윈도우 창의 핸들을 반환해준다. 
   // HWND  가 윈도우 핸들을 의미한다. 

    m_hWnd = CreateWindowW(TEXT("GameFramework"), TEXT("GameFramework"), WS_OVERLAPPEDWINDOW,
        100, 0, 1280, 720, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return false;
    }


    RECT rc = { 0,0,m_RS.Width,m_RS.Height };

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    //위에서 얻어온 크기로 윈도우창의 크기를 변경한다

    MoveWindow(m_hWnd, 50, 50, rc.right - rc.left, rc.bottom - rc.top, TRUE);


    ShowWindow(m_hWnd, SW_SHOW);

    // 이함수를 호출하여 클라이언트 영역이 제대로 갱신되었다면 0 이 아닌값을 반환하고 ,
    // 갱신이 실패했을 경우 0을 반환 한다 .
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


