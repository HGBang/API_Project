
#include"GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

   if (!CGameManager::GetInst()->Init(hInstance))
   {
       CGameManager::DestoyInst();
       return 0;
   }

   int ReturnValue = CGameManager::GetInst()->Run();

   CGameManager::DestoyInst();

   return ReturnValue;

}
