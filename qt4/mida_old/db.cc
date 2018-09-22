#include "DB.h"
#include "Structure.h"
#include <vector>
#include <iostream>

CppCntrl::CppCntrl()
{
    nStyle = WS_CHILD|WS_VISIBLE;
    hCntrl = NULL;
    Width = 100;
    Height = 30;
}

CppCntrl::~CppCntrl()
{
    if (hCntrl)
        DestroyWindow(hCntrl);
}

HWND CppCntrl::Create(HWND hParent)
{
    if (!hInst)
        hInst = (HINSTANCE)GetWindowLong(hParent,GWL_HINSTANCE);
    
    hCntrl = CreateWindowEx(0,                          //more or 'extended' styles
                    chClassName,                        //the 'class' of window to create
                    chCaption,                          //the window title
                    nStyle,                             //window style: how it looks
                    Left,                               //window position: left
                    Top,                                //window position: top
                    Width,                              //window width
                    Height,                             //window height
                    hParent,                            //parent window handle
                    (HMENU)nID,                         //handle to wnd menu or cntrl ID
                    hInst,                              //application instance
                    (VOID*)this);                       //store pointer to class
    return hCntrl;
}

DB::DB()
{
//set a default value for the wnd caption
SetWndCaption(TEXT("MiDa"));
//set a default value for the wnd class name
SetWndClassName(TEXT("MiDa"));
//nullify wnd handle to make later checking easier
hAppWnd=NULL;
//set wnd default dimensions
//Left=GetSystemMetrics(SM_CXSCREEN)/4;
//Top=GetSystemMetrics(SM_CYSCREEN)/4;
//Width=GetSystemMetrics(SM_CXSCREEN)/2;
//Height=GetSystemMetrics(SM_CYSCREEN)/2;
Left = 100;
Top = 100;
Width = 700;
Height = 500;
//set default window style - don't make it resizable
nStyle=WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_THICKFRAME | WS_SIZEBOX;
//set default class style used in wnd registration
nClassStyle=CS_HREDRAW|CS_VREDRAW;
//set default colours to -1 (no colour)
}

DB::~DB()
{}

HWND DB::Create(HWND hParent)
{
    HMENU menu;
    
    WNDCLASSEX wcx;    //this structure is used for storing information about the wnd 'class'
    wcx.cbSize           = sizeof(WNDCLASSEX);                //byte size of WNDCLASSEX struct
    wcx.style            = nClassStyle;                       //ensure wnd is always redrawn
    wcx.lpfnWndProc      = (WNDPROC)MainWndProc;              //pointer to the Window Procedure
    wcx.cbClsExtra       = 0;                                 //Extra bytes for 'class' wnds
    wcx.cbWndExtra       = 0;                                 //Extra bytes for this wnd
    wcx.hInstance        = hInst;				              //Application instance
    wcx.hIcon            = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wcx.hCursor          = LoadCursor(NULL,IDC_ARROW);        //Cursor for wnd
    wcx.hbrBackground    = (HBRUSH)(COLOR_BTNFACE+1);         //Background wnd colour
    wcx.lpszMenuName     = NULL;                             //Name of wnd menu
    wcx.lpszClassName    = GetWndClassName();                 //Name of this wnd 'class'
    wcx.hIconSm          = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));

    if (!RegisterClassEx(&wcx))
    {
        MessageBox( NULL,
                TEXT("Failed to register wnd class"),
                TEXT("ERROR"),
                MB_OK|MB_ICONERROR);
        return NULL;
    }

    HWND hwnd;    //the wnd handle
    hwnd = CreateWindowEx(nExStyle,                     //more or 'extended' styles
                    chClassName,                        //the 'class' of window to create
                    chCaption,                          //the window title
                    nStyle,                             //window style: how it looks
                    Left,                               //window position: left
                    Top,                                //window position: top
                    Width,                              //window width
                    Height,                             //window height
                    hParent,                            //parent window handle
                    (HMENU)nID,                         //handle to wnd menu or cntrl ID
                    hInst,                              //application instance
                    (VOID*)this);                       //store pointer to class
    
    if (!hwnd)
    {
        MessageBox( NULL,
                TEXT("Failed to create wnd"),
                TEXT("ERROR"), 
                MB_OK|MB_ICONERROR);
        return NULL;
    }

    if (!hAppWnd)
        hAppWnd = hwnd;
        
    menu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU));
    SetMenu(hwnd, menu);

    ShowWindow(hwnd, SW_SHOW); 
    UpdateWindow(hwnd);
    SendMessage(hwnd, WM_PASSWORD, 0, 0);
    return hwnd;
}

BOOL DB::OnRightMouse(HWND hwnd)
{
    int indice = SendMessage(listview.hCntrl, LB_GETCURSEL, 0, 0);
    if (indice != LB_ERR)
    {
        POINT pt;
        GetCursorPos(&pt);
        popup = CreatePopupMenu();
        InsertMenu(popup, 1, MF_BYPOSITION | MF_STRING | MF_ENABLED, IDM_POPUP_REMOVE, "Delete");
        InsertMenu(popup, 2, MF_BYPOSITION | MF_STRING | MF_ENABLED, IDM_POPUP_UPDATE, "Update");
        InsertMenu(popup, 3, MF_BYPOSITION | MF_SEPARATOR, 0, "");
        InsertMenu(popup, 4, MF_BYPOSITION | MF_STRING | MF_DISABLED | MF_GRAYED, IDM_POPUP_PRINT, "Print");
        TrackPopupMenu(popup, 0, pt.x, pt.y, 0, hwnd, 0);
        DestroyMenu(popup);
    }
}

LRESULT CALLBACK DB::WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    POINT pt;
    switch (Message)
    {
        case WM_NOTIFY:
            return OnNotify(hwnd, wParam, lParam);
        case WM_CONTEXTMENU:
            return OnRightMouse(hwnd);
        case WM_PASSWORD:    
            return OnPassword(hwnd);
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

BOOL DB::OnNotify(HWND hwnd, WPARAM wParam,LPARAM lParam)
{
    int iIndex;
    if (LOWORD(wParam) == IDC_LISTVIEW)
    {
        if (((LPNMHDR)lParam)->code == NM_DBLCLK)
        {
            iIndex = (int)SendMessage(listview.hCntrl, LVM_GETNEXTITEM, WPARAM(-1), LVNI_SELECTED);
            if (iIndex == -1)
                return false;
            else
            {
                if (stato == 4)
                {
                    InsertInOrder(hwnd);
                }
                else
                    Select(hwnd);
                return 0;
            } 
        }
    }
    return 0;
}

BOOL DB::OnPassword(HWND hwnd)
{
    BOOL p = false;
    std::string pippo;
    pwd = new Password();
    for(int i=0; i<3; i++)
    {
        int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PASSWD), hwnd, PasswordProc);
        if (ret == IDCANCEL) 
            PostMessage(hAppWnd, WM_CLOSE, 0, 0);
        if (ret == IDOK)
        {
            pippo = pwd->GetPassword();
            try
            {
                connection = new Connection(use_exceptions);
                connection->connect("microsuoni", "", "microsuoni", pippo.c_str());
                p = true;
                break;
            }
            catch (BadQuery er)
            {
                MessageBox( NULL, TEXT("Wrong password !"), TEXT("ERROR"), MB_OK|MB_ICONERROR);
            }        
        }
    }   
    if (p)
        MessageBox( NULL, TEXT("Now you are connected to MiDa"), TEXT("Welcome to MiDa"), MB_OK|MB_ICONEXCLAMATION);
    else
        PostMessage(hAppWnd, WM_CLOSE, 0, 0);
               
    delete pwd;    
    return 0;
}

BOOL DB::OnCommand(HWND hwndCtl, int nID, UINT uNotifyCode)
{
    int iIndex;
    switch (nID)                  /* handle the messages */
    {
        case IDM_POPUP_UPDATE:
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
        case ID_APP_EXIT:
            PostMessage(hAppWnd, WM_CLOSE, 0, 0);
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
        case ID_SEARCH_SENT:
            Inventary(hwndCtl, 3);
            break;    
        case ID_SEARCH_PAID:
            Inventary(hwndCtl, 4);
            break;                
        case ID_SEARCH_ORDER:
            Searcher(hwndCtl, 5);
            break;    
        case ID_INVENTARY:
            Inventary(hwndCtl, 1);
            break;
        case ID_MONTHLY_SELL:
            Inventary(hwndCtl, 2);
            break;        
        case ID_FILE_PRINT:
            MessageBox( NULL, TEXT("Not yet implemented"), TEXT("ERRORE !!!"), MB_OK|MB_ICONERROR);
            return 0;
        case ID_CONTROL_PANEL:
            ControlPanel(hwndCtl);
            return 0;    
    }
    return 0;
}

void DB::ControlPanel(HWND hwnd)
{
    cPanel = new CPanel(connection);
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CONTROL_PANEL), hwnd, ControlPanelProc);          
}

void DB::Inventary(HWND hwnd, int a)
{
    if (a == 1)
    {
        totale = 0.0;
        Query query = connection->query();
        query << "select prezzo_acquisto, quantita from cd";
        Result res = query.store();
        Result::iterator i;
        for(i=res.begin(); i!= res.end(); i++)
        {
            Row r = *i;
            totale += (float)r[0] * (float)r[1];
        }    
        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INVENTORY), hwnd, InventoryDlgProc);  
    }
    if (a != 1)
    {
        report = new Report(connection, a-2);
        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SUMMARY), hwnd, ReportDlgProc);    
    }    
}

void DB::InsertInOrder(HWND hwnd)
{
    Row row;
    int indice = (int)SendMessage(listview.hCntrl, LVM_GETNEXTITEM, WPARAM(-1), LVNI_SELECTED);
    if (indice != -1)
    {
        row = *(result->begin() + indice);
        if ((int)row[11] > 0)
            pSheet->InsertInOrder(row);
        else
        {
            int ret = MessageBox( NULL, TEXT("The selected article is out of stock.\n\rDo you want to update the DB with this request ?"), TEXT("Out of stock"), MB_OKCANCEL|MB_ICONEXCLAMATION);                        
            if (ret == IDOK)
            {
                Query query = connection->query();
                query << "update cd set prenotazioni=prenotazioni+1 where indice='" << (int)row[0] << "'";
                query.execute();
            }    
        }
    }    
}

void DB::Insert(HWND hwnd, int s)
{
    stato = s;
    if (s == 4)
    {
        HMENU menu = GetMenu(hAppWnd);
        for(int i=1202; i<1217; i++)
            EnableMenuItem(menu, i, MF_GRAYED);
        
        PROPSHEETPAGE psp[2];
        PROPSHEETHEADER psh;
        pSheet = new PSheet(connection, true);
        //delivery = new Delivery(connection, true);
    
        psp[0].dwSize = sizeof(PROPSHEETPAGE);
        psp[0].dwFlags = PSP_USETITLE;
        psp[0].hInstance = NULL;
        psp[0].pszTemplate = MAKEINTRESOURCE(IDD_INSERT_ORDER);
        psp[0].pszIcon = NULL;
        psp[0].pfnDlgProc = InsertOrderProc;
        psp[0].pszTitle = "Order";
        psp[0].lParam = 0;

        psp[1].dwSize = sizeof(PROPSHEETPAGE);
        psp[1].dwFlags = PSP_USETITLE;
        psp[1].hInstance = NULL;
        psp[1].pszTemplate = MAKEINTRESOURCE(IDD_DELIVERY);
        psp[1].pszIcon = NULL;
        psp[1].pfnDlgProc = DeliveryProc;
        psp[1].pszTitle = "Delivery";
        psp[1].lParam = 0;

        psh.dwSize = sizeof(PROPSHEETHEADER);
        psh.dwFlags = PSH_PROPSHEETPAGE;
        psh.hwndParent = hwnd;
        psh.hInstance = NULL;
        psh.pszIcon = NULL;
        psh.pszCaption = (LPSTR) "Insert/Update Order";
        psh.nPages = sizeof(psp)/sizeof(PROPSHEETPAGE);
        psh.ppsp = (LPCPROPSHEETPAGE) &psp;
    
        PropertySheet(&psh);         
        stato = 0;
        SendDlgItemMessage(hAppWnd, IDC_LISTVIEW, LB_RESETCONTENT, 0, 0);
        for(int i=1202; i<1217; i++)
            EnableMenuItem(menu, i, MF_ENABLED);
    } 
    if (s == 1)
    {
        viewCD = new ViewCD();
        int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INSERT_CD), hwnd, InsertProc);
        if (ret == IDCANCEL) 
        {}
        if (ret == IDOK)
        { 
            try
            {
                int indice;
                Query query = connection->query();
                query << "select max(indice) as indice from cd"; 
                Result res = query.store(); 
                Row r = *(res.begin());
                if ((string)r[0] == "NULL")
                   indice = 0;
                else
                {    
                    Row r = *(res.begin());
                    indice = (int)r[0]+1; 
                }

                string* edit = viewCD->GetEdit();
                cd riga;
                riga.indice = indice;
                riga.stato = viewCD->GetStatus();
                riga.artista = edit[0]; riga.titolo = edit[1]; riga.etichetta = edit[2]; 
                riga.fornitore = edit[4]; riga.formato = edit[3]; riga.codice = edit[5]; 
                riga.prezzo_acquisto = atof(edit[6].c_str()); riga.prezzo_vendita = atof(edit[7].c_str()); 
                riga.prezzo_offerta = atof(edit[8].c_str());
                riga.quantita = atoi(edit[9].c_str()); riga.prenotazioni = atoi(edit[10].c_str()); 
                riga.venduti = atoi(edit[11].c_str());
                int limit = edit[12].length();
                if (edit[12].substr(0, 1) == "'")
                    edit[12].insert(0,"\\");
            
                for (int z=1; z<=limit; z++)
                {
                   
                    if ((edit[12].substr(z, 1) == "'") &&  (edit[12].substr(z-1, 1) != "\\"))
                        edit[12].insert(z,"\\");
                } 
                
                query.insert(riga);
                query.execute();
                query << "insert into note values('" << (int)r[0]+1 << "','" << edit[12] << "')";
                query.execute();
            }
            catch(BadQuery er)
            {
                MessageBox( NULL, TEXT(er.error.c_str()), TEXT("ERROR"), MB_OK|MB_ICONERROR);
            }
        }
    }
    if (s == 2)
    {
        viewClient = new ViewClient();
        int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INSERT_CLIENT), hwnd, InsertClientProc);
        if (ret == IDCANCEL) 
        {}
        if (ret == IDOK)
        {
            try
            {
                int indice;
                Query query = connection->query();
                query << "select max(indice) as indice from clienti"; 
                Result res = query.store(); 
                Row r = *(res.begin());
                if ((string)r[0] == "NULL")
                   indice = 0;
                else
                    indice = (int)r[0]+1; 

                string* edit = viewClient->GetEdit();
                clienti riga;
                riga.indice = indice;
                riga.nome = edit[0]; riga.cognome = edit[1]; riga.via1 = edit[2];
                riga.citta1 = edit[3]; riga.stato1 = edit[4]; riga. cap1 = edit[5];
                riga.nazione1 = edit[6]; riga.presso = edit[7];
                riga.via2 = edit[8]; riga.citta2 = edit[9];
                riga.stato2 = edit[10]; riga.cap2 = edit[11]; riga.nazione2 = edit[12];
                riga.telefono = edit[13]; riga.cellulare = edit[14]; riga.email = edit[15];
                riga.carta = edit[16]; riga.iva = edit[17]; riga.note = edit[18];
                int limit = edit[18].length();
                if (edit[18].substr(0, 1) == "'")
                    edit[18].insert(0,"\\");
            
                for (int z=1; z<=limit; z++)
                {
                   
                    if ((edit[18].substr(z, 1) == "'") &&  (edit[18].substr(z-1, 1) != "\\"))
                        edit[18].insert(z,"\\");
                } 
                if ((edit[0] != "") && (edit[1] != ""))
                {        
                    query.insert(riga);
                    query.execute();
                }    
                else
                   MessageBox( NULL, "Every client MUST have a name and a surname at least.", TEXT("ERROR"), MB_OK|MB_ICONERROR);
            }
            catch(BadQuery er)
            {
                MessageBox( NULL, TEXT(er.error.c_str()), TEXT("ERROR"), MB_OK|MB_ICONERROR);
            }
        }
    }    
}

void DB::Update(HWND hwnd, Row row)
{
    if (stato == 1)
    {
        Query query = connection->query();
        query << "select * from note where indice='" << (int)row[0] << "'";
        Result res = query.store();
        Row row2 = res[0];
        viewCD = new ViewCD(row, row2);
        int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INSERT_CD), hwnd, InsertProc);
        if (ret == IDCANCEL) 
        {}
        if (ret == ID_APPLY)
        {
            try
            {
                string* edit = viewCD->GetEdit();
                cd riga, old_riga;
                old_riga = row;
                riga.stato = viewCD->GetStatus();
                riga.artista = edit[0]; riga.titolo = edit[1]; riga.etichetta = edit[2]; 
                riga.fornitore = edit[4]; riga.formato = edit[3]; riga.codice = edit[5]; 
                riga.prezzo_acquisto = atof(edit[6].c_str()); riga.prezzo_vendita = atof(edit[7].c_str()); 
                riga.prezzo_offerta = atof(edit[8].c_str());
                riga.quantita = atoi(edit[9].c_str()); riga.prenotazioni = atoi(edit[10].c_str()); 
                riga.venduti = atoi(edit[11].c_str());
                riga.indice = (int)row[0];
                query.update(old_riga, riga);
                query.execute();
                int limit = edit[12].length();
                if (edit[12].substr(0, 1) == "'")
                    edit[12].insert(0,"\\");
            
                for (int z=1; z<=limit; z++)
                {
                   
                    if ((edit[12].substr(z, 1) == "'") &&  (edit[12].substr(z-1, 1) != "\\"))
                        edit[12].insert(z,"\\");
                } 
                query << "update note set note='" << edit[12] << "' where indice='" << (int)row[0] << "'";
                query.execute();
            }
            catch(BadQuery er)
            {
                MessageBox( NULL, TEXT(er.error.c_str()), TEXT("ERROR"), MB_OK|MB_ICONERROR);
            }
        }
    }
    if (stato == 2)
    {
        viewClient = new ViewClient(row);
        int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INSERT_CLIENT), hwnd, InsertClientProc);
        if (ret == IDCANCEL) 
        {}
        if (ret == ID_APPLY)
        {
            try
            {
                Query query = connection->query();
                string* edit = viewClient->GetEdit();
                clienti riga, old_riga;
                old_riga = row;
                riga.indice = (int)row[0];
                riga.nome = edit[0]; riga.cognome = edit[1]; riga.via1 = edit[2];
                riga.citta1 = edit[3]; riga.stato1 = edit[4]; riga. cap1 = edit[5];
                riga.nazione1 = edit[6]; riga.presso = edit[7];
                riga.via2 = edit[8]; riga.citta2 = edit[9];
                riga.stato2 = edit[10]; riga.cap2 = edit[11]; riga.nazione2 = edit[12];
                riga.telefono = edit[13]; riga.cellulare = edit[14]; riga.email = edit[15];
                riga.carta = edit[16]; riga.iva = edit[17]; 
                int limit = edit[18].length();
                if (edit[18].substr(0, 1) == "'")
                    edit[18].insert(0,"\\");
            
                for (int z=1; z<=limit; z++)
                {
                    if ((edit[18].substr(z, 1) == "'") &&  (edit[18].substr(z-1, 1) != "\\"))
                        edit[18].insert(z,"\\");
                } 
                riga.note = edit[18];
                query.update(old_riga, riga);
                query.execute();
            }
            catch(BadQuery er)
            {
                MessageBox( NULL, TEXT(er.error.c_str()), TEXT("ERROR"), MB_OK|MB_ICONERROR);
            }
        }
    } 
}

void DB::Remove(HWND hwndCtl)
{
    int ret = MessageBox( NULL, TEXT("If you click Yes, you won't be able to undo this Delete operation.\n\rAre you sure you want to delete this record ?"), 
            TEXT("Delete operation"), MB_YESNO|MB_ICONWARNING);
    if (ret == 6)
    {
        int indice = (int)SendMessage(listview.hCntrl, LVM_GETNEXTITEM, WPARAM(-1), LVNI_SELECTED);
        if (indice != -1)
        {
            try
            {
                Query query = connection->query();
                string ricerca;
                Row row = *(result->begin() + indice);
                int i = (int)row[0];
                if (stato == 1)
                {
                    query << "delete from note where indice = '" << i << "'";
                    query.execute();
                    ricerca = "delete from cd where indice='";
                }
                if (stato == 2)
                    ricerca = "delete from clienti where indice='";
                
                query << ricerca << i << "'";
                query.execute();
            }
            catch(BadQuery er)
            {
                MessageBox( NULL, TEXT(er.error.c_str()), TEXT("ERROR"), MB_OK|MB_ICONERROR);
            }                                    
        }
        Query query = connection->query();
        query << old_query;
        *result = query.store();
        FillListBox();
    }
}

void DB::Select(HWND hwndCtl)
{
    int indice = (int)SendMessage(listview.hCntrl, LVM_GETNEXTITEM, WPARAM(-1), LVNI_SELECTED);
    if (indice != -1)
    {
        Row row = *(result->begin() + indice);
        Update(hwndCtl, row);
    }
    Query query = connection->query();
    query << old_query;
    *result = query.store();
    FillListBox();
}

void DB::Searcher(HWND hwndCtl, int s)
{
    BOOL q = true;
    stato = s;
    string ricerca;
    if ((s == 1) || (s == 4))
    {
        searchCD = new Search();
        int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SEARCH_CD), hwndCtl, SearchProc);
        if (ret == IDCANCEL) 
            q = false;
        if (ret == IDOK)
        {
            BOOL a = false;
            string s1 = searchCD->GetArtist();
            string s2 = searchCD->GetSupplier();
            string s3 = searchCD->GetCompany();
            string s4 = searchCD->GetQuantity();
            string s5 = searchCD->GetCode();
            if (s4 == "")
                s4 = "10000";
            ricerca = "select * from cd where";
            ricerca = ricerca + " artista like '%" + s1 + "%' and";
            ricerca = ricerca + " etichetta like '%" + s3 + "%' and";
            ricerca = ricerca + " fornitore like '%" + s2 + "%' and";
            ricerca = ricerca + " codice like '%" + s5 + "%' and";
            ricerca = ricerca + " quantita < '" + s4 + "' and";
            if (searchCD->GetDeleted())
                ricerca = ricerca + " stato = '3'";
            else
                ricerca = ricerca + " stato <> '3'";
                
            if ((s3 != "") && (s1 == ""))
                ricerca = ricerca + " order by etichetta, artista, titolo, fornitore, quantita";
            else if ((s5 != "") && (s1 == ""))
                ricerca = ricerca + " order by codice, artista, titolo, etichetta";                
            else if ((s1 == "") && (s2 == "") && (s3 == "") && (s4 == "") && (s5 == ""))    
                ricerca = ricerca + " order by artista, titolo, etichetta, fornitore, quantita";
            else if ((s4 != "10000") && (s1 == ""))
                ricerca = ricerca + " order by quantita, artista, titolo, etichetta, fornitore";                
            else    
                ricerca = ricerca + " order by artista, titolo, etichetta, fornitore, quantita";
        }
    }
    if (s == 2)
    {
        searchClient = new SearchClient();
        int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SEARCH_CLIENT), hwndCtl, SearchClientProc);
        if (ret == IDCANCEL) 
            q = false;
        if (ret == IDOK)
        {
            BOOL a = false;
            string s1 = searchClient->GetSurname();
            string s2 = searchClient->GetCity();
            string s3 = searchClient->GetCountry();
            ricerca = "select * from clienti where";
            ricerca = ricerca + " cognome like '" + s1 + "%' and";
            ricerca = ricerca + " (citta1 like '" + s2 + "%'";
            ricerca = ricerca + " or citta2 like '" + s2 + "%') and";
            ricerca = ricerca + " (nazione1 like '" + s3 + "%'";
            ricerca = ricerca + " or nazione2 like '" + s3 + "%')";
            ricerca = ricerca + " order by cognome, nome, citta1, nazione1";
        }
    }
    if (s == 5)
    {
        PROPSHEETPAGE psp[2];
        PROPSHEETHEADER psh;
        pSheet = new PSheet(connection, false);
    
        psp[0].dwSize = sizeof(PROPSHEETPAGE);
        psp[0].dwFlags = PSP_USETITLE;
        psp[0].hInstance = NULL;
        psp[0].pszTemplate = MAKEINTRESOURCE(IDD_INSERT_ORDER);
        psp[0].pszIcon = NULL;
        psp[0].pfnDlgProc = InsertOrderProc;
        psp[0].pszTitle = "Order";
        psp[0].lParam = 0;

        psp[1].dwSize = sizeof(PROPSHEETPAGE);
        psp[1].dwFlags = PSP_USETITLE;
        psp[1].hInstance = NULL;
        psp[1].pszTemplate = MAKEINTRESOURCE(IDD_DELIVERY);
        psp[1].pszIcon = NULL;
        psp[1].pfnDlgProc = DeliveryProc;
        psp[1].pszTitle = "Delivery";
        psp[1].lParam = 0;

        psh.dwSize = sizeof(PROPSHEETHEADER);
        psh.dwFlags = PSH_PROPSHEETPAGE;
        psh.hwndParent = hwndCtl;
        psh.hInstance = NULL;
        psh.pszIcon = NULL;
        psh.pszCaption = (LPSTR) "Insert/Update Order";
        psh.nPages = sizeof(psp)/sizeof(PROPSHEETPAGE);
        psh.ppsp = (LPCPROPSHEETPAGE) &psp;
    
        PropertySheet(&psh); 
        q = false;
    }    
    if (q)
    {
        try
        {
            Query query = connection->query();
            query << ricerca;
            old_query = ricerca;
            result = new Result();
            *result = query.store();
            FillListBox();
        }
        catch (BadQuery er)
        {
            MessageBox( NULL, TEXT(er.error.c_str()), TEXT("ERROR"), MB_OK|MB_ICONERROR);
        }
    }              
}            

void DB::FillListBox()
{
    SendDlgItemMessage(hAppWnd, IDC_LISTVIEW, LVM_DELETEALLITEMS, 0, 0);
    if ((stato == 1) || (stato == 4))
    {
        LV_COLUMN listCol;
        memset(&listCol, 0, sizeof(LV_COLUMN));
        listCol.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
        listCol.pszText = "Artist";
        listCol.cx = 120;
        ListView_SetColumn(listview.hCntrl, 0, &listCol);
        listCol.pszText = "Title";
        listCol.cx = 160;
        ListView_SetColumn(listview.hCntrl, 1, &listCol);
        listCol.pszText = "Label";
        listCol.cx = 100;
        ListView_SetColumn(listview.hCntrl, 2, &listCol);
        listCol.pszText = "Code";
        listCol.cx = 70;
        ListView_SetColumn(listview.hCntrl, 3, &listCol);
        listCol.pszText = "Price";
        listCol.cx = 70;
        ListView_SetColumn(listview.hCntrl, 4, &listCol);
        listCol.pszText = "Quantity";
        listCol.cx = 50;
        ListView_SetColumn(listview.hCntrl, 5, &listCol);
        listCol.pszText = "Ordered";
        listCol.cx = 50;
        ListView_SetColumn(listview.hCntrl, 6, &listCol);
        listCol.pszText = "Format";
        listCol.cx = 70;
        ListView_SetColumn(listview.hCntrl, 7, &listCol);
    }            
    if (stato == 2)
    {
        LV_COLUMN listCol;
        memset(&listCol, 0, sizeof(LV_COLUMN));
        listCol.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
        listCol.pszText = "Surname";
        listCol.cx = 150;
        ListView_SetColumn(listview.hCntrl, 0, &listCol);
        listCol.pszText = "Name";
        listCol.cx = 150;
        ListView_SetColumn(listview.hCntrl, 1, &listCol);
        listCol.pszText = "City";
        listCol.cx = 150;
        ListView_SetColumn(listview.hCntrl, 2, &listCol);
        listCol.pszText = "Country";
        listCol.cx = 150;
        ListView_SetColumn(listview.hCntrl, 3, &listCol);
    }            
    
    LV_ITEM listItem;
    memset(&listItem, 0, sizeof(LV_ITEM));
    listItem.mask = LVIF_TEXT;
    listItem.cchTextMax = 100;
    string linea;
    Row row;
    Result::iterator i;
    int indice = 0;
    for (i=result->begin(); i != result->end(); i++)
    {
        row = *i;
        if ((stato == 1) || (stato == 4))
        {
            listItem.iItem = indice;
            listItem.iSubItem = 0;
            linea = (string)row[1];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEMSTATE, indice, (LPARAM)&listItem);
            SendMessage(listview.hCntrl, LVM_INSERTITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 1;
            linea = (string)row[2];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 2;
            linea = (string)row[3];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 3;
            linea = (string)row[6];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 4;
            if ((int)row[10] != 2)
                linea = (string)row[8];
            else     
                linea = (string)row[9];
            // cambia colore della riga...    
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 5;
            linea = (string)row[11];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 6;
            linea = (string)row[12];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 7;
            linea = (string)row[4];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
        }            
        if (stato == 2)
        {
            listItem.iItem = indice;
            listItem.iSubItem = 0;
            linea = (string)row[2];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEMSTATE, indice, (LPARAM)&listItem);
            SendMessage(listview.hCntrl, LVM_INSERTITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 1;
            linea = (string)row[1];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 2;
            linea = (string)row[4];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
            listItem.iSubItem = 3;
            linea = (string)row[7];
            listItem.pszText = (CHAR*)linea.c_str();     
            SendMessage(listview.hCntrl, LVM_SETITEM, 0, (LPARAM)&listItem);
        }             
        indice++;
    }    
}

int DB::OnCreate(CREATESTRUCT *cs)
{
    RECT rc;
    GetClientRect(hAppWnd, &rc);
    listview.SetWndClassName(WC_LISTVIEW);
    listview.SetWndCaption(TEXT(""));
    listview.nStyle|=LVS_REPORT;
    listview.nExStyle |= WS_EX_CLIENTEDGE;
    listview.Top=0;
    listview.Left=0;
    listview.Width=rc.right - rc.left;
    listview.Height=rc.bottom - rc.top;
    listview.nID=IDC_LISTVIEW;	
    listview.Create(hAppWnd);
    LV_COLUMN listCol;
    SendMessage(listview.hCntrl, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
    memset(&listCol, 0, sizeof(LV_COLUMN));
    listCol.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    listCol.pszText = "";
    listCol.cx = 150;
    SendMessage(listview.hCntrl, LVM_INSERTCOLUMN, 1, (LPARAM)&listCol);
    SendMessage(listview.hCntrl, LVM_INSERTCOLUMN, 2, (LPARAM)&listCol);
    SendMessage(listview.hCntrl, LVM_INSERTCOLUMN, 3, (LPARAM)&listCol);
    SendMessage(listview.hCntrl, LVM_INSERTCOLUMN, 4, (LPARAM)&listCol);
    SendMessage(listview.hCntrl, LVM_INSERTCOLUMN, 5, (LPARAM)&listCol);
    SendMessage(listview.hCntrl, LVM_INSERTCOLUMN, 6, (LPARAM)&listCol);
    SendMessage(listview.hCntrl, LVM_INSERTCOLUMN, 7, (LPARAM)&listCol);
    SendMessage(listview.hCntrl, LVM_INSERTCOLUMN, 8, (LPARAM)&listCol);
    //SetFocus(listview.hCntrl);
    SendMessage(listview.hCntrl, WM_SETREDRAW, true, 0);
    return 0;
}

BOOL DB::OnDestroy()
{
    PostQuitMessage(0);    //signal end of application
    return 0;
}

TCHAR* DB::GetWndCaption()
{
    return chCaption;
}

TCHAR* DB::GetWndClassName()
{
    return chClassName;
}

void DB::SetInstance(HINSTANCE	hInstance)
{
    hInst = hInstance;
}

void DB::SetWndCaption(TCHAR* chCap)
{
    if ((chCap)&&(lstrlen(TEXT(chCap))<256))
	{
		lstrcpy(chCaption,chCap);
	}
}

void DB::SetWndClassName(TCHAR* chClass)
{
    if ((chClass)&&(lstrlen(TEXT(chClass))<100))
	{
		lstrcpy(chClassName,chClass);
	}
}

TCHAR* CppCntrl::GetWndCaption()
{
    return chCaption;
}

TCHAR* CppCntrl::GetWndClassName()
{
    return chClassName;
}

void CppCntrl::SetInstance(HINSTANCE	hInstance)
{
    hInst = hInstance;
}

void CppCntrl::SetWndCaption(TCHAR* chCap)
{
    if ((chCap)&&(lstrlen(TEXT(chCap))<256))
	{
		lstrcpy(chCaption,chCap);
	}
}

void CppCntrl::SetWndClassName(TCHAR* chClass)
{
    if ((chClass)&&(lstrlen(TEXT(chClass))<100))
	{
		lstrcpy(chClassName,chClass);
	}
}

