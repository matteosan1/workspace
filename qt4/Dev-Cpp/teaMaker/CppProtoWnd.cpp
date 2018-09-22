#include "CppProtoWnd.h"	//include important stuff
#include <fstream>

//-------------------------------------------------------------------------------------------
//DEFINITIONS OF CppWnd
//-------------------------------------------------------------------------------------------
CppWnd::CppWnd()
{}

CppWnd::CppWnd(HWND hApp, int n, std::string* nom, std::string* val)
{
    indice = 0;
    giocatori = n;
    for(int i=0; i<giocatori; i++)
    {
        nome[i] = nom[i];
        valutazione[i] = val[i];
    }    
}
//-------------------------------------------------------------------------------------------
CppWnd::~CppWnd()
{
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
BOOL CALLBACK CppWnd::PippoProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
//all the msgs are routed through here. The msgs are 'cracked' ie the wParam and lParam are
//converted into meaningful parameters which are then forwarded to specific handler functions.

switch (Message)
    {
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED)
        {
            if (LOWORD(wParam) == IDOK)
                EndDialog(hwnd, IDOK);
            if (LOWORD(wParam) == IDC_BUTTON1)
                Add();
            if (LOWORD(wParam) == IDC_BUTTON2)
                Change(indice);  
        }
        if (HIWORD(wParam) == CBN_SELCHANGE)
        {
            if (LOWORD(wParam) == IDC_COMBO1)
            {
                TCHAR name[20];
                HWND hCombo = GetDlgItem(hwndCh, IDC_COMBO1); 
                indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                SendMessage(hCombo, CB_GETLBTEXT, (WPARAM) indice, (LPARAM) name);
                std::string voto, n(name);
                if (indice != CB_ERR)
                {
                    for(int i=0; i<giocatori; i++)
                    {
                        if (n == nome[i])
                        {   
                            voto = valutazione[i];
                            indice = i;
                        }   
                    }             
                    HWND hEdit = GetDlgItem(hwndCh, IDC_EDIT3); 
                    SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) voto.c_str());            
                }  
            }
        }
        return true;
    case WM_INITDIALOG:
        hwndCh = hwnd;
        FillCombos();
        return true;
    default:
        return false;
	}
}
//-------------------------------------------------------------------------------------------
void CppWnd::Add()
{
    TCHAR *name = NULL, *forza = NULL;
    HWND hEdit = GetDlgItem(GetActiveWindow(), IDC_EDIT1);   //tmp store for edit cntrl handle
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);  //length of edit box string
    
    if (nLen == 0)
    {
        MessageBox( NULL,
                TEXT("Devi inserire un nome"),
                TEXT("ERRORE !!!"),
                MB_OK|MB_ICONERROR);
        return;
    }
    
    name = new TCHAR[nLen+1];                        //allocate memory for string
    //get edit control contents
    GetWindowText(hEdit, name, nLen+1);
        
    hEdit = GetDlgItem(GetActiveWindow(), IDC_EDIT2);   //tmp store for edit cntrl handle
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);  //length of edit box string
    forza = new TCHAR[nLen+1];                        //allocate memory for string
    
    GetWindowText(hEdit, forza, nLen+1);
    if (atof(forza) > 10)
        forza = "10";
    if (atof(forza) < 0)
        forza = "0";    
    if ((!((atoi(forza) <= 10) && (atoi(forza) >= 0))) || (nLen == 0))
    {
        MessageBox( NULL,
                TEXT("Devi inserire una valutazione valida"),
                TEXT("ERRORE !!!"),
                MB_OK|MB_ICONERROR);
        return;
    }
    
    nome[giocatori] = name;
    valutazione[giocatori] = forza;
    giocatori++;
    
    SendDlgItemMessage(GetActiveWindow(), IDC_COMBO1, CB_RESETCONTENT, 0, 0);
    FillCombos();
    MessageBox( NULL,
                TEXT("Inserimento avvenuto con successo"),
                TEXT("OK !!!"),
                MB_OK|MB_ICONINFORMATION);
    if (name)
    {
        delete[] name;    //free string memory
        delete[] forza;
    }
}

void CppWnd::Change(int i)
{
    TCHAR *forza = NULL;
    
    HWND hEdit = GetDlgItem(hwndCh, IDC_EDIT3);   //tmp store for edit cntrl handle
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);  //length of edit box string
    forza = new TCHAR[nLen+1];                        //allocate memory for string
    //get edit control contents
    GetWindowText(hEdit, forza, nLen+1);
    valutazione[i] = forza;
     
    MessageBox( NULL,
                TEXT("Cambiamento avvenuto con successo"),
                TEXT("OK !!!"),
                MB_OK|MB_ICONINFORMATION);
    if (forza)
        delete[] forza;
}

void CppWnd::FillCombos()
{
    HWND hCombo = GetDlgItem(hwndCh, IDC_COMBO1); 
    for(int i=0; i<giocatori; i++)
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) nome[i].c_str()); 
}

