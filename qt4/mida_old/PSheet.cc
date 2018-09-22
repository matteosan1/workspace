#include "PSheet.h"
#include "ViewClient.h"
#include "resource.h"
#include "math.h"

sql_create_22(ordine_riepilogo, 3, 22,
    int, indice,
    int, fatture,
	string, data,
	int, quantita,
	int, indice_cliente,
	int, indirizzo,
	int, pagamento,
	float, prezzo,
	float, iva,
	float, spedizione,
	float, spedizione_vera,
	float, sconto,
    string, nota,
	int, pagato,
	int, spedito,
    int, euroiva,
    int, porto,
    int, aspetto,
    int, colli,
    float, peso,
    string, data_invio,
    string, trasporto);
 
sql_create_5(ordini, 4, 5,
    int, indice_ordine,
	int, indice_CD,
	string, codice, 	
	int, quantita,
	float, prezzo);

BOOL CALLBACK VcDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

ViewClient* vc;

HFONT MyFont(PRINTDLG pd, int i);

float Rounded(float y)
{
    float temp_y = y;
    //cout << y << endl;
    y = y * 100.;
    //cout << y << endl;
    y = floorf(y);
    //cout << y << endl;
    y = y/100.;
    //cout << y << endl;
    return y;    
}

static HANDLE hDevMode, hDevNames;
RECT rcMargin;
HANDLE GetDevMode()
{
    PAGESETUPDLG psd;
    
    ZeroMemory(&psd, sizeof psd);
    psd.lStructSize = sizeof psd;
    psd.Flags = PSD_RETURNDEFAULT;

    PageSetupDlg(&psd);
    CopyRect(&rcMargin, &psd.rtMargin);
    hDevMode = psd.hDevMode;
    hDevNames = psd.hDevNames;

    return psd.hDevMode;
}

PSheet::PSheet(Connection* q, bool h)
{
    data = "";
    indirizzo = 0;
    quantita = 0;
    prezzo = 0.0;
    iva = 0.0;
    ordine = 0;
    prezzo_netto = 0.0;
    pagato = false;
    spedito = false;
    numero_fattura = 0;
    spedizione_posta = 0.0;
    insert = h;
    c = q;
    Query query = c->query();
    query << "select * from clienti order by cognome, nome";
    result = query.store();    
    vat = 0;
    metodo = 0;
    porto = 0;
    shape = 0;
    colli = 0;
    peso = 0.0;
    carrier = "";
    data_spedizione = "";
}

PSheet::~PSheet()
{}

BOOL CALLBACK PSheet::OrdDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HWND hBtn1;
    switch (Message)
    {            
        case WM_NOTIFY:
            switch(((NMHDR FAR *) lParam)->code)
            {
                case PSN_KILLACTIVE:
                    SetWindowLong(hwnd, DWL_MSGRESULT, FALSE);
                    return true;
                break;
                case PSN_APPLY:
                    SaveInfo();
                    OnOrdExit();
                break;
            }       
           
        case WM_COMMAND:
            if ((HIWORD(wParam) == EN_KILLFOCUS) && ((LOWORD(wParam) == IDC_REDUCTION) ||
                (LOWORD(wParam) == IDC_SHIPPMENT) || (LOWORD(wParam) == IDC_SHIPPMENT2)))
                OnChangePrice();
            if ((HIWORD(wParam) == CBN_SELCHANGE) && (LOWORD(wParam) == IDC_COMBO_CLIENT))
            {
                if (insert)
               {
                    HWND hCombo = GetDlgItem(hwndCtl, IDC_COMBO_CLIENT); 
                    int indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                    Row r = *(result.begin()+indice);
                    cliente = (int)r[0];
                    hBtn1 = GetDlgItem(hwndCtl, ID_INFO);
                    EnableWindow(hBtn1, true);
                }
                else
                {
                    string s = "";
                    hBtn1 = GetDlgItem(hwndCtl, IDC_IVA); 
                    SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
                    hBtn1 = GetDlgItem(hwndCtl, IDC_PRICE); 
                    SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
                    hBtn1 = GetDlgItem(hwndCtl, IDC_REDUCTION); 
                    SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
                    hBtn1 = GetDlgItem(hwndCtl, IDC_QUANTITY); 
                    SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
                    hBtn1 = GetDlgItem(hwndCtl, IDC_NOTE); 
                    SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) nota.c_str()); 
                    hBtn1 = GetDlgItem(hwndCtl, IDC_SHIPPMENT); 
                    SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
                    hBtn1 = GetDlgItem(hwndCtl, IDC_SHIPPMENT2);
                    SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
                    CheckRadioButton(hwndCtl, IDC_RADIO_ADR1, IDC_RADIO_ADR2, 0);
                    SendDlgItemMessage(hwndCtl, IDC_LIST, LB_RESETCONTENT, 0, 0);
                    OnSearchOrders();
                }
            }
            if ((HIWORD(wParam) == CBN_SELCHANGE) && (LOWORD(wParam) == IDC_COMBO_DATA))
            {
                OnFillOrder();
            }        
            if ((HIWORD(wParam) == LBN_DBLCLK) && (LOWORD(wParam) == IDC_LIST))
            {
                if (quantita != 0)
                    DeleteFromOrder();    
            }
            if (HIWORD(wParam) == BN_CLICKED)
            { 
                if (LOWORD(wParam) == ID_INFO)
                {
                    HWND hCombo = GetDlgItem(hwndCtl, IDC_COMBO_CLIENT); 
                    int indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
                    Row r = *(result.begin() + indice);
                    vc = new ViewClient(r);
                    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INSERT_CLIENT), hwndCtl, VcDlgProc);
                    delete vc;
                }
            }            
            return true;    
        case WM_INITDIALOG:
            hwndCtl = hwnd;
            ps = (PROPSHEETPAGE*)lParam;
            FillCombo();
            return true;
        default:
            return false;
	}
} 

void PSheet::OnFillOrder()
{
    HWND hCombo = GetDlgItem(hwndCtl, IDC_COMBO_DATA); 
    int indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
    Row r = *(result1.begin()+indice);
    ordine = (int)r[0];
    int decimal, segno; 
    char b[3];
    prezzo = (float)r[7];
    string s = (string)r[7];
    hCombo = GetDlgItem(hwndCtl, IDC_PRICE); 
    SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str()); 

    sconto = (float)r[11];
    s = (string)r[11];
    hCombo = GetDlgItem(hwndCtl, IDC_REDUCTION); 
    SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
    
    spedizione = (float)r[9];
    s = (string)r[9];
    hCombo = GetDlgItem(hwndCtl, IDC_SHIPPMENT); 
    SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
    
    spedizione_posta = (float)r[10];
    s = (string)r[10];
    hCombo = GetDlgItem(hwndCtl, IDC_SHIPPMENT2); 
    SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str()); 

    iva = (float)r[8];
    s = (string)r[8];
    hCombo = GetDlgItem(hwndCtl, IDC_IVA); 
    SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str());             
            
    quantita = (int)r[3];
    s = (string)r[3];
    hCombo = GetDlgItem(hwndCtl, IDC_QUANTITY); 
    SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str());
  
    nota = (string)r[12];
    hCombo = GetDlgItem(hwndCtl, IDC_NOTE); 
    SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) nota.c_str());
    
    data = (string)r[2];
    if ((int)r[13])
        CheckDlgButton(hwndCtl, IDC_CHECK_PAID, BST_CHECKED);
    else    
        CheckDlgButton(hwndCtl, IDC_CHECK_PAID, BST_UNCHECKED);
    if ((int)r[14])
        CheckDlgButton(hwndCtl, IDC_CHECK_SENT, BST_CHECKED);   
    else
        CheckDlgButton(hwndCtl, IDC_CHECK_SENT, BST_UNCHECKED);       
        
    numero_fattura = (int)r[1];
    indirizzo = (int)r[5];           
    CheckRadioButton(hwndCtl, IDC_RADIO_ADR1, IDC_RADIO_ADR2, IDC_RADIO_ADR1+(int)r[5]);

    cd_collo.clear();
    edit.clear();
    Query query = c->query();
    query << "select * from ordini where indice_ordine='" << ordine << "' order by indice_CD";
    Result res_temp = query.store();
    Result::iterator i;
    
    SendDlgItemMessage(hwndCtl, IDC_LIST, LB_RESETCONTENT, 0, 0);
    string linea;
    hCombo = GetDlgItem(hwndCtl, IDC_LIST); 
    for(i=res_temp.begin(); i!=res_temp.end(); i++)
    {
        r = *i;
        cd_collo.push_back((int)r[3]);
        try
        {
        query << "select * from cd where indice='" << (int)r[1] << "'";
        result2 = query.store();
        row_temp = *(result2.begin());
        edit.push_back(row_temp);
        linea = (string)r[3] + " - " + (string)row_temp[2] + " " + (string)row_temp[1];   
        SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM) linea.c_str());
        } catch(BadQuery* er)
        {cerr << er << endl;}
    }   
    InitDialog();
}

void PSheet::OnSearchOrders()
{
    HWND hCombo = GetDlgItem(hwndCtl, IDC_COMBO_CLIENT); 
    int indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
    Row r = *(result.begin()+indice);
    cliente = (int)r[0];
    string linea;
    Query query = c->query();
    query << "select * from ordine_riepilogo where indice_cliente='" << cliente << "' order by data";
    result1 = query.store();
    hCombo = GetDlgItem(hwndCtl, IDC_COMBO_DATA); 
    SendDlgItemMessage(hwndCtl, IDC_COMBO_DATA, CB_RESETCONTENT, 0, 0);
    
    if (result1.size() != 0)
    {
        Result::iterator i;
    
        for(i=result1.begin(); i!=result1.end(); i++)
        {
            r = *i;
            linea = (string)r[2];
            SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) linea.c_str());
        }                           
    }
}

void PSheet::OnOrdExit()
{
    if (!insert)
    {
        Query query = c->query();
        query << "update ordine_riepilogo set nota = '" << nota << "' where indice = '" << ordine << "'";    
        query.execute();
        query << "update ordine_riepilogo set pagato = '" << pagato << "' where indice = '" << ordine << "'";    
        query.execute();
        query << "update ordine_riepilogo set spedito = '" << spedito << "' where indice = '" << ordine << "'";    
        query.execute();
    }
    
    if((insert) && (quantita != 0))
    {
        int indice;
        Query query = c->query();
        ordine_riepilogo riga;
        query << "select max(indice) as indice from ordine_riepilogo"; 
        Result res = query.store(); 
        Row r = *(res.begin());
        if ((string)r[0] == "NULL")
            indice = 1;
        else 
            indice = (int)r[0]+1;
            
        riga.indice = indice; riga.data = data;
        riga.quantita = quantita; riga.indice_cliente = cliente;            
        riga.indirizzo = indirizzo; riga.prezzo = prezzo;            
        riga.spedizione = spedizione; riga.sconto = sconto;
        riga.spedizione_vera = spedizione_posta; 
        riga.iva = iva; riga.nota = nota;
        riga.fatture = numero_fattura; riga.pagato = pagato;
        riga.spedito = spedito; 

        riga.euroiva = vat; riga.pagamento = metodo; riga.porto = porto;
        riga.aspetto = shape; riga.colli = colli; riga.peso = peso;
        riga.trasporto = carrier; riga.data_invio = data_spedizione;
            
        query.insert(riga); 
        query.execute();
         
        ordini info;        
        vector<Row> cdInseriti = edit;
        vector<int> quantita = cd_collo;
        vector<Row>::iterator itRow; 
        vector<int>::const_iterator itQuantita = quantita.begin();   
        for(itRow = cdInseriti.begin(); itRow != cdInseriti.end(); itRow++)
        {            
            Row r = *itRow;
            info.indice_ordine = indice;
            info.indice_CD = (int)r[0];
            info.codice = (string)r[6];
            info.quantita = *itQuantita;
            if (((int)r[10] == 0) || ((int)r[10] == 1))
                info.prezzo = (float)r[8];
            else     
                info.prezzo = (float)r[9];
            query.insert(info);
            query.execute();
                
            query << "update cd set quantita=quantita-" << (*itQuantita) << ", venduti=venduti+"
                        << (*itQuantita) <<" where indice='" << (int)r[0] << "'";
            query.execute();                
            itQuantita++;
        }
        insert = false;
    }
}

void PSheet::FillCombo()
{   
    SYSTEMTIME time;
    GetLocalTime(&time);
    char b[4];
    string anno = itoa (time.wYear, b, 10);
    string mese = itoa (time.wMonth, b, 10);
    string giorno = itoa (time.wDay, b, 10);
    data = anno + "-" + mese + "-" + giorno;
    
    Query query = c->query();
    query << "select max(fatture) from ordine_riepilogo where year(data) = '" << anno << "'"; 
    Result res = query.store(); 
    Row r = *(res.begin());
    
    if ((string)r[0] == "NULL")
        numero_fattura = 1;
    else
        numero_fattura = (int)r[0]+1; 
    
    HWND hEdit = GetDlgItem(hwndCtl, IDC_COMBO_CLIENT);   
    SendDlgItemMessage(hwndCtl, IDC_COMBO_CLIENT, CB_RESETCONTENT, 0, 0);
    Result::iterator i;
   
    for (i=result.begin(); i != result.end(); i++)
    {
        r = *i;
        string linea = (string) r[2] + " " + (string) r[1];
        SendMessage(hEdit, CB_ADDSTRING, 0, (LPARAM) linea.c_str());
    }
   
    if (!insert)
    {   
        hEdit = GetDlgItem(hwndCtl, IDC_COMBO_DATA); 
        EnableWindow(hEdit, true);
        hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT); 
        EnableWindow(hEdit, false);
        hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT2); 
        EnableWindow(hEdit, false);
        hEdit = GetDlgItem(hwndCtl, IDC_REDUCTION); 
        EnableWindow(hEdit, false);
        hEdit = GetDlgItem(hwndCtl, IDOK); 
        EnableWindow(hEdit, true);
        hEdit = GetDlgItem(hwndCtl, IDC_RADIO_ADR1); 
        EnableWindow(hEdit, false);
        hEdit = GetDlgItem(hwndCtl, IDC_RADIO_ADR2); 
        EnableWindow(hEdit, false);
    }
}

void PSheet::DeleteFromOrder()
{
    HWND lv = GetDlgItem(hwndCtl, IDC_LIST);
    int indice = SendMessage(lv, LB_GETCURSEL, 0, 0);
    if(indice != LB_ERR)
    {
        Row r = edit[indice];
        if (((int)r[10] == 0) || ((int)r[10] == 1))
        {
            prezzo -= (float)r[8];
            prezzo_netto -= (float)r[8];
        }        
        else     
        {    
            prezzo -= (float)r[9];
            prezzo_netto -= (float)r[9];
        }        
        string s;
        char b[10];
        cd_collo[indice] -= 1;
        quantita--;
        if (cd_collo[indice] != 0)
        {
            s = itoa(cd_collo[indice], b, 10);
            s = s + " - " + (string)r[1] + " - " + (string)r[2]; 
            SendMessage(lv, LB_DELETESTRING, indice, 0);
            SendMessage(lv, LB_INSERTSTRING, indice, (LPARAM) s.c_str());   
        }      
        else
        {   
            SendMessage(lv, LB_DELETESTRING, indice, 0);
            edit.erase(edit.begin()+indice);
            cd_collo.erase(cd_collo.begin()+indice);
        }    
  
        OnChangePrice();
        s = itoa(quantita, b, 10);
        HWND hEdit = GetDlgItem(hwndCtl, IDC_QUANTITY); 
        SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s.c_str());
    }
}    

void PSheet::InsertInOrder(Row row)
{
    int isOrdered = -10;
    HWND lv = GetDlgItem(hwndCtl, IDC_LIST);
    vector<Row>::iterator itRow, selectedRow;
    char b[10];
    string s;
    int indice = 0, i=0;
    for(itRow = edit.begin(); itRow != edit.end(); itRow++)
    {   
        Row r = *itRow;
        if ((int)r[0] == (int)row[0])
        {
            selectedRow = itRow;
            isOrdered = indice;
        }    
        indice++;
    }
    
    if (isOrdered == -10)
    {
        edit.push_back(row);
        cd_collo.push_back(1);
        s = "1 - " + (string)row[1] + " - " + (string)row[2]; 
        SendMessage(lv, LB_INSERTSTRING, edit.size()-1, (LPARAM) s.c_str());
        
        if (((int)row[10] == 0) || ((int)row[10] == 1))
        {
            prezzo += (float)row[8];
            prezzo_netto  += (float)row[8];
        }    
        else     
        {
            prezzo += (float)row[9];
            prezzo_netto += (float)row[9];
        }    
        quantita++;
    }    
    else
    {
        cd_collo[isOrdered] += 1;
        quantita++;
        Row r = edit[isOrdered];
        s = itoa(cd_collo[isOrdered], b, 10);
        s = s + " - " + (string)r[1] + " - " + (string)r[2]; 
        SendMessage(lv, LB_DELETESTRING, isOrdered, 0);
        SendMessage(lv, LB_INSERTSTRING, isOrdered, (LPARAM) s.c_str());
        if (((int)row[10] == 0) || ((int)row[10] == 1))
        {
            prezzo += (float)row[8];
            prezzo_netto += (float)row[8];
        }    
        else     
        {
            prezzo += (float)row[9];
            prezzo_netto += (float)row[9];
        }    
    }       
  
    OnChangePrice();
    s = itoa(quantita, b, 10);
    HWND hEdit = GetDlgItem(hwndCtl, IDC_QUANTITY); 
    SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s.c_str());
}    

void PSheet::OnChangePrice()
{
    TCHAR* passwd;
    HWND hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT);   
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        spedizione = 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        spedizione = atof(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_REDUCTION);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        sconto = 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        sconto = atof(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT2);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        spedizione_posta= 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        spedizione_posta = atof(passwd);
    }
    
    prezzo = prezzo_netto + spedizione - sconto;
    int decimal, segno; 
    string s = _ecvt(prezzo, 6, &decimal, &segno);
    s.insert(decimal, ".");
    string s1 = s.substr(0, decimal+3);
    hEdit = GetDlgItem(hwndCtl, IDC_PRICE); 
    SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
    float prezzo_temp = (prezzo_netto-sconto-spedizione_posta+spedizione);
    //cout << prezzo_temp << " ";
    prezzo_temp = (prezzo_temp/1.2);
    //cout << prezzo_temp << " ";
    prezzo_temp = Rounded(prezzo_temp);
    //cout << prezzo_temp << endl;
    s = _ecvt((prezzo_netto-sconto-spedizione_posta+spedizione-prezzo_temp), 6, &decimal, &segno);
    s.insert(decimal, ".");
    s1 = s.substr(0, decimal+3);
    hEdit = GetDlgItem(hwndCtl, IDC_IVA); 
    SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
}

BOOL PSheet::OnPrint()
{
    
    HINSTANCE hInst;
    ZeroMemory(&pd, sizeof(pd));
    pd.lStructSize = sizeof(pd);    // always remember to set this!
    pd.hInstance = hInst;           // application process handle
    pd.hwndOwner = hwndCtl;
    GetDevMode();
    pd.hDevMode = hDevMode;
    pd.hDevNames = hDevNames;
    pd.Flags = PD_ALLPAGES|PD_HIDEPRINTTOFILE|PD_NOPAGENUMS|PD_RETURNDC;
    pd.nCopies   = 1;

    if(!PrintDlg(&pd))
        return FALSE;

    RECT margins;
    margins.left = MulDiv(rcMargin.left, GetDeviceCaps(pd.hDC, LOGPIXELSX), 1000);
    margins.top = MulDiv(rcMargin.top, GetDeviceCaps(pd.hDC, LOGPIXELSY), 1000);
    margins.right = MulDiv(rcMargin.right, GetDeviceCaps(pd.hDC, LOGPIXELSX), 1000);
    margins.bottom = MulDiv(rcMargin.bottom, GetDeviceCaps(pd.hDC, LOGPIXELSY), 1000);

    int iPOX = GetDeviceCaps(pd.hDC, PHYSICALOFFSETX);
    int iPOY = GetDeviceCaps(pd.hDC, PHYSICALOFFSETY);
    int iPW = GetDeviceCaps(pd.hDC, PHYSICALWIDTH);
    int iPH = GetDeviceCaps(pd.hDC, PHYSICALHEIGHT);
    
    int iLeftAdjust = margins.left - iPOX;
    int iTopAdjust = margins.top - iPOY;
    int iRightAdjust = margins.right - (iPW - iPOX - GetDeviceCaps(pd.hDC, HORZRES));
    int iBottomAdjust = margins.bottom - (iPH - iPOY - GetDeviceCaps(pd.hDC, VERTRES));
    int iWidth = GetDeviceCaps(pd.hDC, HORZRES) - (iLeftAdjust + iRightAdjust);
    int iHeight = GetDeviceCaps(pd.hDC, VERTRES) - (iTopAdjust + iBottomAdjust);
    
    hfontStd1 = MyFont(pd, 1);
    hfontBold1 = MyFont(pd, 2);
    hfontStd2 = MyFont(pd, 3);
    hfontBold2 = MyFont(pd, 4);
    hfontSmall = MyFont(pd, 5);

    SetMapMode(pd.hDC, MM_TEXT);
    
    TEXTMETRIC tm;
    SelectObject(pd.hDC, hfontStd1);
    GetTextMetrics(pd.hDC, &tm);
    yChar = tm.tmHeight;
    wChar = tm.tmAveCharWidth;
    
    int iHeaderHeight = 10;
    int iLinesPerPage = iHeight / yChar;
// iLine = yChar * iLinesPerPage * iPage + iHeaderHeight;      
    int iPage = 0;
    iLine = 0;
    
    DOCINFO di;
    BOOL bSuccess = TRUE;
    char* szFileName = "Stampa fattura";
    ZeroMemory(&di, sizeof(di));
    di.cbSize = sizeof(di);
    di.lpszDocName = szFileName;        
       
    if(StartDoc(pd.hDC, &di) > 0)
    {
        for(int z = 0; z < pd.nCopies; z++)
        {    
            if(StartPage(pd.hDC) < 0)
            {
                bSuccess = FALSE;
            }
            if (IsDlgButtonChecked(hwndCtl2, IDC_CHECK_FATTURA) == BST_CHECKED)
            {
                PrintHeader();
                PrintAddress();
                PrintInitTable();
                PrintTable(true);
                PrintEndTable(true);
                if(EndPage(pd.hDC) < 0)
                {   
                    bSuccess = FALSE;
                }
            }
            
            if (IsDlgButtonChecked(hwndCtl2, IDC_CHECK_FATTURA_SEMPLICE) == BST_CHECKED)
            {
                PrintInitTable();
                PrintTable(false);    
                PrintEndTable(false);
                if(EndPage(pd.hDC) < 0)
                {
                    bSuccess = FALSE;
                }
            }   
            
            DeleteObject(hfontStd1);
            DeleteObject(hfontStd2);
            DeleteObject(hfontBold1);
            DeleteObject(hfontBold2);
            DeleteObject(hfontSmall);          
        }    
        if (IsDlgButtonChecked(hwndCtl2, IDC_CHECK_LABEL) == BST_CHECKED)
        {
            StartPage(pd.hDC);
            PrintLabel();
            if(EndPage(pd.hDC) < 0)
            {
                bSuccess = FALSE;
            }
        }   
    }
    else
        bSuccess = FALSE;
     
    if(bSuccess) 
        EndDoc(pd.hDC);
    else
        AbortDoc(pd.hDC);
    DeleteDC(pd.hDC);
    
}
void PSheet::InitDialog()
{
    char b[6];
    Query query = c->query();
    query << "select * from ordine_riepilogo where indice = '" << ordine << "'";                    
    Result res = query.store();
    query << "select * from pannello_controllo order by indice";                    
    Result res2 = query.store();
    Result::iterator i;
    Row row;
    for(i=res2.begin(); i!=res2.end(); i++)
    {
        row = *i;
        combo[(int)row[1]][(int)row[0]] = (string)row[2];  
        SendDlgItemMessage(hwndCtl2, IDC_COMBO_METHOD+(int)row[1], CB_INSERTSTRING, (WPARAM) (int)row[0], (LPARAM) combo[(int)row[1]][(int)row[0]].c_str());
    }    
    Row r = *(res.begin());
    SendDlgItemMessage(hwndCtl2, IDC_NUMBER, EM_LIMITTEXT, (WPARAM)3, 0);
    SendDlgItemMessage(hwndCtl2, IDC_CARRIER, EM_LIMITTEXT, (WPARAM)50, 0);
    SendDlgItemMessage(hwndCtl2, IDC_DELIVERY_DATE, EM_LIMITTEXT, (WPARAM)16, 0);
    CheckDlgButton(hwndCtl2, IDC_CHECK_FATTURA, BST_CHECKED);
    CheckDlgButton(hwndCtl2, IDC_CHECK_FATTURA_SEMPLICE, BST_UNCHECKED);
    CheckDlgButton(hwndCtl2, IDC_CHECK_LABEL, BST_UNCHECKED);
    
    if (insert)
    {
        SendDlgItemMessage(hwndCtl2, IDC_COMBO_METHOD, CB_SETCURSEL, 0, 0);
        SendDlgItemMessage(hwndCtl2, IDC_NUMBER, WM_SETTEXT, 0, (LPARAM) "0");
        SendDlgItemMessage(hwndCtl2, IDC_SPIN_NUMBER, UDM_SETRANGE, 0, (LPARAM) MAKELONG(200, 0)); 
        SendDlgItemMessage(hwndCtl2, IDC_WEIGHT, WM_SETTEXT, 0, (LPARAM) "0.000");
        SendDlgItemMessage(hwndCtl2, IDC_DELIVERY_DATE, WM_SETTEXT, 0, (LPARAM) "01/01/2005 09:00");
        vat = 0;
    }
    if ((!insert) && (quantita != 0))
    {
        SendDlgItemMessage(hwndCtl2, IDC_SPIN_NUMBER, UDM_SETRANGE, 0, (LPARAM) MAKELONG(200, 0)); 
        vat = (int)r[15];
        if ((int)r[15] == 1)
            CheckDlgButton(hwndCtl2, IDC_EURO_VAT, BST_CHECKED);
        metodo = (int)r[6];    
        SendDlgItemMessage(hwndCtl2, IDC_COMBO_METHOD, CB_SETCURSEL, (WPARAM)(int)r[6], 0);
        porto = (int)r[16];
        SendDlgItemMessage(hwndCtl2, IDC_COMBO_PORTO, CB_SETCURSEL, (WPARAM)(int)r[16], 0);
        shape = (int)r[17];
        SendDlgItemMessage(hwndCtl2, IDC_COMBO_SHAPE, CB_SETCURSEL, (WPARAM)(int)r[17], 0);    
        colli = (int)r[18];
        string anno = itoa ((int)r[18], b, 10);
        SendDlgItemMessage(hwndCtl2, IDC_NUMBER, WM_SETTEXT, 0, (LPARAM)anno.c_str());
        anno = (string)r[21];
        carrier = (string)r[21];
        SendDlgItemMessage(hwndCtl2, IDC_CARRIER, WM_SETTEXT, 0, (LPARAM)anno.c_str());
        peso = (float)r[19];
        anno = (string)r[19];
        SendDlgItemMessage(hwndCtl2, IDC_WEIGHT, WM_SETTEXT, 0, (LPARAM)anno.c_str());
        anno = (string)r[20];
        data_spedizione = (string)r[20];
        SendDlgItemMessage(hwndCtl2, IDC_DELIVERY_DATE, WM_SETTEXT, 0, (LPARAM)anno.c_str());
    }
}

void PSheet::OnDelExit()
{
    if (!insert)
    {
        Query query = c->query();
        query << "update ordine_riepilogo set colli = '" << colli << "'," <<
            " peso = '" << peso << "', trasporto = '" << carrier << "'," <<
            " data_invio = '" << data_spedizione << "', euroiva = '" << vat << "'," <<
            " pagamento = '" << metodo << "', porto = '" << porto << "'," <<
            " aspetto = '" << shape << "' where indice = '" << ordine << "'";            
        query.execute();
    }    
}

BOOL CALLBACK PSheet::DelDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    switch(Message)
    {
        case WM_NOTIFY:
            switch(((NMHDR FAR *) lParam)->code)
            {
                case PSN_KILLACTIVE:
                    SetWindowLong(hwnd, DWL_MSGRESULT, FALSE);
                    return true;
                    break;
                case PSN_APPLY:
                    SaveInfo();
                    OnDelExit();
                    break;
            }       
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED)
            { 
                if (LOWORD(wParam) == ID_PRINT)
                {
                    if (quantita != 0)
                    {
                        SaveInfo();
                        OnOrdExit();
                        OnDelExit();
                        OnPrint();
                    }    
                    else 
                    {
                        MessageBox( NULL,
                            TEXT("You must insert an order before print it !"),
                            TEXT("ERROR"),
                            MB_OK|MB_ICONERROR);
                    }
                }
            }            
            return true;    
        case WM_INITDIALOG:
            hwndCtl2 = hwnd;
            InitDialog();
            return true;
        default:
            return false;
    }
    return true;
}                

void PSheet::SaveInfo()
{
    TCHAR* passwd;
    HWND hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT);   
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        spedizione = 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        spedizione = atof(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_REDUCTION);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        sconto = 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        sconto = atof(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_PRICE);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        prezzo= 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        prezzo = atof(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT2);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        spedizione_posta= 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        spedizione_posta = atof(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_IVA);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        iva= 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        iva = atof(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_NOTE);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        nota = "";
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        nota = passwd;
    }
    
    if (IsDlgButtonChecked(hwndCtl, IDC_CHECK_SENT) == BST_CHECKED)
        spedito = true;
    else
        spedito = false;
    
    if (IsDlgButtonChecked(hwndCtl, IDC_CHECK_PAID) == BST_CHECKED)
        pagato = true;
    else
        pagato = false;
       
    hEdit = GetDlgItem(hwndCtl2, IDC_NUMBER);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        colli = 0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        colli = atoi(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl2, IDC_WEIGHT);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        peso = 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        peso = atof(passwd);
    }
        
    hEdit = GetDlgItem(hwndCtl2, IDC_CARRIER);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        carrier = "";
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        carrier = passwd;
    }
    
    hEdit = GetDlgItem(hwndCtl2, IDC_DELIVERY_DATE);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        data_spedizione = "";
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        data_spedizione = passwd;
    }
    
    if (IsDlgButtonChecked(hwndCtl2, IDC_EURO_VAT) == BST_CHECKED)
        vat = true;
    else
        vat = false;
    
    hEdit = GetDlgItem(hwndCtl2, IDC_COMBO_METHOD); 
    metodo = SendMessage(hEdit, CB_GETCURSEL, 0, 0);
    hEdit = GetDlgItem(hwndCtl2, IDC_COMBO_PORTO); 
    porto = SendMessage(hEdit, CB_GETCURSEL, 0, 0); 
    hEdit = GetDlgItem(hwndCtl2, IDC_COMBO_SHAPE); 
    shape = SendMessage(hEdit, CB_GETCURSEL, 0, 0);
    
    for(int i=0; i<2; i++)
    {
        hEdit = GetDlgItem(hwndCtl, 1459+i);
        if (SendMessage(hEdit, BM_GETCHECK, 0, 0) == BST_CHECKED)
            indirizzo = i;
    }
}

BOOL CALLBACK VcDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                    break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;
            }
            break;
        case WM_INITDIALOG:
            vc->hwndCtl = hwnd;
            vc->FillEdit();
            return true;
        default:
            return false;
    }
    return true;
}                

HFONT MyFont(PRINTDLG pd, int i)
{
    LOGFONT logfont;
    logfont.lfEscapement = 0; 
    logfont.lfOrientation = 0; 
    logfont.lfItalic = false; 
    logfont.lfUnderline = false; 
    logfont.lfStrikeOut = false;        
    logfont.lfCharSet = DEFAULT_CHARSET; 
    logfont.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE; 
            
    switch(i)
    {
        case 1:
            logfont.lfHeight = -MulDiv(9, GetDeviceCaps(pd.hDC, LOGPIXELSX), 72); 
            logfont.lfWidth = -MulDiv(5, GetDeviceCaps(pd.hDC, LOGPIXELSY), 72); 
            logfont.lfWeight = FW_ULTRALIGHT; 
            lstrcpy(logfont.lfFaceName, "Verdana");
            break;
        case 2:
            logfont.lfHeight = -MulDiv(9, GetDeviceCaps(pd.hDC, LOGPIXELSX), 72); 
            logfont.lfWidth = -MulDiv(5, GetDeviceCaps(pd.hDC, LOGPIXELSY), 72); 
            logfont.lfWeight = FW_BOLD; 
            lstrcpy(logfont.lfFaceName, "Verdana");
            break;
        case 3:
            logfont.lfHeight = -MulDiv(8, GetDeviceCaps(pd.hDC, LOGPIXELSX), 72); 
            logfont.lfWidth = -MulDiv(4, GetDeviceCaps(pd.hDC, LOGPIXELSY), 72); 
            logfont.lfWeight = FW_ULTRALIGHT; 
            lstrcpy(logfont.lfFaceName, "Verdana");
        break;
        case 4:
            logfont.lfHeight = -MulDiv(8, GetDeviceCaps(pd.hDC, LOGPIXELSX), 72); 
            logfont.lfWidth = -MulDiv(4, GetDeviceCaps(pd.hDC, LOGPIXELSY), 72); 
            logfont.lfWeight = FW_BOLD; 
            lstrcpy(logfont.lfFaceName, "Verdana");
        break;
        case 5:
            logfont.lfHeight = -MulDiv(6, GetDeviceCaps(pd.hDC, LOGPIXELSX), 72); 
            logfont.lfWidth = -MulDiv(3, GetDeviceCaps(pd.hDC, LOGPIXELSY), 72); 
            logfont.lfWeight = FW_DEMIBOLD; 
            lstrcpy(logfont.lfFaceName, "Lucida Console");
            break;
        case 6:
            logfont.lfHeight = -MulDiv(16, GetDeviceCaps(pd.hDC, LOGPIXELSX), 72); 
            logfont.lfWidth = -MulDiv(8, GetDeviceCaps(pd.hDC, LOGPIXELSY), 72); 
            logfont.lfWeight = FW_BOLD; 
            lstrcpy(logfont.lfFaceName, "Verdana");
        break;
        
    }
    return CreateFontIndirect(&logfont);             
}

void PSheet::PrintAddress()
{
    Query query = c->query();
    query << "select * from clienti where indice = '" << cliente << "'";
    Result res = query.store();
    Row r = *(res.begin());
    char b[5];
    SelectObject(pd.hDC, hfontStd1);
    TextOut(pd.hDC, 62*wChar, yChar * 10 + iLine, "Gent.:", 6);
    string s = (string)r[1] + " " + (string)r[2];
    SelectObject(pd.hDC, hfontBold1);
    TextOut(pd.hDC, 70*wChar, yChar * 10 + iLine, s.c_str(), s.length());
    SelectObject(pd.hDC, hfontStd1);
    if (indirizzo == 0)
    {
        s = (string)r[3];        
        TextOut(pd.hDC, 70*wChar, yChar * 11 + iLine, s.c_str(), s.length());
        s = (string)r[6] + " " + (string)r[4] + " " + (string)r[5];
        TextOut(pd.hDC, 70*wChar, yChar * 12 + iLine, s.c_str(), s.length());
        s = (string)r[7];
        TextOut(pd.hDC, 70*wChar, yChar * 13 + iLine, s.c_str(), s.length());
        if ((string)r[18] != "")
        {
            TextOut(pd.hDC, 62*wChar, yChar * 14 + iLine, "P. IVA:", 7); 
            s = (string)r[18];
            TextOut(pd.hDC, 70*wChar, yChar * 14 + iLine, s.c_str(), s.length());
        }
    }
    else 
    {
        //TextOut(pd.hDC, 70*wChar, yChar * 11 + iLine, "Presso ", 7);
        SelectObject(pd.hDC, hfontStd1);
        s = (string)r[8];        
        TextOut(pd.hDC, 70*wChar, yChar * 11 + iLine, s.c_str(), s.length());
        s = (string)r[9];        
        TextOut(pd.hDC, 70*wChar, yChar * 12 + iLine, s.c_str(), s.length());
        s = (string)r[12] + " " + (string)r[10] + " " + (string)r[11];
        TextOut(pd.hDC, 70*wChar, yChar * 13 + iLine, s.c_str(), s.length());
        s = (string)r[13];
        TextOut(pd.hDC, 70*wChar, yChar * 14 + iLine, s.c_str(), s.length());
        if ((string)r[18] != "")
        {
            TextOut(pd.hDC, 62*wChar, yChar * 15 + iLine, "P. IVA:", 7); 
            s = (string)r[18];
            TextOut(pd.hDC, 70*wChar, yChar * 15 + iLine, s.c_str(), s.length());
        }
    }
        
    string t = itoa(numero_fattura, b, 10);
    s = "fattura #               data ";             
    SelectObject(pd.hDC, hfontBold1);
    TextOut(pd.hDC, 10*wChar, yChar * 18 + iLine, s.c_str(), s.length());
    SelectObject(pd.hDC, hfontStd1);
    TextOut(pd.hDC, 23*wChar, yChar * 18 + iLine, t.c_str(), t.length());
    
    int pos[2];
    int j = 0;
    for(int i=0; i<data.length(); i++)
    {
        if (data.substr(i,1) == "-")
        {
            pos[j] = i;
            j++;
        }
    }  
    s = data.substr(pos[1]+1, data.length() - pos[1] -1) + "/" 
        + data.substr(5, pos[1] - 5) + "/" +  data.substr(0,4);
    
    TextOut(pd.hDC, 37*wChar, yChar * 18 + iLine, s.c_str(), s.length());
}

void PSheet::PrintInitTable()
{
    BITMAP bm;
    HBITMAP hBmpLinea = (HBITMAP)LoadImage(GetModuleHandle(NULL), "linea.bmp",
                        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
    HDC hMemDC = CreateCompatibleDC(pd.hDC);                        
    SelectObject(hMemDC, hBmpLinea);       
    GetObject(hBmpLinea, sizeof(bm), &bm); 
    
    float fScaleX = (float) GetDeviceCaps(pd.hDC, LOGPIXELSX)/72;
    float fScaleY = (float) GetDeviceCaps(pd.hDC, LOGPIXELSY)/72;
    StretchBlt(pd.hDC, 5*wChar, yChar * 19 + iLine, 
               (int) (bm.bmWidth * fScaleX), (int) (bm.bmHeight * fScaleY), 
                hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    StretchBlt(pd.hDC, 5*wChar, yChar * 52 + iLine, 
                (int) (bm.bmWidth * fScaleX), (int) (bm.bmHeight * fScaleY), 
                hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);                
 
    SelectObject(pd.hDC, hfontSmall);
    SIZE size;
    string s = "cod. nr.";
    GetTextExtentPoint32(pd.hDC, s.c_str(), s.length(), &size); 
    TextOut(pd.hDC, 19*wChar - size.cx, yChar * 20 + iLine, s.c_str(), s.length());
    s = "qtà";
    GetTextExtentPoint32(pd.hDC, s.c_str(), s.length(), &size); 
    TextOut(pd.hDC, 23*wChar - size.cx, yChar * 20 + iLine, s.c_str(), s.length());
    s = "artista - titolo - formato";
    TextOut(pd.hDC, 25*wChar, yChar * 20 + iLine, s.c_str(), s.length());
    s = "prezzo unità";
    GetTextExtentPoint32(pd.hDC, s.c_str(), s.length(), &size); 
    TextOut(pd.hDC, 95*wChar - size.cx, yChar * 20 + iLine, s.c_str(), s.length());    
    s = "importo euro";
    GetTextExtentPoint32(pd.hDC, s.c_str(), s.length(), &size); 
    TextOut(pd.hDC, 108*wChar - size.cx, yChar * 20 + iLine, s.c_str(), s.length());
}

void PSheet::PrintEndTable(bool h)
{   
    int uplimit;
    if (h)
        uplimit = 4;
    else
        uplimit = 2;
        
    int decimal, segno;
    SIZE size;
    string s;
    string u[4];
    char b[6];
    
    HBITMAP hBmpLineaCorta = (HBITMAP)LoadImage(GetModuleHandle(NULL), "linea.bmp",
                        IMAGE_BITMAP, 108, 3, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
                        
    float fScaleX = (float) GetDeviceCaps(pd.hDC, LOGPIXELSX)/72;
    float fScaleY = (float) GetDeviceCaps(pd.hDC, LOGPIXELSY)/72;                                
    HDC hMemDC = CreateCompatibleDC(pd.hDC);                        
    SelectObject(hMemDC, hBmpLineaCorta);       
                    
    TextOut(pd.hDC, 5*wChar, yChar * 53 +  iLine, "totale pezzi", 12);
    SelectObject(pd.hDC, hfontBold2);
    string t = itoa(quantita, b, 10);
    GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
    TextOut(pd.hDC, 23*wChar - size.cx, yChar * 53 +  iLine, t.c_str(), t.length());
    
    if (h) 
    {
        u[0] = "totale imponibile";
        u[1] = "iva - vat 20%";
        u[2] = "spese postali esenti IVA art. 15";
        u[3] = "totale fattura";
    }
    else 
    {
        u[0] = "spese postali esenti IVA art. 15";
        u[1] = "totale fattura";
    }            
    
    for(int k=0; k < uplimit; k++)
    {          
        SelectObject(pd.hDC, hfontBold2);
        GetTextExtentPoint32(pd.hDC, u[k].c_str(), u[k].length(), &size); 
        TextOut(pd.hDC, 95*wChar - size.cx, yChar * (53+k)  +  iLine, u[k].c_str(), u[k].length());
        TextOut(pd.hDC, 97*wChar, yChar * (53+k)  +  iLine, "€", 1);
        float numero;
        switch(k)
        {
            case 0:
                if (h)
                {
                    SelectObject(pd.hDC, hfontStd2);
                    numero = totale_imponibile;
                    totale_finale += numero;
                }    
                else 
                {
                    SelectObject(pd.hDC, hfontStd2);
                    numero = spedizione;
                }
                break;
            case 1:
                if (h)
                {
                    SelectObject(pd.hDC, hfontStd2);
                    if (!vat)
                        numero = iva;
                    else 
                        numero = 0.0;    
                    totale_finale += numero;    
                }
                else
                {
                    SelectObject(pd.hDC, hfontBold2);
                    if (!vat)
                        numero = prezzo;    
                    else
                        numero = prezzo - iva;    
                }             
                break;
            case 2:
                SelectObject(pd.hDC, hfontStd2);
                numero = spedizione_posta;
                totale_finale += numero;
                break;
            case 3:
                numero = totale_finale;
                break;
        }
        s = _ecvt(numero, 6, &decimal, &segno);
        s.insert(decimal, ".");
        if (numero == 0)
        {
            s.insert(0, "0");
            t = s.substr(0, decimal+4);
        }    
        else
            t = s.substr(0, decimal+3);    
        GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
        TextOut(pd.hDC, 108*wChar - size.cx, yChar * (53+k)  +  iLine, t.c_str(), t.length());        
        StretchBlt(pd.hDC, 99*wChar, yChar * (54+k) - 23 + iLine, 
           (int) (108.0 * fScaleX), (int) (3.0 * fScaleY), 
            hMemDC, 0, 0, 108, 3, SRCCOPY);
    }    
    
    if (h)
    {    
        SelectObject(pd.hDC, hfontBold1);
        s = "PAGAMENTO: " + combo[0][metodo];
        TextOut(pd.hDC, 5*wChar, yChar * 56  +  iLine, s.c_str(), s.length());        
        SelectObject(pd.hDC, hfontStd2);
        s = "Causale del trasporto: vendita";
        TextOut(pd.hDC, 5*wChar, yChar * 57  +  iLine, s.c_str(), s.length());        
        s = "Porto: " + combo[1][porto];
        TextOut(pd.hDC, 5*wChar, yChar * 58  +  iLine, s.c_str(), s.length());        
        s = "Aspetto esteriore dei beni: " + combo[2][shape];
        TextOut(pd.hDC, 5*wChar, yChar * 59  +  iLine, s.c_str(), s.length());        
        t = itoa(colli, b, 10);
        s = "Numero colli: " + t;
        TextOut(pd.hDC, 5*wChar, yChar * 60  +  iLine, s.c_str(), s.length());        
        s = "contributo CONAI ASSOLTO";
        GetTextExtentPoint32(pd.hDC, s.c_str(), s.length(), &size); 
        TextOut(pd.hDC, 108*wChar - size.cx, yChar * 60  +  iLine, s.c_str(), s.length());        
        s = _ecvt(peso, 6, &decimal, &segno);
        s.insert(decimal, ".");
        if (peso < 1.000)
            t = "Peso: Kg  0" + s.substr(0, decimal+4);
        else    
            t = "Peso: Kg  " + s.substr(0, decimal+4);
        TextOut(pd.hDC, 5*wChar, yChar * 61  +  iLine, t.c_str(), t.length());        
        s = "Trasporto a mezzo: " + carrier;
        TextOut(pd.hDC, 5*wChar, yChar * 62  +  iLine, s.c_str(), s.length());        
        s = "Data e ora di partenza: " + data_spedizione;
        TextOut(pd.hDC, 5*wChar, yChar * 63  +  iLine, s.c_str(), s.length());        
    }
}

void PSheet::PrintTable(bool h)
{
    char b[6];
    Query query = c->query();
    query << "select * from ordini where indice_ordine ='" << ordine << "' order by indice_CD";
    Result result3 = query.store();    
    Result::iterator pippo;
       
    int decimal, segno;
    string s, t;
    SIZE size;    
    float prezzo_temp;
    totale_imponibile = 0.0;
    sconto_finale = 0.0;
    totale_finale = 0.0;
    
    vector<Row>::iterator itRow = edit.begin();    
    
    SelectObject(pd.hDC, hfontStd2);    
    for(int i=0; i<cd_collo.size(); i++)
    {
        if (((i % 28) == 0) && (i != 0))
        {   
            EndPage(pd.hDC);
            StartPage(pd.hDC);
            PrintHeader();
            PrintInitTable();
            SelectObject(pd.hDC, hfontStd2);    
        }
        
        Row r1 = *(edit.begin()+i);
        s = (string)r1[6];

        GetTextExtentPoint32(pd.hDC, s.c_str(), s.length(), &size); 
        TextOut(pd.hDC, 19*wChar - size.cx, yChar * (21+(i%28)) + iLine, s.c_str(), s.length());
        t = itoa(cd_collo[i], b, 10);
        GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
        TextOut(pd.hDC, 23*wChar - size.cx, yChar * (21+(i%28)) +  iLine, t.c_str(), t.length());
        string s1 = (string)r1[1] ;
        string s2 = (string)r1[2] ;
        string s3 = (string)r1[4] ;
        int lunghezza = (s1.length() + s2.length() + s3.length() + 5);
        if (lunghezza > 70)
        {
            s1 = s1.substr(0, (s1.length()/lunghezza*70));
            s2 = s2.substr(0, (s2.length()/lunghezza*70));
            s3 = s3.substr(0, (s3.length()/lunghezza*70));
        }
        s = s1 + " . " + s2 + "  " + s3;                
        TextOut(pd.hDC, 25*wChar, yChar * (21+(i%28)) +  iLine, s.c_str(), s.length());
        row_temp = *(result3.begin()+i);
        prezzo_temp = (float)row_temp[4];

        if ((h) || ((!h) && (vat != 0)))
        {
            prezzo_temp = prezzo_temp / 1.2;
            prezzo_temp = Rounded(prezzo_temp);
            totale_imponibile += prezzo_temp*(float)cd_collo[i];
        }    
        s = _ecvt(prezzo_temp, 6, &decimal, &segno);
        s.insert(decimal, ".");
        if (prezzo_temp == 0)
        {
            s.insert(0, "0");
            t = s.substr(0, decimal+4);
        }    
        else
            t = s.substr(0, decimal+3);    
            
        GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
        TextOut(pd.hDC, 95*wChar - size.cx, yChar * (21+(i%28)) +  iLine, t.c_str(), t.length());
        s = _ecvt(prezzo_temp*(float)cd_collo[i], 6, &decimal, &segno);
        s.insert(decimal, ".");
        if (prezzo_temp*(float)cd_collo[i] == 0)
        {
            s.insert(0, "0");
            t = s.substr(0, decimal+4);
        }    
        else
            t = s.substr(0, decimal+3);    
        
        GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
        TextOut(pd.hDC, 108*wChar - size.cx, yChar * (21+(i%28)) +  iLine, t.c_str(), t.length());
    }        
    
    s = "SCSP";
    GetTextExtentPoint32(pd.hDC, s.c_str(), s.length(), &size); 
    TextOut(pd.hDC, 19*wChar - size.cx, yChar * 51 + iLine, s.c_str(), s.length());
    t = itoa(1, b, 10);
    GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
    TextOut(pd.hDC, 23*wChar - size.cx, yChar * 51 +  iLine, t.c_str(), t.length());
    s = "SCONTO";
    TextOut(pd.hDC, 25*wChar, yChar * 51 +  iLine, s.c_str(), s.length());
    if (h)
    {
        sconto_finale = -Rounded((spedizione_posta - spedizione + sconto)/1.2);
        totale_imponibile += sconto_finale;
    }
    else if ((h) || ((!h) && (vat != 0)))
    {
        sconto_finale = -sconto/1.2;
    }
    else 
        sconto_finale = -sconto;
        
    s = _ecvt(sconto_finale, 6, &decimal, &segno);
    s.insert(decimal, ".");
    if (fabs(sconto_finale) < 1.)
    {
        s.insert(0, "0");
        t = s.substr(0, decimal+4);
    }    
    else
        t = s.substr(0, decimal+3);    
    
    if (segno == 1)
        t = "-" + t;
            
    GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
    TextOut(pd.hDC, 95*wChar - size.cx, yChar * 51 +  iLine, t.c_str(), t.length());
    GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
    TextOut(pd.hDC, 108*wChar - size.cx, yChar * 51 +  iLine, t.c_str(), t.length()); 
    
}

void PSheet::PrintHeader()
{
    BITMAP bm;
    
    HBITMAP hBmpHeader = (HBITMAP)LoadImage(GetModuleHandle(NULL), "header.bmp",
                        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
    HBITMAP hBmpFooter = (HBITMAP)LoadImage(GetModuleHandle(NULL), "footer.bmp",
                        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE); 
    HBITMAP hBmpLogo = (HBITMAP)LoadImage(GetModuleHandle(NULL), "logo.bmp",
                        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
    float fScaleX = (float) GetDeviceCaps(pd.hDC, LOGPIXELSX)/72/4.75;
    float fScaleY = (float) GetDeviceCaps(pd.hDC, LOGPIXELSY)/72/4.75;                                
    HDC hMemDC = CreateCompatibleDC(pd.hDC);                        
    
    SelectObject(hMemDC, hBmpHeader);       
    GetObject(hBmpHeader, sizeof(bm), &bm);
    StretchBlt(pd.hDC, 5*wChar, yChar * 3, 
           (int) (bm.bmWidth * fScaleX), (int) (bm.bmHeight * fScaleY), 
            hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);            
            
    SelectObject(hMemDC, hBmpLogo);       
    GetObject(hBmpLogo, sizeof(bm), &bm);
    StretchBlt(pd.hDC, 108*wChar-(int) (bm.bmWidth * fScaleX), yChar * 3, 
           (int) (bm.bmWidth * fScaleX), (int) (bm.bmHeight * fScaleY), 
            hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);            
            
    SelectObject(hMemDC, hBmpFooter);       
    GetObject(hBmpFooter, sizeof(bm), &bm);
    StretchBlt(pd.hDC, 5*wChar + (int)(103*wChar - (int)(bm.bmWidth * fScaleX))/2, yChar * 67 + iLine, 
           (int) (bm.bmWidth * fScaleX), (int) (bm.bmHeight * fScaleY), 
            hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);            
}

void PSheet::PrintLabel()
{
    BITMAP bm;
    HFONT hfontBold3 = MyFont(pd, 6);
    HFONT hfontStd1 = MyFont(pd, 1);
    Query query = c->query();
    query << "select * from clienti where indice = '" << cliente << "'";
    Result res = query.store();
    Row r = *(res.begin());
    char b[5];
    SelectObject(pd.hDC, hfontBold3);
    string s = (string)r[1] + " " + (string)r[2];
    TextOut(pd.hDC, 5*wChar, yChar * 1, s.c_str(), s.length());
    if (indirizzo == 0)
    {
        s = (string)r[3];        
        TextOut(pd.hDC, 5*wChar, yChar * 3, s.c_str(), s.length());
        s = (string)r[6] + " " + (string)r[4] + " " + (string)r[5];
        TextOut(pd.hDC, 5*wChar, yChar * 5, s.c_str(), s.length());
        s = (string)r[7];
        TextOut(pd.hDC, 5*wChar, yChar * 7, s.c_str(), s.length());
    }
    else 
    {
        s = (string)r[8];        
        TextOut(pd.hDC, 5*wChar, yChar * 3, s.c_str(), s.length());
        s = (string)r[11] + " " + (string)r[9] + " " + (string)r[10];
        TextOut(pd.hDC, 5*wChar, yChar * 5, s.c_str(), s.length());
        s = (string)r[12];
        TextOut(pd.hDC, 5*wChar, yChar * 7, s.c_str(), s.length());
    }
    HBITMAP hBmpLogo = (HBITMAP)LoadImage(GetModuleHandle(NULL), "logo.bmp",
                        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE);
    float fScaleX = (float) GetDeviceCaps(pd.hDC, LOGPIXELSX)/72/4.75;
    float fScaleY = (float) GetDeviceCaps(pd.hDC, LOGPIXELSY)/72/4.75;                                
    HDC hMemDC = CreateCompatibleDC(pd.hDC);                        
    
    SelectObject(hMemDC, hBmpLogo);       
    GetObject(hBmpLogo, sizeof(bm), &bm);
    StretchBlt(pd.hDC, 5*wChar, yChar * 11 - 45, 
           (int) (bm.bmWidth * fScaleX), (int) (bm.bmHeight * fScaleY), 
            hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);            
    
    SelectObject(pd.hDC, hfontStd1);
    TextOut(pd.hDC, 5*wChar, yChar * 12, "Loc. Lupompesi",14);
    TextOut(pd.hDC, 5*wChar, yChar * 13, "I - 53016 - MURLO (SI)",22);
}
