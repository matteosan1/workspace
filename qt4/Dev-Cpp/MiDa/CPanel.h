#include <windows.h>
#include "mysql++.h"
#include <string>

using namespace mysqlpp;
using namespace std;

class CPanel
{
    public:
        CPanel(Connection* con);
        virtual ~CPanel();
        BOOL CALLBACK DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        void InitList();
        void InsertList(int i);
        HWND hwndCtl;
                    
    private:
        Connection* connection;
        string combo;
}; 

