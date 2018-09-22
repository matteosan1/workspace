#include <windows.h>
#include "resource.h"

class ListDlg
{
    public:
        ListDlg();
        ListDlg(HWND hwnd, const char* a);
        virtual ~ListDlg();
        friend BOOL CALLBACK ListDlgProc(HWND, UINT, WPARAM, LPARAM);
};
