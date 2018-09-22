#include <windows.h>

#include "mysql++.h"
#include <string>

using namespace mysqlpp;
using namespace std;

class ViewCD
{
    public:
        ViewCD();
        ViewCD(Row row1, Row row2);
        virtual ~ViewCD();
        string* GetEdit() { return edit; };
        int GetStatus() { return status; };
        void GetInfo();
        void FillEdit();
        BOOL CALLBACK DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        HWND hwndCtl;
                    
    private:
        string edit[13];
        int status;
        bool insert;
}; 

