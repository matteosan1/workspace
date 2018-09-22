#include <windows.h>

class SearchClient
{
    public:
        SearchClient();
        virtual ~SearchClient();
        TCHAR* GetSurname() { return surname; }
        TCHAR* GetCity() { return city; }
        TCHAR* GetCountry() { return country; }
        void SetEditCtrl();
        BOOL CALLBACK DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        HWND hwndCtl;
                    
    private:
        TCHAR* surname;
        TCHAR* city;
        TCHAR* country;
}; 

