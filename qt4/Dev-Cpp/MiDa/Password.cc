#include "Password.h"
#include "resource.h"

Password::Password()
{
    passwd = NULL;
}

Password::~Password()
{}

BOOL CALLBACK Password::DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED)
            {
                if (LOWORD(wParam) == IDOK)
                {
                    SetPassword();
                    EndDialog(hwnd, IDOK);
                }
                if (LOWORD(wParam) == IDCANCEL)
                    EndDialog(hwnd, IDCANCEL);
            }
            return true;
        case WM_INITDIALOG:
            hwndCtl = hwnd;	//store wnd handle here
            return true;
        default:
            return false;
	}
} 

void Password::SetPassword()
{
    HWND hEdit = GetDlgItem(hwndCtl, IDC_PASSWORD);   
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    passwd = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, passwd, nLen+1);
}    
