#include <windows.h>

#include "Gioco.h"

Gioco gioco;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
    MSG messages; 
    gioco.SetInstance(hThisInstance);
    if (gioco.Create())
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
    return gioco.WndProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK NewGameProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return gioco.nuovoGioco->DlgProc(hwnd,Message,wParam,lParam);
}

