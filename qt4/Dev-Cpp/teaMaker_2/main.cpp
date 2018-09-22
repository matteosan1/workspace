#include "formazioni.h"

using namespace std;

Formazioni formazioni;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
    InitCommonControls();
    MSG messages; 
    formazioni.SetInstance(hThisInstance);
    if (formazioni.Create())
    { 
        while (GetMessage (&messages, NULL, 0, 0))
        {
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }
    }
    
    return messages.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return formazioni.WndProc(hwnd,Message,wParam,lParam);
}
