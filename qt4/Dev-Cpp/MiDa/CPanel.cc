#include "CPanel.h"
#include "resource.h"

CPanel::CPanel(Connection* q)
{
    connection = q;
}

CPanel::~CPanel()
{}

BOOL CALLBACK CPanel::DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HWND hBtn1;
    switch (Message)
    {
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED)
            {
                if (LOWORD(wParam) == IDOK)
                    EndDialog(hwnd, IDOK);    
                if (LOWORD(wParam) == IDCANCEL)
                    EndDialog(hwnd, IDCANCEL);                    
                if (LOWORD(wParam) == ID_BUTTON_METHOD)
                    InsertList(0);
                if (LOWORD(wParam) == ID_BUTTON_PORTO)
                    InsertList(1);
                if (LOWORD(wParam) == ID_BUTTON_SHAPE)
                    InsertList(2);    
            }
            return true;
        case WM_INITDIALOG:
            hwndCtl = hwnd;
            InitList();
            return true;
        default:
            return false;
	}
} 

void CPanel::InsertList(int s)
{
    int indice;        
    HWND hEdit = GetDlgItem(hwndCtl, IDC_EDIT_METHOD + s);   
    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
    if (nLen != 0)
    {         
        TCHAR* passwd = new TCHAR[nLen+1]; 
        GetWindowText(hEdit, passwd, nLen+1);
        indice = SendDlgItemMessage(hwndCtl, IDC_LIST_METHOD + s , LB_ADDSTRING, 0, (LPARAM) passwd);                   
        SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) ""); 
        if (indice != LB_ERR)
        {
            Query query = connection->query();
            query << "insert into pannello_controllo values('" << indice <<
                "','" << s << "','" << passwd << "')";
            query.execute();    
        }
    }   
}

void CPanel::InitList()
{
    for(int j=0; j<3; j++)
        SendDlgItemMessage(hwndCtl, IDC_LIST_METHOD + j , LB_RESETCONTENT, 0, 0);       
        
    Query query = connection->query();
    Result res;
    int x;
    query << "select * from pannello_controllo order by indice";                    
    res = query.store();
    Result::iterator i;
    for (i = res.begin(); i != res.end(); i++)
    {
        Row r = *i;
        combo = (string)r[2];     
        SendDlgItemMessage(hwndCtl, IDC_LIST_METHOD + (int)r[1] , LB_ADDSTRING, 0, (LPARAM) combo.c_str());       
    }            
} 
