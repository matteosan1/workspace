#include "CppProtoWnd.h"

#include <windows.h>
//-------------------------------------------------------------------------------------------
//declare window procedure
LRESULT CALLBACK MainWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

//-------------------------------------------------------------------------------------------
//DECLARATION OF CppProtoWnd - the base class
//-------------------------------------------------------------------------------------------
class CppProtoWnd
{
private:
	//variables
	TCHAR        chClassName[100];                //string to contain wnd class name
	TCHAR        chCaption[256];                  //string to contain wnd caption
protected:
	//variables
	HINSTANCE    hInst;                           //the application instance
public:
	CppProtoWnd();	                              //constructor
	virtual ~CppProtoWnd();	                      //destructor
	virtual HWND Create(HWND hParent=NULL);       //wnd creation, parent defaults to NULL
	TCHAR*       GetWndCaption();		
	TCHAR*       GetWndClassName();	
	virtual void SetInstance(HINSTANCE hInstance);//stores application instance
	virtual void SetWndCaption(TCHAR* chCap);     //stores user choice of wnd caption
	virtual void SetWndClassName(TCHAR* chClass); //stores user choice of wnd class
	//variables
	int          Left,Top,Width,Height;           //wnd dimensions
	int          nExStyle;                        //wnd extended style
	int          nID;                             //control identifier or menu handle
	int          nStyle;                          //wnd style
};
//-------------------------------------------------------------------------------------------
//DECLARATION OF CppCntrl. Class Hierarchy: CppProtoWnd<-CppCntrl
//-------------------------------------------------------------------------------------------
class CppCntrl:public CppProtoWnd
{
private:
protected:
public:
	CppCntrl();
	virtual ~CppCntrl();
	virtual HWND Create(HWND hParent=NULL);	//wnd creation, parent defaults to NULL
	//variables
	HWND	hCntrl;		//handle of the control
};

class MainWin:public CppProtoWnd
{
private:
    //functions
    int cardCombset(int n, int k);
    void rank2comb(int rank, int* comb, int ncomb, int n, int m);
    void nextComb(int* combA, int* combB, int n, int m);
    float chiSquare(int* comb, int n, int m, float* chi, float chitot);
    void OrdinaData();                    
    void CalcolaFormazioni();
	void FillListBoxes();                          //puts data into listbox controls
	void LoadData();
	void SaveData();
    //variables
	COLORREF       clrMulti;                       //colour selected in multi selection listbox
	CppCntrl       editSqu1;                       //edit cntrl for showing dir listbox path
	CppCntrl       editSqu2;                       //edit cntrl for showing dir listbox path
    CppCntrl       grpList[6];                     //array of groupboxes
    CppCntrl       listMulti;                      //multiple selection listbox cntrl object
	int            nClassStyle;                    //style passed to RegisterClassEx
	float          var[100][7];
	std::string    nome[100];
	std::string    valutazione[100];
	float          media[100];
	float          partite[100];
	float          goal[100];
	float          giocate;
	int            giocatori;
	float          maxpoint;
	float          minpoint;
	int            C[20][20];
protected:
    //messages
    virtual BOOL   OnCommand(HWND hwndCtl,int nID,UINT uNotifyCode);	//WM_COMMAND handler
    virtual int    OnCreate(CREATESTRUCT *cs);         //WM_CREATE handler
    virtual BOOL   OnDestroy();                        //WM_DESTROY handler
public:
    MainWin();	        //constructor
    virtual ~MainWin();	//destructor
    virtual HWND Create(HWND hParent=NULL);       //wnd creation, parent defaults to NULL
    //class window procedure that global window procedure forwards msgs to
    virtual LRESULT CALLBACK CppWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
    //variables
    HWND        hAppWnd;                         //the main application window handle
    CppWnd*     aggio;
    void        Change();
};
//-------------------------------------------------------------------------------------------

