#include "main.h"

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";
static HINSTANCE g_hInst = NULL;
HFONT g_hfFont;
int status = 0;
Gioco* gioco = NULL;
Corsa* corsa = new Corsa();

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                    break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    LOGBRUSH background;

    g_hInst = hThisInstance;

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW; /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);                
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    
    /* Use Windows's default color as the background of the window */
    //wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	background.lbStyle     = BS_PATTERN;				
	background.lbHatch     = (long) LoadImage(hThisInstance,"Intro.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);														
    wincl.hbrBackground    = CreateBrushIndirect(&background); 

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           WS_EX_CLIENTEDGE,    /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Tempo di Palio",    /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           490,                 /* The programs width */
           410,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND g_hToolbar = NULL;
    int ret;
    switch (message)                  /* handle the messages */
    {
   /*     case WM_CREATE:
            hbmIntro = LoadBitmap(g_hInst, "INTROBMP");
            hbmWinter = LoadBitmap(g_hInst, "WINTERBMP");
            HFONT hf;
            HDC hdcWindow;
            long lfHeight;
                
            hdcWindow = GetDC(NULL);
            lfHeight = -MulDiv(12, GetDeviceCaps(hdcWindow, LOGPIXELSY), 72);
            ReleaseDC(NULL, hdcWindow);
            hf = CreateFont(lfHeight, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
            if(hf)
            {
                DeleteObject(g_hfFont);
                g_hfFont = hf;
            }
            else
            {
                MessageBox(hwnd, "Font creation failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
            }
                
             if(!hbmWinter)
            {
                MessageBox(hwnd, "Load of resources failed.", "Error",
                    MB_OK | MB_ICONEXCLAMATION);
                return -1;
            }
            break;
*/            
        case WM_PAINT:
            if (status == 4)
            {
            }
            if (status == 0)
            {
                PAINTSTRUCT ps;
                
                RECT windowRect = {100, 100, 400, 400};
                int x, y;
                HDC hdc = GetWindowDC(hwnd);
                GetWindowRect(hwnd, &windowRect);
                ReleaseDC(hwnd, hdc);
                char szSize[100];
                char szTitle[] = "These are the dimensions of your client area:";
                static int length = strlen(szTitle);
                HFONT hfOld = (HFONT) SelectObject(hdc, g_hfFont);
                SetBkColor(hdc, TRANSPARENT);
                SetTextColor(hdc, RGB(0,255,0));
               // if(g_bOpaque)
               // {
                    SetBkMode(hdc, TRANSPARENT);
//                }
//                else
//                {
//                    SetBkMode(hdc, TRANSPARENT);
//                }
                hdc = BeginPaint(hwnd, &ps);
    			x = (windowRect.right - windowRect.left) / 2;	// So 500 - 100 = 400.  Divide that by 2 and we have 200.  x = 200
//	       		x = x - ((length * textInfo.tmAveCharWidth) / 2);// So 200 - ((12 * 7) / 2) = 158.  So our X position for the string starts at 158.
															// Now we do the exact same thing for the Y, but with different numbers.
                y = (windowRect.bottom - windowRect.top) / 2;	// So once again, (500 - 100) / 2 = 200;
//			y = y - (textInfo.tmHeight / 2);				// Since the amount of characters doesn't matter for the Y value, we just subtract half the height of the font.
															// Next we want to print out the text.  We will use TextOut().  It's parameters are (HDC, XPosition, YPosition, The string, and the string's length);
			TextOut(hdc, x, y, szTitle, length);			// We pass in our hdc, the x and y position, the string, and the string's length.  Tada!  Centered text!  Even if you resize the window.  Every time you move or resize the window, it calls WM_PAINT.
			EndPaint(hwnd, &ps);					// Now we must free our memory that was allocated for the paintStruct.
		    break;					
            }    
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_START_GAME:
                    if (status != 0)
                    {
                        corsa->Estrazione(gioco, hwnd);
                        corsa->Batterie(gioco->GetCavalli(), hwnd);
                        //corsa->Assegnazione(gioco);
                        //corsa->SceltaFantini(gioco->GetFantini());
                    }
                    else
                        MessageBox(hwnd, "Il gioco non è stato creato o caricato.", "Attenzione!", MB_OK | MB_ICONEXCLAMATION); 
                    break;
                case ID_VIEW_CONTRADE:
                    g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR), hwnd, ToolDlgProc);
                    if (g_hToolbar != NULL)
                        ShowWindow(g_hToolbar, SW_SHOW);            
                    else 
                        MessageBox(hwnd, "CreateDialog returned NULL", "Warning!", MB_OK | MB_ICONINFORMATION);
                    break;            
                case ID_NEW_GAME:
                    gioco = InizioGioco(hwnd);
                    if (gioco != NULL)
                    {
                        status = 1;
                        //ShowWindow(hwnd, SW_SHOWNORMAL);
                        //UpdateWindow(hwnd);
                        // ATTIVARE AVVIA PALIO;
                    }    
                    break;            
                case ID_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                case ID_ABOUT_DIALOG:
                    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
                    break;    
            }
            break;
        case WM_DESTROY:
            DestroyWindow(g_hToolbar);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {   
                case IDC_PRESS:
                    MessageBox(hwnd, "Hi!", "This is a message", MB_OK | MB_ICONEXCLAMATION);
                    break;
                case IDC_OTHER:
                    ShowWindow(hwnd, SW_HIDE);
                    break;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}
