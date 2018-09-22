#include "Report.h"
#include "resource.h"

Report::Report(Connection* q, int y)
{
    stato = y;
    connection = q;
    indirizzo = 0;
    quantita = 0;
    prezzo = 0.0;
}

Report::~Report()
{}

BOOL CALLBACK Report::DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HWND hBtn1;
    switch (Message)
    {
        case WM_COMMAND:
            if ((HIWORD(wParam) == CBN_SELCHANGE) && (LOWORD(wParam) == IDC_MESI))
                FillList();    
            if ((HIWORD(wParam) == EN_CHANGE) && (LOWORD(wParam) == IDC_ANNO))
            {
                hBtn1 = GetDlgItem(hwndCtl, IDC_VENDITE); 
                SendMessage(hBtn1, LB_RESETCONTENT, 0, 0);
            }    
            if (HIWORD(wParam) == BN_CLICKED)
            {
                if (LOWORD(wParam) == IDOK)
                {
                    OnExit();    
                    EndDialog(hwnd, IDOK); 
                }    
                if (LOWORD(wParam) == IDCANCEL)
                    EndDialog(hwnd, IDCANCEL);                    
            }
            return true;
        case WM_NOTIFY:
            if (LOWORD(wParam) == IDC_SPIN1)
            {
                hBtn1 = GetDlgItem(hwndCtl, IDC_VENDITE); 
                SendMessage(hBtn1, LB_RESETCONTENT, 0, 0);
            }
            return true;            
        case WM_INITDIALOG:
            hwndCtl = hwnd;
            InitList();
            FillCombo();
            return true;
        default:
            return false;
	}
} 

void Report::OnExit()
{
    if (stato != 0)
    {
        Result res;
        Result::iterator j;
        Row r;
        Query query = connection->query();
        HWND listview;
        listview = GetDlgItem(hwndCtl, IDC_VENDITE);
        int numLista = SendMessage(listview, LVM_GETITEMCOUNT, 0, 0);
    
        if (stato == 1)
        {
            query << "select indice from ordine_riepilogo where spedito = '0' order by data, indice";
            res = query.store();
            for(int i=0; i<numLista; i++)
            {
                int pippo = ListView_GetCheckState(listview, i);
                if (pippo == 1)
                {
                    r = *(res.begin()+i);      
                    query << "update ordine_riepilogo set spedito = '1' where indice = '" << (int)r[0] << "'";
                    query.execute();
                }
            }        
        } 
        
        if (stato == 2)
        {
            query << "select indice from ordine_riepilogo where pagato = '0' order by data, indice";
            res = query.store();
            for(int i=0; i<numLista; i++)
            {
                int pippo = ListView_GetCheckState(listview, i);
                if (pippo == 1)
                {
                    r = *(res.begin()+i);      
                    query << "update ordine_riepilogo set pagato = '1' where indice = '" << (int)r[0] << "'";
                    query.execute();
                }
            }
        } 
    }
}

void Report::InitList()
{

    Query query = connection->query();
    query << "select edit from pannello_controllo where combo = '0' order by indice";                    
    Result res = query.store();
    Result::iterator i;
    int num = 0;
    for (i = res.begin(); i != res.end(); i++)
    {
        Row r = *i;
        tipo_pagamento[num] = (string)r[0];
        num++;
    }       
    
    TCHAR* labels[] = {"Client", "Fattura", "Date", "Price", "Note", "Payment method"}; 
    int width[] = {150, 60, 70, 60, 140, 115};
    if (stato == 1)
        SetWindowText(hwndCtl, "Orders not yet sent");
    if (stato == 2)
        SetWindowText(hwndCtl, "Orders not yet paid");
        
    HWND listview = GetDlgItem(hwndCtl, IDC_VENDITE);
    if (stato == 0)
        SendMessage(listview, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    else
    {     
        SendMessage(listview, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES);
        HWND hEdit = GetDlgItem(hwndCtl, IDC_MESI);
        EnableWindow(hEdit, false);
        hEdit = GetDlgItem(hwndCtl, IDC_ANNO);
        EnableWindow(hEdit, false);
        hEdit = GetDlgItem(hwndCtl, IDC_SPIN1);
        EnableWindow(hEdit, false);
    }
    LV_COLUMN listCol;
    memset(&listCol, 0, sizeof(LV_COLUMN));
    
    listCol.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    listCol.pszText = "";
    for (int i = 0; i<6; i++)
    {
        listCol.pszText = labels[i];
        listCol.cx = width[i];
        SendMessage(listview, LVM_INSERTCOLUMN, i, (LPARAM)&listCol);
    }
    if (stato == 0)
        InitImage();
} 

void Report::InitImage()
{
    HWND list = GetDlgItem(hwndCtl, IDC_VENDITE);
	HIMAGELIST hImageList, hImageNormal;
	hImageNormal = ImageList_Create(32, 32, ILC_COLOR8, 3, 3);
	hImageList = ImageList_Create(16, 16, ILC_COLOR8, 3, 3);
	HICON hIcon;
	for(int i = 0; i < 3; i++)
	{
		hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1 + i));
		ImageList_AddIcon(hImageNormal, hIcon);
		ImageList_AddIcon(hImageList, hIcon);
		DestroyIcon(hIcon);
	}
	/*	you can use bitmap too
	// bitmap
	HBITMAP hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_LISTIMAGE));
	ImageList_Add(hImageList, hBmp, NULL);
	DeleteObject(hBmp);
	*/
	SendMessage(list, LVM_SETIMAGELIST, LVSIL_NORMAL, (LPARAM)hImageNormal);
	SendMessage(list, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)hImageList);
}	

void Report::FillCombo()
{
    if (stato == 0)
    {    
        string mesi[12] = {"January ", "February ", "March ", "April ", "May ", "June ", 
                "July ", "August ", "September ", "October ", "November ", "December "};
        HWND hEdit = GetDlgItem(hwndCtl, IDC_MESI);   
        for (int i=0; i <12; i++)
            SendMessage(hEdit, CB_ADDSTRING, 0, (LPARAM) mesi[i].c_str());
        SYSTEMTIME time;        
        char b[4];
        GetLocalTime(&time);
        string anno = itoa (time.wYear, b, 10);
        hEdit = GetDlgItem(hwndCtl, IDC_ANNO); 
        SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) anno.c_str());
        SendMessage(hEdit, EM_LIMITTEXT, (WPARAM)4, 0);
        hEdit = GetDlgItem(hwndCtl, IDC_SPIN1);
        SendMessage(hEdit, UDM_SETRANGE, 0, (LPARAM) MAKELONG(2200, 1988));  
    }    
    else
        FillList();
}

void Report::FillList()
{
    SendDlgItemMessage(hwndCtl, IDC_VENDITE, LVM_DELETEALLITEMS, 0, 0);
    Result res;
    Query query = connection->query();
    HWND hEdit;
    TCHAR* passwd;
    char b[2];
    int nLen, indice;
    string giorno, linea, inf, sup;
    switch(stato)
    {
        case 0:
            hEdit = GetDlgItem(hwndCtl, IDC_VENDITE);
            SendMessage(hEdit, LB_RESETCONTENT, 0, 0);
            hEdit = GetDlgItem(hwndCtl, IDC_ANNO);   
            nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
            passwd = new TCHAR[nLen+1]; 
            GetWindowText(hEdit, passwd, nLen+1);
    
            hEdit = GetDlgItem(hwndCtl, IDC_MESI); 
            indice = SendMessage(hEdit, CB_GETCURSEL, 0, 0);
            giorno = itoa(indice+1, b, 10);
            
            if (giorno.length() == 1)
                giorno = "0" + giorno;
    
            inf = passwd;
            inf = inf + "-" + giorno + "-00";
            sup = passwd;
            sup = sup + "-" + giorno + "-32";
            hEdit = GetDlgItem(hwndCtl, IDC_VENDITE);
            
            query << "select p2.cognome, p1.fatture, p1.data, p1.prezzo, p1.nota, p1.pagamento" <<
                    ", p1.indice_cliente, p1.pagato, p1.spedito from " <<
                    "ordine_riepilogo as p1, clienti as p2" << 
                    " where ((p1.indice_cliente = p2.indice) and (p1.data > '" << 
                    inf << "') and (p1.data < '" << sup << "')) order by p1.data, p1.indice";
            res = query.store();
            break;
        case 1:
            query << "select p2.cognome, p1.fatture, p1.data, p1.prezzo, p1.nota, p1.pagamento" <<
                    ", p1.indice_cliente from ordine_riepilogo as p1, clienti as p2" << 
                    " where ((p1.indice_cliente = p2.indice) and (p1.spedito = '0')) order by p1.data, p1.indice";
            res = query.store();
            break;
        case 2:
            query << "select p2.cognome, p1.fatture, p1.data, p1.prezzo, p1.nota, p1.pagamento" <<
                    ", p1.indice_cliente from ordine_riepilogo as p1, clienti as p2" << 
                    " where ((p1.indice_cliente = p2.indice) and (p1.pagato = '0')) order by p1.data, p1.indice";
            res = query.store();
            break;
    }
    
    Result::iterator i;
    int num = 0;
    for (i = res.begin(); i != res.end(); i++)
    {
        LV_ITEM lit;
        memset(&lit, 0, sizeof(LV_ITEM));
        Row row = *i;
        if (stato == 0)
            lit.mask = LVIF_IMAGE|LVIF_TEXT;
        else    
            lit.mask = LVIF_TEXT;
        lit.cchTextMax = 100;
        lit.iItem = num;
        
        if (stato == 0)
        {
            lit.iImage = 0;
            if ((int)row[7] == 0)
                lit.iImage = 1;
            if ((int)row[8] == 0)
                lit.iImage = 2;
        }        
        string s = (string)row[0];
        lit.pszText = (CHAR*)s.c_str();
        SendDlgItemMessage(hwndCtl, IDC_VENDITE, LVM_SETITEMSTATE, num, (LPARAM)&lit);
        SendDlgItemMessage(hwndCtl, IDC_VENDITE, LVM_INSERTITEM, num, (LPARAM)&lit);
        for(int j=1; j<6; j++)
        {
            lit.iSubItem = j;
            if (j != 5)
                s = (string)row[j];
            else
                s = tipo_pagamento[(int)row[j]];    
            lit.pszText = (CHAR*)s.c_str();
            SendDlgItemMessage(hwndCtl, IDC_VENDITE, LVM_SETITEM, num, (LPARAM)&lit);
        } 
        num++;
    }
}
