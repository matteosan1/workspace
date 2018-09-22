#include "ListDlg.h"

const char* l = "";

ListDlg::ListDlg()
{
}

ListDlg::~ListDlg()
{
}

ListDlg::ListDlg(HWND hwnd, const char* a)
{
    l = a;
    int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LISTA), hwnd, ListDlgProc);
    if (ret == -1)
    {
        MessageBox(hwnd, "ERRORE", "Attenzione!", MB_OK | MB_ICONERROR); 
    }
}

BOOL CALLBACK ListDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_INITDIALOG:
            SetDlgItemText(hwnd, IDC_NOME, l);  
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                    break;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}
