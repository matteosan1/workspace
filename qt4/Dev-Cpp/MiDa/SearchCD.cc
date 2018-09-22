#include "SearchCD.h"
#include "resource.h"

Search::Search()
{
    artist = NULL;
    company = NULL;
    supplier = NULL;
    quantity = NULL;
    code = NULL;
}

Search::~Search()
{}

BOOL CALLBACK Search::DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
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

void Search::SetEditCtrl()
{
    HWND hEdit = GetDlgItem(hwndCtl, IDC_SEARCH_ARTIST);   
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    artist = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, artist, nLen+1);
        
    hEdit = GetDlgItem(hwndCtl, IDC_SEARCH_COMPANY);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    company = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, company, nLen+1);
    
    hEdit = GetDlgItem(hwndCtl, IDC_SEARCH_SUPPLIER);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    supplier = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, supplier, nLen+1);
    
    hEdit = GetDlgItem(hwndCtl, IDC_SEARCH_QUANTITY);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    quantity = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, quantity, nLen+1);
    
    hEdit = GetDlgItem(hwndCtl, IDC_SEARCH_CODE);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    code = new TCHAR[nLen+1]; 
    GetWindowText(hEdit, code, nLen+1);
}    
