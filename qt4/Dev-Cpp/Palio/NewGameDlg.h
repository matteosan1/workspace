#include <windows.h>
#include "resource.h"

#include <string>

using namespace std;

class NewGameDlg
{
    public:
        NewGameDlg();
        virtual ~NewGameDlg();
        void SetControl();
        BOOL GetControl();
        void InsertList();
        void RemoveList();
        BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
        int GetAnno() { return anno; }
        int GetGiocatori() { return giocatori; }
        string GetNome(int i) { return nome[i]; }
        HWND hwndCtl;
    
    private:
        string nome[17];
        int anno;
        int giocatori;
};
