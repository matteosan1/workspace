#include "Delivery.h"
#include "resource.h"
/*
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

BOOL Delivery::OnPrint()
{
    if (insert)
        OnExit();
    bool stampa = false;
    
    if (stampa)
    {  
        PRINTDLG pd;
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
        TEXTMETRIC tm;
        HFONT hfont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
        int yChar, wChar;
    
        SetMapMode(pd.hDC, MM_TEXT);
        SelectObject(pd.hDC, hfont);
        GetTextMetrics(pd.hDC, &tm);
        yChar = tm.tmHeight;
        wChar = tm.tmAveCharWidth;
    
        int iHeaderHeight = 10;
        int iLinesPerPage = iHeight / yChar;
        int iPage = 0;
        int iLine = 0;
        
        DOCINFO di;
        BOOL bSuccess = TRUE;

        char* szFileName = "Stampa fattura";

        ZeroMemory(&di, sizeof(di));
        di.cbSize = sizeof(di);
        di.lpszDocName = szFileName;        
        
        if(StartDoc(pd.hDC, &di) > 0)
        {
            HANDLE hold;
            if(StartPage(pd.hDC) < 0)
            {
                bSuccess = FALSE;
            }
            //Make all printing be offset by the amount specified for the margins
            //SetViewportOrgEx(pd.hDC, iLeftAdjust, iTopAdjust, NULL);
            
            //select the fixed-width font into the printer DC
            hold = SelectObject(pd.hDC, hfont);

            char b[5];
            Query query = c->query();
            query << "select * from clienti where indice = '" << cliente << "'";
            Result res = query.store();
            Row r = *(res.begin());
        
            TextOut(pd.hDC, 72*wChar, yChar * 11 + iHeaderHeight, "Gent.:", 6);
            string s = (string)r[1] + " " + (string)r[2];
            TextOut(pd.hDC, 80*wChar, yChar * 11 + iHeaderHeight, s.c_str(), s.length());
            if (indirizzo == 0)
            {
                s = (string)r[3];        
                TextOut(pd.hDC, 80*wChar, yChar * 12 + iHeaderHeight, s.c_str(), s.length());
                s = (string)r[6] + " " + (string)r[4] + " " + (string)r[5];
                TextOut(pd.hDC, 80*wChar, yChar * 13 + iHeaderHeight, s.c_str(), s.length());
                s = (string)r[7];
                TextOut(pd.hDC, 80*wChar, yChar * 14 + iHeaderHeight, s.c_str(), s.length());
            }
            else 
            {
                s = (string)r[8];        
                TextOut(pd.hDC, 80*wChar, yChar * 12 + iHeaderHeight, s.c_str(), s.length());
                s = (string)r[11] + " " + (string)r[9] + " " + (string)r[10];
                TextOut(pd.hDC, 80*wChar, yChar * 13 + iHeaderHeight, s.c_str(), s.length());
                s = (string)r[12];
                TextOut(pd.hDC, 80*wChar, yChar * 14 + iHeaderHeight, s.c_str(), s.length());
            }
        
            string t = itoa(numero_fattura, b, 10);
            s = "fattura # " + t + "    data " + data;             
            TextOut(pd.hDC, 10*wChar, yChar * 18 + iHeaderHeight, s.c_str(), s.length());
    
            vector<Row>::iterator itRow = edit.begin();
            
            for(int i=0; i<cd_collo.size(); i++)
            {
                if ((i % 30) == 0)
                {
                    iPage++;
                    // stampa header e legenda
                    // aggiorna numero di pagina;
                }
                iLine = yChar * iLinesPerPage * iPage + iHeaderHeight;
                Row r1 = *(itRow+i);
                s = (string)r1[6];
                SIZE size;
                GetTextExtentPoint32(pd.hDC, s.c_str(), s.length(), &size); 
                TextOut(pd.hDC, 14*wChar - size.cx, yChar * (20+i) + iLine, s.c_str(), s.length());
                string t = itoa(cd_collo[i], b, 10);
                TextOut(pd.hDC, 16*wChar, yChar * (20+i) +  iLine, t.c_str(), t.length());
                s = (string)r1[1] + "." + (string)r1[2] + " " + (string)r1[4];
                if (s.length() > 70)
                    t = s.substr(0, 70);
                else 
                    t = s;    
                TextOut(pd.hDC, 18*wChar, yChar * (20+i) +  iLine, t.c_str(), t.length());
                float prezzo;
                int decimal, segno;
                if ((int)r1[10] != 2)
                    prezzo = (int)r1[8];
                else
                    prezzo = (int)r1[9];    
                s = _ecvt(prezzo, 6, &decimal, &segno);
                s.insert(decimal, ".");
                t = s.substr(0, decimal+3);
                GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
                TextOut(pd.hDC, 100*wChar - size.cx, yChar * (20+i) +  iLine, t.c_str(), t.length());
                s = _ecvt(prezzo*(float)cd_collo[i], 6, &decimal, &segno);
                s.insert(decimal, ".");
                t = s.substr(0, decimal+3);
                GetTextExtentPoint32(pd.hDC, t.c_str(), t.length(), &size); 
                TextOut(pd.hDC, 110*wChar - size.cx, yChar * (20+i) +  iLine, t.c_str(), t.length());
            }        
            
            // stampare riepilogo

            SelectObject(pd.hDC, hold);
            if(EndPage(pd.hDC) < 0)
            {
                bSuccess = FALSE;
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
}
*/
Delivery::Delivery(Connection* q, bool h)
{
    connection = q;
    insert = h;
}

Delivery::~Delivery()
{}

void Delivery::InitDialog()
{
    char b[6];
    string combo[10][10];
    Query query = connection->query();
    query << "select * from ordine_riepilogo where indice = '" << Order::GetOrdine() << "'";                    
    Result res = query.store();
    query << "select * from pannello_controllo order by indice";                    
    Result res2 = query.store();
    Result::iterator i;
    Row row;
    for(i=res2.begin(); i!=res2.end(); i++)
    {
        row = *i;
        combo[(int)row[1]][(int)row[0]] = (string)row[2];  
        SendDlgItemMessage(hwndCtl, IDC_COMBO_METHOD+(int)row[1], CB_INSERTSTRING, (WPARAM) (int)row[0], (LPARAM) combo[(int)row[1]][(int)row[0]].c_str());
    }    
        
    Row r = *(res.begin());
    SendDlgItemMessage(hwndCtl, IDC_NUMBER, EM_LIMITTEXT, (WPARAM)3, 0);
    SendDlgItemMessage(hwndCtl, IDC_CARRIER, EM_LIMITTEXT, (WPARAM)50, 0);
    SendDlgItemMessage(hwndCtl, IDC_DELIVERY_DATE, EM_LIMITTEXT, (WPARAM)16, 0);
    if ((int)r[6] == 0)
    {
        SendDlgItemMessage(hwndCtl, IDC_COMBO_METHOD, CB_SETCURSEL, 0, 0);
        SendDlgItemMessage(hwndCtl, IDC_NUMBER, WM_SETTEXT, 0, (LPARAM) "0");
        SendDlgItemMessage(hwndCtl, IDC_SPIN_NUMBER, UDM_SETRANGE, 0, (LPARAM) MAKELONG(200, 0)); 
        SendDlgItemMessage(hwndCtl, IDC_WEIGHT, WM_SETTEXT, 0, (LPARAM) "0.000");
        SendDlgItemMessage(hwndCtl, IDC_DELIVERY_DATE, WM_SETTEXT, 0, (LPARAM) "01/01/2005 09:00");
    }
    else
    {
        
        if ((int)r[14] == 1)
            CheckDlgButton(hwndCtl, IDC_EURO_VAT, BST_CHECKED);
        SendDlgItemMessage(hwndCtl, IDC_COMBO_METHOD, CB_SETCURSEL, (WPARAM)(int)r[6], 0);
        SendDlgItemMessage(hwndCtl, IDC_COMBO_PORTO, CB_SETCURSEL, (WPARAM)(int)r[15], 0);
        SendDlgItemMessage(hwndCtl, IDC_COMBO_SHAPE, CB_SETCURSEL, (WPARAM)(int)r[16], 0);    
        string anno = itoa ((int)r[17], b, 10);
        SendDlgItemMessage(hwndCtl, IDC_NUMBER, WM_SETTEXT, 0, (LPARAM)anno.c_str());
        anno = (string)r[20];
        SendDlgItemMessage(hwndCtl, IDC_CARRIER, WM_SETTEXT, 0, (LPARAM)anno.c_str());
        anno = (string)r[18];
        SendDlgItemMessage(hwndCtl, IDC_WEIGHT, WM_SETTEXT, 0, (LPARAM)anno.c_str());
        anno = (string)r[19];
        SendDlgItemMessage(hwndCtl, IDC_DELIVERY_DATE, WM_SETTEXT, 0, (LPARAM)anno.c_str());
    }
}

void Delivery::OnExit()
{
    Query query = connection->query();
    TCHAR* passwd;
    HWND hEdit = GetDlgItem(hwndCtl, IDC_NUMBER);   
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        colli = 0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        colli = atoi(passwd);
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_WEIGHT);   
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        peso = 0.0;
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        peso = atof(passwd);
    }
        
    hEdit = GetDlgItem(hwndCtl, IDC_CARRIER);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        carrier = "";
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        carrier = passwd;
    }
    
    hEdit = GetDlgItem(hwndCtl, IDC_DELIVERY_DATE);
    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen == 0)
        data = "";
    else
    {         
        passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        data = passwd;
    }
    
    if (IsDlgButtonChecked(hwndCtl, IDC_EURO_VAT) == BST_CHECKED)
        vat = true;
    else
        vat = false;
    
    hEdit = GetDlgItem(hwndCtl, IDC_COMBO_METHOD); 
    metodo = SendMessage(hEdit, CB_GETCURSEL, 0, 0);
    hEdit = GetDlgItem(hwndCtl, IDC_COMBO_PORTO); 
    porto = SendMessage(hEdit, CB_GETCURSEL, 0, 0); 
    hEdit = GetDlgItem(hwndCtl, IDC_COMBO_SHAPE); 
    shape = SendMessage(hEdit, CB_GETCURSEL, 0, 0);
    
    query << "update ordine_riepilogo set colli = '" << colli << "'," <<
        " peso = '" << peso << "', trasporto = '" << carrier << "'," <<
        " data_invio = '" << data << "', euroiva = '" << vat << "'," <<
        " pagamento = '" << metodo << "', porto = '" << porto << "'," <<
        " aspetto = '" << shape << "' where indice = '" << ordine << "'";            
    query.execute();
}

BOOL CALLBACK Delivery::DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
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
                break;
            }       
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                
            }
            break;
            if (HIWORD(wParam) == BN_CLICKED)
            { 
                if (LOWORD(wParam) == ID_PRINT)
                {
                    OnPrint();
                }
            }            
            return true;    
        case WM_INITDIALOG:
            hwndCtl = hwnd;
            InitDialog();
            return true;
        default:
            return false;
    }
    return true;
}                
