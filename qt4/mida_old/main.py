# -*- coding: utf-8 -*-

BOOL CALLBACK InventoryDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    string anno, mese, giorno, s;
    HWND hCombo;
    string mesi[12] = {"January ", "February ", "March ", "April ", "May ", "June ", 
                "July ", "August ", "September ", "October ", "November ", "December "};
    char b[4];
    SYSTEMTIME time;
    int decimal,segno;
    switch(Message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                    break;
            }
            break;
        case WM_INITDIALOG:
            GetLocalTime(&time);
            anno = itoa (time.wYear, b, 10);
            mese = itoa (time.wMonth, b, 10);
            giorno = itoa (time.wDay, b, 10);
            mese = _ecvt(dataBase.totale, 6, &decimal, &segno);
            mese.insert(decimal, ".");
            s = "Stock on " + mesi[time.wMonth - 1] + giorno + ", " + anno 
                + ": " + mese.substr(0, decimal+3) + " ";    
            hCombo = GetDlgItem(hwnd, IDC_DATE); 
            SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
            break;
        default:
            return false;
    }
    return true;
}

