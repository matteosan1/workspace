#ifndef _WIN32_IE
#define _WIN32_IE   0x0501 
#endif

#include <windows.h>
#include <commctrl.h>

#define ListView_GetCheckState(w,i) ((((UINT)(SNDMSG((w),LVM_GETITEMSTATE,(WPARAM)(i),LVIS_STATEIMAGEMASK)))>>12)-1)

#include "mysql++.h"
#include <string>

using namespace mysqlpp;
using namespace std;

class Report
{
    public:
        Report(Connection* con, int i);
        virtual ~Report();
        BOOL CALLBACK DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        void FillCombo();
        void FillList();
        void InitImage();
        void InitList();
        void OnExit();
        HWND hwndCtl;
                    
    private:
        Connection* connection;
        string data;
        int indirizzo;
        int quantita;
        float prezzo;
        float sconto;
        float spedizione;
        int cliente;
        int stato;
        string tipo_pagamento[12];
}; 

