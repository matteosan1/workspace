#include <windows.h>
#include "resource.h"

class NewGameDlg
{
    public:
        NewGameDlg();
        NewGameDlg(HWND hwnd);
        virtual ~NewGameDlg();
        friend BOOL CALLBACK NewGameDlgProc(HWND, UINT, WPARAM, LPARAM);
        int GetAnno() { return anno; }
        int GetGiocatori() { return giocatori; }
        char* GetNome() { return nome; }
    
    private:
        char* nome;
        int anno;
        int giocatori;
};
