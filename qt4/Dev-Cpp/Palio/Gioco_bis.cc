#include "Gioco.h"
#include "Utilities.h"
#include "resource.h"

CppCntrl::CppCntrl()
{
    nStyle = WS_CHILD|WS_VISIBLE;
    hCntrl = NULL;
    Width = 100;
    Height = 30;
}

CppCntrl::~CppCntrl()
{
    if (hCntrl)
        DestroyWindow(hCntrl);
}

HWND CppCntrl::Create(HWND hParent)
{
    if (!hInst)
        hInst = (HINSTANCE)GetWindowLong(hParent,GWL_HINSTANCE);
    
    hCntrl = CreateWindowEx(0,                          //more or 'extended' styles
                    chClassName,                        //the 'class' of window to create
                    chCaption,                          //the window title
                    nStyle,                             //window style: how it looks
                    Left,                               //window position: left
                    Top,                                //window position: top
                    Width,                              //window width
                    Height,                             //window height
                    hParent,                            //parent window handle
                    (HMENU)nID,                         //handle to wnd menu or cntrl ID
                    hInst,                              //application instance
                    (VOID*)this);                       //store pointer to class
    return hCntrl;
}

Gioco::Gioco()
{
    SetWndCaption(TEXT("TDPalio"));
    SetWndClassName(TEXT("Tempo di Palio"));
    hAppWnd=NULL;
    Left=GetSystemMetrics(SM_CXSCREEN)/4;
    Top=GetSystemMetrics(SM_CYSCREEN)/4;
    Width=GetSystemMetrics(SM_CXSCREEN)/2;
    Height=GetSystemMetrics(SM_CYSCREEN)/2;
    nStyle=WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_THICKFRAME&~WS_SIZEBOX;
    nClassStyle=CS_HREDRAW|CS_VREDRAW;
}

Gioco::~Gioco()
{}

HWND Gioco::Create(HWND hParent)
{
    HMENU menu;
    
    WNDCLASSEX wcx;    //this structure is used for storing information about the wnd 'class'
    wcx.cbSize           = sizeof(WNDCLASSEX);                //byte size of WNDCLASSEX struct
    wcx.style            = nClassStyle;                       //ensure wnd is always redrawn
    wcx.lpfnWndProc      = (WNDPROC)MainWndProc;              //pointer to the Window Procedure
    wcx.cbClsExtra       = 0;                                 //Extra bytes for 'class' wnds
    wcx.cbWndExtra       = 0;                                 //Extra bytes for this wnd
    wcx.hInstance        = hInst;				              //Application instance
    wcx.hIcon            = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wcx.hCursor          = LoadCursor(NULL,IDC_ARROW);        //Cursor for wnd
    wcx.hbrBackground    = (HBRUSH)(COLOR_BTNFACE+1);         //Background wnd colour
    wcx.lpszMenuName     = NULL;                             //Name of wnd menu
    wcx.lpszClassName    = GetWndClassName();                 //Name of this wnd 'class'
    wcx.hIconSm          = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));

    if (!RegisterClassEx(&wcx))
    {
        MessageBox( NULL,
                TEXT("Failed to register wnd class"),
                TEXT("ERROR"),
                MB_OK|MB_ICONERROR);
        return NULL;
    }

    HWND hwnd;    //the wnd handle
    hwnd = CreateWindowEx(nExStyle,                           //more or 'extended' styles
                    chClassName,                        //the 'class' of window to create
                    chCaption,                          //the window title
                    nStyle,                             //window style: how it looks
                    Left,                               //window position: left
                    Top,                                //window position: top
                    Width,                              //window width
                    Height,                             //window height
                    hParent,                            //parent window handle
                    (HMENU)nID,                         //handle to wnd menu or cntrl ID
                    hInst,                              //application instance
                    (VOID*)this);                       //store pointer to class
    
    if (!hwnd)
    {
        MessageBox( NULL,
                TEXT("Failed to create wnd"),
                TEXT("ERROR"), 
                MB_OK|MB_ICONERROR);
        return NULL;
    }

    if (!hAppWnd)
        hAppWnd = hwnd;
        
    menu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU));
    SetMenu(hwnd, menu);

    ShowWindow(hwnd, SW_SHOW); 
    UpdateWindow(hwnd);
    return hwnd;
}

TCHAR* Gioco::GetWndCaption()
{
    return chCaption;
}

TCHAR* Gioco::GetWndClassName()
{
    return chClassName;
}

void Gioco::SetInstance(HINSTANCE	hInstance)
{
    hInst = hInstance;
}

void Gioco::SetWndCaption(TCHAR* chCap)
{
    if ((chCap)&&(lstrlen(TEXT(chCap))<256))
	{
		lstrcpy(chCaption,chCap);
	}
}

void Gioco::SetWndClassName(TCHAR* chClass)
{
    if ((chClass)&&(lstrlen(TEXT(chClass))<100))
	{
		lstrcpy(chClassName,chClass);
	}
}

TCHAR* CppCntrl::GetWndCaption()
{
    return chCaption;
}

TCHAR* CppCntrl::GetWndClassName()
{
    return chClassName;
}

void CppCntrl::SetInstance(HINSTANCE	hInstance)
{
    hInst = hInstance;
}

void CppCntrl::SetWndCaption(TCHAR* chCap)
{
    if ((chCap)&&(lstrlen(TEXT(chCap))<256))
	{
		lstrcpy(chCaption,chCap);
	}
}

void CppCntrl::SetWndClassName(TCHAR* chClass)
{
    if ((chClass)&&(lstrlen(TEXT(chClass))<100))
	{
		lstrcpy(chClassName,chClass);
	}
}
