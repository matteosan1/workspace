#include "NewPlayerDlg.h"

char* c1;

NewPlayerDlg::~NewPlayerDlg()
{
}

NewPlayerDlg::NewPlayerDlg()
{
}

NewPlayerDlg::NewPlayerDlg(HWND hwnd)
{
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PLAYER), hwnd, NewPlayerDlgProc);
    nome = c1;
}

BOOL CALLBACK NewPlayerDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int len;
    switch(message)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    len  = GetWindowTextLength(GetDlgItem(hwnd, IDC_PLAYER_NAME));
                    if(len > 0)
                    {
                        int i;
                        char* buf;
                        buf = (char*)GlobalAlloc(GPTR, len + 1);
                        GetDlgItemText(hwnd, IDC_PLAYER_NAME, buf, len + 1);
                        c1 = buf;
                        GlobalFree((HANDLE)buf);
                    }
                    else
                        c1 = "default";
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
