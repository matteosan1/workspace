#include "ViewClient.h"
#include "resource.h"

ViewClient::ViewClient(Row row)
{
    for(int i=1; i<19; i++)
        edit[i-1] = (string)row[i];
    insert = false;
}

ViewClient::ViewClient()
{
    for(int i=0; i<18; i++)
        edit[i] =  "";
    insert = true;
}

ViewClient::~ViewClient()
{}

BOOL CALLBACK ViewClient::DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HWND hBtn1, hBtn2, hBtn3;
    switch (Message)
    {
        case WM_COMMAND:
            if (HIWORD(wParam) == EN_CHANGE)
            {
                // enable changes button
            }    
            if (HIWORD(wParam) == BN_CLICKED)
            {
                if (LOWORD(wParam) == IDOK)
                {
                    GetInfo();
                    EndDialog(hwnd, IDOK);
                }
                if (LOWORD(wParam) == IDCANCEL)
                    EndDialog(hwnd, IDCANCEL);
                if (LOWORD(wParam) == ID_APPLY)
                {
                    GetInfo();
                    EndDialog(hwnd, ID_APPLY);
                }   
            }
            return true;
        case WM_INITDIALOG:
            hwndCtl = hwnd;
            hBtn1 = GetDlgItem(hwndCtl, IDOK);
            hBtn2 = GetDlgItem(hwndCtl, ID_APPLY);
            if (!insert)
            {
                EnableWindow(hBtn2, true);
                EnableWindow(hBtn1, false);
            }    
            FillEdit();
            return true;
        default:
            return false;
	}
} 

void ViewClient::FillEdit()
{
    HWND hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_NAME); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)30, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_SURNAME); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)30, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_ADD1); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)40, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_ADD2); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)40, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_CITY1); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)25, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_CITY2); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)25, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_STATE1); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)25, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_STATE2); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)25, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_ZIP1); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)10, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_ZIP2); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)10, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_COUNTRY1); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)25, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_COUNTRY2); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)25, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_PHONE); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)20, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_MOBILE); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)20, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_EMAIL); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)50, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_CC); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)16, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CLIENT_PIVA); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)16, 0);
      
    for(int i=0; i<18; i++)
    {
        hEdit = GetDlgItem(hwndCtl, 1411+i); 
        SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) edit[i].c_str());
    }     
}

void ViewClient::GetInfo()
{
    TCHAR* passwd;
    HWND hEdit;
    int nLen;
    for(int i=0; i<18; i++)
    {
        hEdit = GetDlgItem(hwndCtl, 1411+i);   
        nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
        /*if (nLen == 0)
        {
            MessageBox( NULL, TEXT("You must EVERY field"), TEXT("ERRORE !!!"), MB_OK|MB_ICONERROR);
            break;
        }*/
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        edit[i] = passwd;
    }    
}                    

