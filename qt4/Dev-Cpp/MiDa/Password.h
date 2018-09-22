#include <windows.h>

class Password
{
    public:
        Password();
        virtual ~Password();
        TCHAR* GetPassword() { return passwd; }
        void SetPassword();
        BOOL CALLBACK DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        HWND hwndCtl;
                    
    private:
        TCHAR* passwd;
}; 

