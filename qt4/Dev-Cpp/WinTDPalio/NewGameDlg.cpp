#include "NewGameDlg.h"

int a, b;
char* c;

NewGameDlg::~NewGameDlg()
{
}

NewGameDlg::NewGameDlg()
{
    anno = 0;
    giocatori = 0;
}

NewGameDlg::NewGameDlg(HWND hwnd)
{
    anno = 2004;
    giocatori = 1;
    int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_GAME), hwnd, NewGameDlgProc);
    anno = b;
    if (ret == IDCANCEL)
    {
        MessageBox(hwnd, "Il gioco non è stato creato.", "Attenzione!", MB_OK | MB_ICONEXCLAMATION); 
        anno = -1;
    }
    nome = c;
    giocatori = a;
}

BOOL CALLBACK NewGameDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int len;
    switch(message)
    {
        case WM_INITDIALOG:
            SetDlgItemText(hwnd, IDC_GAME_PLAYER, "1");  
            SetDlgItemText(hwnd, IDC_GAME_YEAR, "2004"); 
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    BOOL bSucces;
                    a = GetDlgItemInt(hwnd, IDC_GAME_PLAYER, &bSucces, FALSE);
                    b = GetDlgItemInt(hwnd, IDC_GAME_YEAR, &bSucces, FALSE);
                    len  = GetWindowTextLength(GetDlgItem(hwnd, IDC_GAME_NAME));
                    if(len > 0)
                    {
                        int i;
                        char* buf;
                        buf = (char*)GlobalAlloc(GPTR, len + 1);
                        GetDlgItemText(hwnd, IDC_GAME_NAME, buf, len + 1);
                        c = buf;
                        GlobalFree((HANDLE)buf);
                    }
                    else
                        c = "default";
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
