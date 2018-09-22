#include <windows.h>
#include "resource.h"

class NewPlayerDlg
{
    public:
        NewPlayerDlg();
        NewPlayerDlg(HWND hwnd);
        virtual ~NewPlayerDlg();
        friend BOOL CALLBACK NewPlayerDlgProc(HWND, UINT, WPARAM, LPARAM);
        char* GetNome() { return nome; }
    
    private:
        char* nome;
};
