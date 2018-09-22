#include "ViewCD.h"
#include "resource.h"

ViewCD::ViewCD(Row row1, Row row2)
{
    for(int i=1; i<10; i++)
        edit[i-1] = (string)row1[i];
    edit[9] = (string)row1[11];
    edit[10] = (string)row1[12];  
    edit[11] = (string)row1[13];
    edit[12] = (string)row2[1];
    status = (int)row1[10];
    insert = false;
}

ViewCD::ViewCD()
{
    for(int i=0; i<13; i++)
        edit[i] =  "";
    status = 0;
    insert = true;
}

ViewCD::~ViewCD()
{}

BOOL CALLBACK ViewCD::DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HWND hBtn1, hBtn2;
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

void ViewCD::FillEdit()
{
    HWND hEdit = GetDlgItem(hwndCtl, IDC_CD_ARTIST); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)100, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CD_TITLE); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)100, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CD_COMPANY); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)30, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CD_SUPPLIER); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)30, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CD_FORMAT); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)30, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_CD_CODE); 
    SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)20, 0);
    
    for(int i=0; i<13; i++)
    {
        hEdit = GetDlgItem(hwndCtl, 1221+i); 
        SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) edit[i].c_str());
    }     
    CheckRadioButton(hwndCtl, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1+status);
}

void ViewCD::GetInfo()
{
    TCHAR* passwd;
    HWND hEdit;
    int nLen;
    for(int i=0; i<13; i++)
    {
        hEdit = GetDlgItem(hwndCtl, 1221+i);   
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
    for(int i=0; i<4; i++)
    {
        hEdit = GetDlgItem(hwndCtl, 1234+i);
        if (SendMessage(hEdit, BM_GETCHECK, 0, 0) == BST_CHECKED)
            status = i;
    }
}                    
