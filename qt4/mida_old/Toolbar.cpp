//=========================================================================================
//COMMON CONTROLS: TOOLBAR - Copyright © 2000-2002 Ken Fitlike
//=========================================================================================
//API functions used: CreateWindowEx,DefWindowProc,DispatchMessage,GetMessage,
//GetSystemMetrics,InitCommonControlsEx,LoadImage,MessageBox,MoveWindow,PostQuitMessage,
//RegisterClassEx,SendMessage,ShowWindow,UpdateWindow,TranslateMessage,WinMain.
//=========================================================================================
//
//=========================================================================================
#if !defined CommonCntrlToolbarH
#define      CommonCntrlToolbarH
//=========================================================================================
//#define UNICODE         //make active when compiling on WinNT/2000 (W-fns)
#define WIN32_LEAN_AND_MEAN //optional: no MFC
#include <windows.h>        //include all the basics
#if defined __MINGW_H
#define _WIN32_IE 0x0400
#endif
//DevC++(MinGW) must link with -lcomctl32. bcc5.5,msvc (must link with comctl32.lib)
#include <commdlg.h>

#include <commctrl.h>
//=========================================================================================
//LCC-WIN32 Specific: LR_SHARED (used by LoadImage API function) is currently not defined
//in WIN.H. If you have a later version of this lcc-win32 header that defines LR_SHARED
//then you may safely discard the following conditional definition.
#if !defined LR_SHARED
#define LR_SHARED 0x00008000   //required only for lcc-win32 (Aug 2002)
#endif
//=========================================================================================
//declare the Window procedure where all messages will be handled


static HANDLE hDevMode, hDevNames;
RECT rcMargin;
HANDLE GetDevMode()
{
    PAGESETUPDLG psd;
    
    ZeroMemory(&psd, sizeof psd);
    psd.lStructSize = sizeof psd;
    psd.Flags = PSD_RETURNDEFAULT;

    PageSetupDlg(&psd);
    CopyRect(&rcMargin, &psd.rtMargin);
    hDevMode = psd.hDevMode;
    hDevNames = psd.hDevNames;

    return psd.hDevMode;
}


LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
//declare some global variables
HBITMAP hBmp;
HINSTANCE g_hInst;          //application instance
HWND      g_hwndToolbar;    //handle to toolbar common control
//=========================================================================================
//declare the Window procedure where all messages will be handled
LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
//=========================================================================================
//start the application; all win32 applications require a WinMain function
//that the windows operating system looks for as an entry point to that application
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
HWND    hwnd;    //the wnd handle
MSG     Msg;     //a simple structure for storing message information
HICON   hIcon;   //window icon
HCURSOR hCursor; //window cursor
//declare and initialise wnd registration information variables
TCHAR chClassName[]=TEXT("SIMPLEWND");
WNDCLASSEX wcx;    //this structure is used for storing information about the wnd 'class'
g_hInst=hInstance; //store the application instance
//use 'LoadImage' to load wnd class icon and cursor as it supercedes the obsolete functions
//'LoadIcon' and 'LoadCursor', although these functions will still work. Because the icon and
//cursor are loaded from system resources ie they are shared, it is not necessary to free the
//image resources with either 'DestroyIcon' or 'DestroyCursor'.
hIcon=(HICON)LoadImage(0,IDI_APPLICATION,IMAGE_ICON,0,0,LR_SHARED);
hCursor=(HCURSOR)LoadImage(0,IDC_ARROW,IMAGE_CURSOR,0,0,LR_SHARED);
wcx.cbSize           = sizeof(WNDCLASSEX);              //byte size of WNDCLASSEX struct
wcx.style            = CS_HREDRAW|CS_VREDRAW;           //ensure wnd is always redrawn
wcx.lpfnWndProc      = (WNDPROC)WndProc;                //pointer to the Window Procedure
wcx.cbClsExtra       = 0;                               //Extra bytes for 'class' wnds
wcx.cbWndExtra       = 0;                               //Extra bytes for this wnd
wcx.hInstance        = hInstance;                       //Application instance
wcx.hIcon            = hIcon;                           //Application icon
wcx.hCursor          = hCursor;                         //Cursor for wnd
wcx.hbrBackground    = (HBRUSH)(COLOR_BTNFACE+1);       //Background wnd colour
wcx.lpszMenuName     = NULL;                            //Name of wnd menu
wcx.lpszClassName    = chClassName;                     //Name of this wnd 'class'
wcx.hIconSm          = NULL;                            //Icon in top-left corner of wnd
//Register the wnd class with the Windows system
if (!RegisterClassEx(&wcx))
    {
    //Registration has failed so inform the user
    MessageBox( NULL,
                TEXT("Failed to register wnd class"),
                TEXT("ERROR"),
                MB_OK|MB_ICONERROR);
    return FALSE;
    }
//create wnd of the 'class' just registered
hwnd=CreateWindowEx(0,                                  //more or 'extended' styles
                    chClassName,                        //the 'class' of window to create
                    TEXT("Common Controls - Toolbar"),  //the window title
                    WS_OVERLAPPEDWINDOW,                //window style: how it looks
                    GetSystemMetrics(SM_CXSCREEN)/4,    //window position: left
                    GetSystemMetrics(SM_CYSCREEN)/4,    //window position: top
                    GetSystemMetrics(SM_CXSCREEN)/2,	//window width
                    GetSystemMetrics(SM_CYSCREEN)/2,	//window height
                    NULL,                               //parent window handle
                    NULL,                               //handle to this windows's menu
                    hInstance,                          //application instance
                    NULL);                              //user defined information
if (!hwnd)
    {
    //wnd creation has failed so inform the user
    MessageBox( NULL,
                TEXT("Failed to create wnd"),
                TEXT("ERROR"),
                MB_OK|MB_ICONERROR);
    return FALSE;
    }
//Display the wnd
ShowWindow(hwnd,nCmdShow);
UpdateWindow(hwnd);

//start message loop
while (GetMessage(&Msg,NULL,0,0)>0)
    {
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
    }
return Msg.wParam;
}
//=========================================================================================
LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
switch (Message)
    {
        PAINTSTRUCT ps;
        HDC hMemDC;
        HBITMAP hOldBmp;
    case WM_PAINT:
    
        BeginPaint(hwnd,&ps);
        //first create a memory device context(dc) to hold image
        hMemDC=CreateCompatibleDC(ps.hdc);
        //and copy the bitmap into it
        hOldBmp=(HBITMAP)SelectObject(hMemDC,hBmp);
        //blt (pronounced 'blit' - bit block transfer) the image onto the window
        //this is essentially copying the image from the memory dc to the display dc.
        BitBlt(ps.hdc,                //target dc
           100,100,           //left-top to place bitmap on target
           1496,64,  //dimensions of target to receive bitmap
           hMemDC,                //source dc
           0,0,                   //left-top to take bitmap from source
           SRCCOPY);              //flag for blt operation - here it's just a copy
            //now restore the memory dc to preserve our bitmap
        SelectObject(hMemDC,hOldBmp);
        //free resources back to system used by memory dc
        DeleteDC(hMemDC);
        EndPaint(hwnd,&ps);
        return 0;
        break;
    case WM_CREATE:
        {
		INITCOMMONCONTROLSEX iccx;
		TBADDBITMAP          tbAddBmp;
		TBBUTTON             tbb[17];
        //first load in the common controls dll, specifying the toolbar control wnd class
        iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
        iccx.dwICC=ICC_BAR_CLASSES;
        InitCommonControlsEx(&iccx);
        //create a toolbar control - its dimensions are set by the parent wnd
        g_hwndToolbar=CreateWindowEx(WS_EX_DLGMODALFRAME,          //more or 'extended' styles
                                     TOOLBARCLASSNAME,             //the 'class' of window to create
                                     NULL,                         //the window title
                                     WS_CHILD|WS_VISIBLE|          //window style: how it looks
                                     TBSTYLE_FLAT|CCS_ADJUSTABLE|CCS_NODIVIDER,
                                     0,                            //window position: left
                                     0,                            //window position: top
                                     0,                            //window width
                                     0,                            //window height
                                     hwnd,                         //parent window handle
                                     NULL,                         //handle to this windows's menu
                                     g_hInst,                      //application instance
                                     NULL);                        //user defined information
        //setup and add buttons
        SendMessage(g_hwndToolbar,TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON),0);
        //add images
        tbAddBmp.hInst=HINST_COMMCTRL;
        tbAddBmp.nID=IDB_STD_SMALL_COLOR;
        SendMessage(g_hwndToolbar,TB_ADDBITMAP,0,(WPARAM)&tbAddBmp);
        //add buttons
        tbb[0].iBitmap=STD_FILENEW;
        tbb[0].idCommand=-1;
        tbb[0].fsState=TBSTATE_ENABLED;
        tbb[0].fsStyle=TBSTYLE_BUTTON;
        tbb[0].dwData=0;
        tbb[0].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("New"));
        //
        tbb[1].iBitmap=STD_FILEOPEN;
        tbb[1].idCommand=-1;
        tbb[1].fsState=TBSTATE_ENABLED;
        tbb[1].fsStyle=TBSTYLE_BUTTON;
        tbb[1].dwData=0;
        tbb[1].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Open"));
        //
        tbb[2].iBitmap=STD_FILESAVE;
        tbb[2].idCommand=-1;
        tbb[2].fsState=TBSTATE_ENABLED;
        tbb[2].fsStyle=TBSTYLE_BUTTON;
        tbb[2].dwData=0;
        tbb[2].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Save"));
        //
        tbb[3].iBitmap=STD_PRINTPRE;
        tbb[3].idCommand=-1;
        tbb[3].fsState=TBSTATE_ENABLED;
        tbb[3].fsStyle=TBSTYLE_BUTTON;
        tbb[3].dwData=0;
        tbb[3].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("PrintPre"));
        //
        tbb[4].iBitmap=STD_PRINT;
        tbb[4].idCommand=-1;
        tbb[4].fsState=TBSTATE_ENABLED;
        tbb[4].fsStyle=TBSTYLE_BUTTON;
        tbb[4].dwData=0;
        tbb[4].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Print"));
        //add a separator
        tbb[5].iBitmap=0;
        tbb[5].idCommand=-1;
        tbb[5].fsState=TBSTATE_ENABLED;
        tbb[5].fsStyle=TBSTYLE_SEP;	//separator
        tbb[5].dwData=0;
        tbb[5].iString=0;
        //
        tbb[6].iBitmap=STD_DELETE;
        tbb[6].idCommand=-1;
        tbb[6].fsState=TBSTATE_ENABLED;
        tbb[6].fsStyle=TBSTYLE_BUTTON;
        tbb[6].dwData=0;
        tbb[6].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Delete"));
        //
        tbb[7].iBitmap=STD_COPY;
        tbb[7].idCommand=-1;
        tbb[7].fsState=TBSTATE_ENABLED;
        tbb[7].fsStyle=TBSTYLE_BUTTON;
        tbb[7].dwData=0;
        tbb[7].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Copy"));
        //
        tbb[8].iBitmap=STD_CUT;
        tbb[8].idCommand=-1;
        tbb[8].fsState=TBSTATE_ENABLED;
        tbb[8].fsStyle=TBSTYLE_BUTTON;
        tbb[8].dwData=0;
        tbb[8].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Cut"));
        //
        tbb[9].iBitmap=STD_PASTE;
        tbb[9].idCommand=-1;
        tbb[9].fsState=TBSTATE_ENABLED;
        tbb[9].fsStyle=TBSTYLE_BUTTON;
        tbb[9].dwData=0;
        tbb[9].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Paste"));
        //
        tbb[10].iBitmap=STD_REDOW;
        tbb[10].idCommand=-1;
        tbb[10].fsState=TBSTATE_ENABLED;
        tbb[10].fsStyle=TBSTYLE_BUTTON;
        tbb[10].dwData=0;
        tbb[10].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Redo"));
        //
        tbb[11].iBitmap=STD_UNDO;
        tbb[11].idCommand=-1;
        tbb[11].fsState=TBSTATE_ENABLED;
        tbb[11].fsStyle=TBSTYLE_BUTTON;
        tbb[11].dwData=0;
        tbb[11].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Undo"));
        //add a separator
        tbb[12].iBitmap=0;
        tbb[12].idCommand=-1;
        tbb[12].fsState=TBSTATE_ENABLED;
        tbb[12].fsStyle=TBSTYLE_SEP;	//separator
        tbb[12].dwData=0;
        tbb[12].iString=0;
        //
        tbb[13].iBitmap=STD_PROPERTIES;
        tbb[13].idCommand=-1;
        tbb[13].fsState=TBSTATE_ENABLED;
        tbb[13].fsStyle=TBSTYLE_BUTTON;
        tbb[13].dwData=0;
        tbb[13].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Props"));
        //
        tbb[14].iBitmap=STD_FIND ;
        tbb[14].idCommand=-1;
        tbb[14].fsState=TBSTATE_ENABLED;
        tbb[14].fsStyle=TBSTYLE_BUTTON;
        tbb[14].dwData=0;
        tbb[14].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Find"));
        //
        tbb[15].iBitmap=STD_REPLACE ;
        tbb[15].idCommand=-1;
        tbb[15].fsState=TBSTATE_ENABLED;
        tbb[15].fsStyle=TBSTYLE_BUTTON;
        tbb[15].dwData=0;
        tbb[15].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Replace"));
        //
        tbb[16].iBitmap=STD_HELP;
        tbb[16].idCommand=-1;
        tbb[16].fsState=TBSTATE_ENABLED;
        tbb[16].fsStyle=TBSTYLE_BUTTON;
        tbb[16].dwData=0;
        tbb[16].iString=SendMessage(g_hwndToolbar,TB_ADDSTRING,0,(LPARAM)TEXT("Help"));
        //
        SendMessage(g_hwndToolbar,TB_ADDBUTTONS,17,(LPARAM)(LPTBBUTTON)&tbb);
        return 0;
        }
    case WM_DESTROY:
        {
        PostQuitMessage(0);    //signal end of application
        return 0;
        }
    case WM_SIZE:
        {
        //resize toolbar so that it's always same width as parent's client area
        MoveWindow(g_hwndToolbar,0,0,LOWORD(lParam),0,TRUE);
TCHAR chFile[]=TEXT(".\\semaforo.bmp");    //use this for DevC++ and running msvc++ apps within IDE

hBmp=(HBITMAP)LoadImage(g_hInst,                       //application instance
                        chFile,                      //file name of bitmap
                        IMAGE_BITMAP,                //constant specifying image type
                        0,                           //image width, when 0 use resource width
                        0,                           //image height, when 0 use resource height
                        LR_CREATEDIBSECTION|LR_LOADFROMFILE); //how to load image

PAINTSTRUCT ps;
HDC hMemDC;
HBITMAP hOldBmp;

BeginPaint(hwnd,&ps);
//first create a memory device context(dc) to hold image
hMemDC=CreateCompatibleDC(ps.hdc);
//and copy the bitmap into it
hOldBmp=(HBITMAP)SelectObject(hMemDC,hBmp);
//blt (pronounced 'blit' - bit block transfer) the image onto the window
//this is essentially copying the image from the memory dc to the display dc.
BitBlt(ps.hdc,                //target dc
       100,100,           //left-top to place bitmap on target
       1496,64,  //dimensions of target to receive bitmap
       hMemDC,                //source dc
       0,0,                   //left-top to take bitmap from source
       SRCCOPY);              //flag for blt operation - here it's just a copy
//now restore the memory dc to preserve our bitmap
SelectObject(hMemDC,hOldBmp);
//free resources back to system used by memory dc
DeleteDC(hMemDC);


PRINTDLG pd;
HINSTANCE hInst;
HWND hwnd_p;
ZeroMemory(&pd, sizeof(pd));
pd.lStructSize = sizeof(pd);    // always remember to set this!
pd.hInstance = hInst;           // application process handle
pd.hwndOwner = hwnd_p;
GetDevMode();
//pd.hDevMode = hDevMode;
//pd.hDevNames = hDevNames;
pd.Flags = PD_ALLPAGES|PD_HIDEPRINTTOFILE|PD_NOPAGENUMS|PD_RETURNDC;
pd.nCopies   = 1;

//now we can show the print dialog
//if the user chose cancel, then quit out.
if(!PrintDlg(&pd))
    return FALSE;
RECT margins;
margins.left = MulDiv(rcMargin.left, GetDeviceCaps(pd.hDC, LOGPIXELSX), 1000);
margins.top = MulDiv(rcMargin.top, GetDeviceCaps(pd.hDC, LOGPIXELSY), 1000);
margins.right = MulDiv(rcMargin.right, GetDeviceCaps(pd.hDC, LOGPIXELSX), 1000);
margins.bottom = MulDiv(rcMargin.bottom, GetDeviceCaps(pd.hDC, LOGPIXELSY), 1000);

int iPOX = GetDeviceCaps(pd.hDC, PHYSICALOFFSETX);
int iPOY = GetDeviceCaps(pd.hDC, PHYSICALOFFSETY);
int iPW = GetDeviceCaps(pd.hDC, PHYSICALWIDTH);
int iPH = GetDeviceCaps(pd.hDC, PHYSICALHEIGHT);

int iLeftAdjust = margins.left - iPOX;
int iTopAdjust = margins.top - iPOY;
int iRightAdjust = margins.right - (iPW - iPOX - GetDeviceCaps(pd.hDC, HORZRES));
int iBottomAdjust = margins.bottom - (iPH - iPOY - GetDeviceCaps(pd.hDC, VERTRES));

int iWidth = GetDeviceCaps(pd.hDC, HORZRES) - (iLeftAdjust + iRightAdjust);
int iHeight = GetDeviceCaps(pd.hDC, VERTRES) - (iTopAdjust + iBottomAdjust);

TEXTMETRIC tm;
HFONT hfont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
int yChar;

// Setup the current device context
SetMapMode(pd.hDC, MM_TEXT);
SelectObject(pd.hDC, hfont);

// work out the character dimensions for the current font
GetTextMetrics(pd.hDC, &tm);
yChar = tm.tmHeight;

int iHeaderHeight   = 0;
int iTotalLines     = 3;   
int iLinesPerPage   = (iHeight - iHeaderHeight) / yChar;
int iTotalPages     = (iTotalLines + iLinesPerPage - 1) / iLinesPerPage;

DOCINFO di;
BOOL bSuccess = TRUE;
BOOL bUserAbort = FALSE;

char* szFileName = "prova";

ZeroMemory(&di, sizeof(di));
di.cbSize = sizeof(di);
di.lpszDocName = szFileName;    // name of the file you are printing.
                                // this will appear in the print manager
                                
if(StartDoc(pd.hDC, &di) > 0)
{
//    BeginPaint(hwnd,&pd);
    //first create a memory device context(dc) to hold image
    hMemDC=CreateCompatibleDC(pd.hDC);
    //and copy the bitmap into it
    hOldBmp=(HBITMAP)SelectObject(hMemDC,hBmp);
    //blt (pronounced 'blit' - bit block transfer) the image onto the window
    //this is essentially copying the image from the memory dc to the display dc.
    BitBlt(pd.hDC,                //target dc
       100,100,           //left-top to place bitmap on target
       1496,64,  //dimensions of target to receive bitmap
       hMemDC,                //source dc
       0,0,                   //left-top to take bitmap from source
       SRCCOPY);              //flag for blt operation - here it's just a copy
    //now restore the memory dc to preserve our bitmap
    SelectObject(hMemDC,hOldBmp);
    //free resources back to system used by memory dc
    DeleteDC(hMemDC);

    for(int iColCopy = 0; iColCopy < ((pd.Flags & PD_COLLATE) ? pd.nCopies : 1); iColCopy++)
    {
        for(int iPage = 0; iPage < iTotalPages; iPage++)
        {
            for(int iNonColCopy = 0; iNonColCopy < ((pd.Flags & PD_COLLATE) ? 1 : pd.nCopies); iNonColCopy++)
            {
                HANDLE hold;
                if(StartPage(pd.hDC) < 0)
                {
                    bSuccess = FALSE;
                    break;
                }
                //Make all printing be offset by the amount specified for the margins
                SetViewportOrgEx(pd.hDC, iLeftAdjust, iTopAdjust, NULL);
                                
                //select the fixed-width font into the printer DC
                hold = SelectObject(pd.hDC, hfont);
                //print the current file line by line
                for(int iLine = 0; iLine < iLinesPerPage; iLine++)
                {
                    const char* szBuffer;
                    int iLineNum = iLinesPerPage * iPage + iLine;
                    if(iLineNum > iTotalLines) break;
                        
                    //get line (iLine) from the application, and store it
                    //into szBuffer
                    if (iLine == 0)
                       szBuffer = "STAMPA DI PROVA";
                    else
                        szBuffer = "COME VIENE ";   
                    //szBuffer = l[iLine].c_str();
                    //output a line of text to the printer
                    TextOut(pd.hDC, 0, yChar * iLine + iHeaderHeight, szBuffer, 
                            lstrlen(szBuffer) - 2);
                    //bUserAbort = !QueryAbort();
                }

                SelectObject(pd.hDC, hold);

                if(EndPage(pd.hDC) < 0)
                {
                    bSuccess = FALSE;
                    break;
                }
                    
                //bUserAbort = !QueryAbort();
                if(bUserAbort) break;
            }
            if(!bSuccess || bUserAbort) break;
        }
    
        if(!bSuccess || bUserAbort) break;
    }

}
else
{
    bSuccess = FALSE;
}

if(bSuccess && !bUserAbort) 
    EndDoc(pd.hDC);
else
    AbortDoc(pd.hDC);

DeleteDC(pd.hDC);

        return 0;
        }
    default:
        return DefWindowProc(hwnd,Message,wParam,lParam);  //let system deal with msg
    }
}
//=========================================================================================
#endif

