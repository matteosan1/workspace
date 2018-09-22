#include <windows.h>
#include "commctrl.h"
#include "mysql++.h"
#include <string>

using namespace mysqlpp;
using namespace std;

class Delivery
{
    public:
        void OnExit();
        BOOL OnPrint();
        void InitDialog();
        HWND hwndCtl;
                    
    private:
        Connection* connection;
        bool insert;
        int ordine;
        int vat;
        int metodo;
        int porto;
        int shape;
        int colli;
        float peso;
        string carrier;
        string data;
}; 
