#include "Gioco.h"
#include "Utilities.h"
#include "resource.h"

#include <fstream>

LRESULT CALLBACK Gioco::WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    switch (Message)
    {
        case WM_COMMAND:
            return OnCommand((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        case WM_CREATE:
            hAppWnd = hwnd;	
            return OnCreate((CREATESTRUCT*)lParam);
        case WM_DESTROY:
            return OnDestroy();
        case WM_SIZE:
            MoveWindow(listview.hCntrl,0,0,LOWORD(lParam),HIWORD(lParam),TRUE);
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);  //let system deal with msg
	}
}

BOOL Gioco::OnCommand(HWND hwndCtl, int nID, UINT uNotifyCode)
{
    switch (nID)                  /* handle the messages */
    {
        case ID_NEW_GAME:
            NuovoGioco(hwndCtl);
            return 0;
            break;
        case ID_FILE_EXIT:
            if (isGioco)
                ;// Chiede se voglio salvare
            PostMessage(hAppWnd, WM_CLOSE, 0, 0);
            return 0;
            break;
/*        case IDM_POPUP_UPDATE:
            Select(hwndCtl);
            return 0;
            break;
        case IDM_POPUP_REMOVE:
            Remove(hwndCtl);
            return 0;
            break;    
        case ID_APP_ABOUT:
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwndCtl, AboutDlgProc);
            return 0;
            break;
        case ID_SEARCH_CD:
            if (stato == 4)
                Searcher(hwndCtl, 4);
            else
                Searcher(hwndCtl, 1);     
            break;
        case ID_INSERT_CD:   
            Insert(hwndCtl, 1);
            break;
        case ID_INSERT_CLIENT:
            Insert(hwndCtl, 2);
            break;    
        case ID_INSERT_ORDER:
            Insert(hwndCtl, 4);
            break;
        case ID_SEARCH_CLIENT:
            Searcher(hwndCtl, 2);
            break;
        case ID_SEARCH_ORDER:
            Searcher(hwndCtl, 5);
            break;
        case ID_CREATE_HTML:
        case ID_FILE_PRINT:
            MessageBox( NULL, TEXT("Not yet implemented"), TEXT("ERRORE !!!"), MB_OK|MB_ICONERROR);
            return 0;
    }
        
    if (hwndCtl)
    {
        if (uNotifyCode == LBN_DBLCLK)
        {
            if (nID == IDC_LISTVIEW)
            {
                if (stato == 4)
                {
                    InsertInOrder(hwndCtl);
                }
                else
                    Select(hwndCtl);
                return 0;
            }
        }   		*/
	}
    return 0;
   
}

void Gioco::NuovoGioco(HWND hwnd)
{
    if (isGioco);// chiedi se voglio salvare
    
    nuovoGioco = new NewGameDlg();
    int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NUOVO_GIOCO), hwnd, NewGameProc);
    if (ret == IDCANCEL) 
    {
        MessageBox( NULL, TEXT("Il gioco non è stato creato."), 
                TEXT("ATTENZIONE !!!"), MB_OK|MB_ICONEXCLAMATION);
    }    
    if (ret == IDOK)
    {
        int* y;
        anno = nuovoGioco->GetAnno();
        numGiocatori = nuovoGioco->GetGiocatori();
        Ordina(17, y);
        for(int i=0; i<numGiocatori; i++)
            giocatori[i].SetGiocatore(nuovoGioco->GetNome(i), y[i], .5);

        ifstream f("contrade.dat");
        string nome;
        int popolo, avversaria;
        for(int i=0; i<17; i++)
        {
                f >> nome >> popolo >> avversaria;
                contrade[i].SetContrada(nome, popolo, avversaria);
        }        
        f.close();
        
        EstrazioneContrade(false);
        
        // mostra risultato
        isGioco = true;
    }
    delete nuovoGioco;
}

void Gioco::EstrazioneContrade(bool h)
{
    if(!h)
    {
        int numero[17];
        int* valore;
    
        for(int i=0; i<17; i++)
            numero[i] = i;

        Ordina(17, valore);
        for(int i=0; i<16; i++)
        {
            for(int j=i+1; j<17; j++)
            {
                if (valore[i] > valore[j])
                {
                    int temp = numero[i];
                    numero[i] = numero[j];
                    numero[j] = temp;
                }
            }
        }     
    
        for(int i=0; i<17; i++)
            contradeLuglio[i] = numero[i];
    
        Ordina(17, valore);
        for(int i=0; i<16; i++)
        {
            for(int j=i+1; j<17; j++)
            {
                if (valore[i] > valore[j])
                {
                    int temp = numero[i];
                    numero[i] = numero[j];
                    numero[j] = temp;
                }
            }
        }     
        for(int i=0; i<17; i++)
            contradeAgosto[i] = numero[i];
    }
}

int Gioco::OnCreate(CREATESTRUCT *cs)
{
    RECT rc;
    GetClientRect(hAppWnd, &rc);
    /*
    listview.SetWndClassName("LISTBOX");
    listview.SetWndCaption(TEXT(""));
    listview.nStyle|= LBS_NOTIFY|WS_VSCROLL|LBS_USETABSTOPS;
    listview.nExStyle = WS_EX_CLIENTEDGE;
    listview.Top=0;
    listview.Left=0;
    listview.Width=rc.right - rc.left;
    listview.Height=rc.bottom - rc.top;
    listview.nID=IDC_LISTVIEW;	
    listview.Create(hAppWnd);
*/
    return 0;	//return -1 to fail wnd creation
}

BOOL Gioco::OnDestroy()
{
    PostQuitMessage(0);    //signal end of application
    return 0;
}
