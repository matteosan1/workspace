#define _WIN32_IE 0x501 

#include <windows.h>
#include "commctrl.h"
#include "mysql++.h"
#include "Password.h"
#include "SearchCD.h"
#include "SearchClient.h"
#include "ViewCD.h"
#include "ViewClient.h"
#include "Report.h"
#include "PSheet.h"
#include "CPanel.h"

#include <string>
#include "resource.h"

using namespace mysqlpp;
using namespace std;

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK InventoryDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK ReportDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK PasswordProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK SearchProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK SearchClientProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK InsertProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK InsertClientProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK InsertOrderProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK DeliveryProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK ControlPanelProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

class CppCntrl
{
private:
	TCHAR        chClassName[100];                //string to contain wnd class name
	TCHAR        chCaption[256];                  //string to contain wnd caption

protected:
public:
	CppCntrl();
	virtual ~CppCntrl();
	virtual HWND Create(HWND hParent=NULL);	//wnd creation, parent defaults to NULL
	TCHAR* GetWndCaption();		
    TCHAR* GetWndClassName();	
    virtual void SetInstance(HINSTANCE hInstance);//stores application instance
    virtual void SetWndCaption(TCHAR* chCap);     //stores user choice of wnd caption
    virtual void SetWndClassName(TCHAR* chClass); //stores user choice of wnd class

	HWND	hCntrl;		//handle of the control
	int nID;
	int nExStyle;
	int          nStyle;                          //wnd style
	int          Left,Top,Width,Height;           //wnd dimensions
	HINSTANCE    hInst;                           //the application instance
};

class DB
{
    public:
        DB();	        //constructor
        virtual ~DB();	//destructor
        virtual HWND Create(HWND hParent=NULL);       //wnd creation, parent defaults to NULL
        virtual LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
       	TCHAR* GetWndCaption();		
    	TCHAR* GetWndClassName();	
        virtual void SetInstance(HINSTANCE hInstance);//stores application instance
    	virtual void SetWndCaption(TCHAR* chCap);     //stores user choice of wnd caption
        virtual void SetWndClassName(TCHAR* chClass); //stores user choice of wnd class
        void Searcher(HWND hwnd, int i);
        void FillListBox();
        void Select(HWND hwnd);
        void Remove(HWND hwnd);
        void Update(HWND hwnd, Row row);
        void Insert(HWND hwnd, int i);
        void InsertInOrder(HWND hwnd);
        void Inventary(HWND hwnd, int i);
        void ControlPanel(HWND hwnd);
         
        int Left,Top,Width,Height;           //wnd dimensions  
        int nExStyle;                        //wnd extended style
        int nID;                             //control identifier or menu handle
        int nStyle;                          //wnd style
        HWND hAppWnd;                        //the main application window handle
        
        Password* pwd;
        Search* searchCD;
        SearchClient* searchClient;
        ViewCD* viewCD;
        ViewClient* viewClient;
        Report* report;
        PSheet* pSheet;
        CPanel* cPanel;
        int stato;
        float totale;
        
        Connection* connection;
        Result* result;
        string old_query;
        
   	protected:
		HINSTANCE hInst;                           //the application instance
        virtual BOOL OnCommand(HWND hwndCtl,int nID,UINT uNotifyCode);	//WM_COMMAND handler
        virtual int  OnCreate(CREATESTRUCT *cs);         //WM_CREATE handler
        virtual BOOL OnDestroy();                        //WM_DESTROY handler
        virtual BOOL OnPassword(HWND hwnd);
        virtual BOOL OnRightMouse(HWND hwnd);
        virtual BOOL OnNotify(HWND hwnd, WPARAM wParam, LPARAM lParam);

    private:
    	int nClassStyle;                    //style passed to RegisterClassEx
   		TCHAR chClassName[100];                //string to contain wnd class name
    	TCHAR chCaption[256];                  //string to contain wnd caption
	    HMENU popup;
    	CppCntrl listview;
};
