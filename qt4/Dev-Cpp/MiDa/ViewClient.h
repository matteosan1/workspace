#ifndef VIEWCLIENT
#define VIEWCLIENT
#include <windows.h>

#include "mysql++.h"
#include <string>

using namespace mysqlpp;
using namespace std;

class ViewClient
{
    public:
        ViewClient();
        ViewClient(Row row);
        virtual ~ViewClient();
        string* GetEdit() { return edit; };
        void GetInfo();
        void FillEdit();
        BOOL CALLBACK DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        HWND hwndCtl;
                    
    private:
        string edit[18];
        bool insert;
}; 
#endif
