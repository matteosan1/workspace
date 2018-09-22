#include <windows.h>

class Search
{
    public:
        Search();
        virtual ~Search();
        TCHAR* GetArtist() { return artist; }
        TCHAR* GetCompany() { return company; }
        TCHAR* GetSupplier() { return supplier; }
        TCHAR* GetQuantity() { return quantity; }
        TCHAR* GetCode() { return code; }
        void SetEditCtrl();
        BOOL CALLBACK DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        HWND hwndCtl;
                    
    private:
        TCHAR* artist;
        TCHAR* company;
        TCHAR* supplier;
        TCHAR* quantity;
        TCHAR* code;
}; 

