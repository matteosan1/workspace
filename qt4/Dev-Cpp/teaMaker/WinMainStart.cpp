//===========================================================================================
//APPLICATION ENTRY POINT - Copyright © 2000 Ken Fitlike.
//===========================================================================================
//
// Two global functions appear here: the WinMain function which is the essential win32 
// application entry point function required by windows and the MainWndProc function which
// is declared elsewhere but implemented here just to keep all the application globals
// together. MainWndProc is the window procedure for the main application window.
//
//-------------------------------------------------------------------------------------------
//FILENAME: WinMainStart.cpp
//-------------------------------------------------------------------------------------------

#include "MainWin.h"
#include <iostream>

MainWin App;	//declare instance of CppWnd object
//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
//store application instance
App.SetInstance(hInstance);
//register and create wnd,checking the return value to ensure that a valid wnd handle has
//been made.
if (App.Create())
    {
    MSG Msg;    //a simple structure for storing message information
    //start message loop
    while (GetMessage(&Msg,NULL,0,0))
        {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
        }
    return Msg.wParam;
    }
return 0;
}
//-------------------------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return App.CppWndProc(hwnd,Message,wParam,lParam);
}
//-------------------------------------------------------------------------------------------
BOOL CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return App.aggio->PippoProc(hwnd,Message,wParam,lParam);
}

