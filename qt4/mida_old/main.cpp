#include "DB.h"

DB dataBase;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
    InitCommonControls();
    MSG messages; 
    dataBase.SetInstance(hThisInstance);
    if (dataBase.Create())
    { 
        while (GetMessage (&messages, NULL, 0, 0))
        {
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }
    }
    
    return messages.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.WndProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK AboutDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
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
        default:
            return false;
    }
    return true;
}

BOOL CALLBACK Range(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
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
        default:
            return false;
    }
    return true;
}


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
                + ": " + mese.substr(0, decimal+3) + " €";    
            hCombo = GetDlgItem(hwnd, IDC_DATE); 
            SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
            break;
        default:
            return false;
    }
    return true;
}


BOOL CALLBACK PasswordProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.pwd->DlgProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK SearchProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.searchCD->DlgProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK InsertProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.viewCD->DlgProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK InsertClientProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.viewClient->DlgProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK SearchClientProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.searchClient->DlgProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK InsertOrderProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.pSheet->OrdDlgProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK DeliveryProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.pSheet->DelDlgProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK ReportDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.report->DlgProc(hwnd,Message,wParam,lParam);
}

BOOL CALLBACK ControlPanelProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    return dataBase.cPanel->DlgProc(hwnd,Message,wParam,lParam);
}
