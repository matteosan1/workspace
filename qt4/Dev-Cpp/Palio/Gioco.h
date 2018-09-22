#include <windows.h>
#include "NewGameDlg.h"
#include "Giocatore.h"
#include "Contrada.h"

using namespace std;

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK NewGameProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

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

class Gioco
{
    public:
        Gioco();	        //constructor
        virtual ~Gioco();	//destructor
        virtual HWND Create(HWND hParent=NULL);       //wnd creation, parent defaults to NULL
        virtual LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
       	TCHAR* GetWndCaption();		
    	TCHAR* GetWndClassName();	
        virtual void SetInstance(HINSTANCE hInstance);//stores application instance
    	virtual void SetWndCaption(TCHAR* chCap);     //stores user choice of wnd caption
        virtual void SetWndClassName(TCHAR* chClass); //stores user choice of wnd class
        
        int Left,Top,Width,Height;           //wnd dimensions  
        int nExStyle;                        //wnd extended style
        int nID;                             //control identifier or menu handle
        int nStyle;                          //wnd style
        HWND hAppWnd;                        //the main application window handle
        
        void NuovoGioco(HWND);
        void EstrazioneContrade(bool);
        
        NewGameDlg* nuovoGioco;
        Giocatore giocatori[17];
        Contrada contrade[17];
        
   	protected:
		HINSTANCE hInst;                           //the application instance
        virtual BOOL OnCommand(HWND hwndCtl,int nID,UINT uNotifyCode);	//WM_COMMAND handler
        virtual int OnCreate(CREATESTRUCT *cs);         //WM_CREATE handler
        virtual BOOL OnDestroy();                        //WM_DESTROY handler

    private:
    	int nClassStyle;                       //style passed to RegisterClassEx
   		TCHAR chClassName[100];                //string to contain wnd class name
    	TCHAR chCaption[256];                  //string to contain wnd caption
	    HMENU popup;
    	CppCntrl listview;
    	int anno;
    	int numGiocatori;
    	bool isGioco;
    	int contradeLuglio[17];
    	int contradeAgosto[17];
};
