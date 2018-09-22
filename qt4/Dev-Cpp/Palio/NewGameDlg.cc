#include "NewGameDlg.h"

NewGameDlg::~NewGameDlg()
{}

NewGameDlg::NewGameDlg()
{
    anno = 2005;
    giocatori = 0;
}

BOOL CALLBACK NewGameDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int len;
    switch(message)
    {
        case WM_INITDIALOG:
            hwndCtl = hwnd;
            SetControl();     
            return TRUE;
        case WM_COMMAND:
            if ((HIWORD(wParam) == LBN_DBLCLK) && (LOWORD(wParam) == IDC_LISTA_GIOCATORI))
                RemoveList();
            switch(LOWORD(wParam))
            {
                case IDOK:
                    if (GetControl())
                        EndDialog(hwnd, IDOK);
                    break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;
                case ID_INSERISCI:
                    InsertList();
                    break;    
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

void NewGameDlg::SetControl()
{
    char b[4];
    string s = itoa(anno, b, 10);
    HWND hEdit = GetDlgItem(hwndCtl, IDC_ANNO);
    SendMessage(hEdit, EM_SETLIMITTEXT, 4, 0);
    SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s.c_str());
    SetFocus(hEdit);
}    

BOOL NewGameDlg::GetControl()
{   
    if (giocatori != 0)
    {
        TCHAR* passwd;
        HWND hEdit;
        hEdit = GetDlgItem(hwndCtl, IDC_ANNO);   
        int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
        if (nLen == 0)
            anno = 1650;
        else
        {
            passwd = new TCHAR[nLen+1]; 
            GetWindowText(hEdit, passwd, nLen+1);
            anno = atoi(passwd);
        }
        return true;
    }
    else
    {
       MessageBox( NULL, TEXT("Devi inserire almeno un giocatore !"), TEXT("ERRORE !!!"), MB_OK|MB_ICONERROR);    
       return false;
    }   
}

void NewGameDlg::InsertList()
{
    if (giocatori < 16)
    {
        TCHAR* passwd;
        HWND hEdit;
        int nLen;
        hEdit = GetDlgItem(hwndCtl, IDC_NOME);   
        nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
        if (nLen == 0)
            MessageBox( NULL, TEXT("Devi inserire un nome !"), TEXT("ERRORE !!!"), MB_OK|MB_ICONERROR);
        else
        {
            passwd = new TCHAR[nLen+1]; 
            GetWindowText(hEdit, passwd, nLen+1);
            nome[giocatori] = passwd;
            SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) "");
            SetFocus(hEdit);
            hEdit = GetDlgItem(hwndCtl, IDC_LISTA_GIOCATORI);
            SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)nome[giocatori].c_str());   
            giocatori++;
        }
    }
    else            
        MessageBox( NULL, TEXT("Hai già inserito 17 giocatori !"), TEXT("ERRORE !!!"), MB_OK|MB_ICONERROR);
}

void NewGameDlg::RemoveList()
{
    HWND lv = GetDlgItem(hwndCtl, IDC_LISTA_GIOCATORI);
    int indice = SendMessage(lv, LB_GETCURSEL, 0, 0);
    if(indice != LB_ERR)
    {
        SendMessage(lv, LB_DELETESTRING, indice, 0);
        for (int i=indice; i <giocatori; i++)
            nome[i] = nome[i+1];
        giocatori--;    
    }    
}

