#include "SearchClient.h"
#include "resource.h"

SearchClient::SearchClient()
{
    surname = NULL;
    city = NULL;
    country = NULL;
}

SearchClient::~SearchClient()
{}

BOOL CALLBACK SearchClient::DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED)
            {
                if (LOWORD(wParam) == IDOK)
                {
                    SetEditCtrl();
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

void SearchClient::SetEditCtrl()
{
    HWND hEdit = GetDlgItem(hwndCtl, IDC_SEARCH_SURNAME);   
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    surname = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, surname, nLen+1);
    
    hEdit = GetDlgItem(hwndCtl, IDC_SEARCH_CITY);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    city = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, city, nLen+1);
    
    hEdit = GetDlgItem(hwndCtl, IDC_SEARCH_COUNTRY);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    country = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, country, nLen+1);
}    
