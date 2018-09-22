#ifndef _FORMAZIONI_
#define _FORMAZIONI_

#include "giocatore.h"
#include "windows.h"
#include "commctrl.h"
#include <vector>

BOOL CALLBACK MainWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);

using namespace std;

class Formazioni
{
    public:
        Formazioni();
        virtual ~Formazioni(void);
        virtual HWND Create(HWND hParent=NULL);       //wnd creation, parent defaults to NULL
        virtual LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
       	TCHAR* GetWndCaption();		
    	TCHAR* GetWndClassName();	
        virtual void SetInstance(HINSTANCE hInstance);//stores application instance
    	virtual void SetWndCaption(TCHAR* chCap);     //stores user choice of wnd caption
        virtual void SetWndClassName(TCHAR* chClass); //stores user choice of wnd class
        // riempire listbox con giocatori
        void LoadGiocatori(void);
        void SelezioneGiocatori(void);
        void Simulazione(void);
        float Numero_casuale(float l);
        void CalcolaFormazioni(void);
        void PrintSquadre(void);
        
        int Left,Top,Width,Height;           //wnd dimensions  
        int nExStyle;                        //wnd extended style
        int nID;                             //control identifier or menu handle
        int nStyle;                          //wnd style
        HWND hAppWnd;                        //the main application window handle
        HWND hList1, hList2, hList3;
        HWND hButton1, hButton2, hButton3;
        HWND hSlider1, hSlider2;
        HWND hProgress;
        	    
	protected:
        HINSTANCE hInst;                          
        virtual BOOL OnCommand(HWND hwndCtl,int nID,UINT uNotifyCode);
        virtual int OnCreate(CREATESTRUCT *cs);      
        virtual BOOL OnDestroy(void);                
        virtual BOOL OnSlider(HWND hwndCtl,int nID,UINT uNotifyCode);                    
    
    private:
        vector<Giocatore> giocatori;
        vector<Giocatore> giocanti;
  	    float giocate;
	    float maxbravura;
	    float minbravura;
	    float maxgoal;
	    float mingoal;
	    int nloop, n, m;
	    float random;
	    int form1[22], form2[22];
	    int nClassStyle;                    //style passed to RegisterClassEx
   		TCHAR chClassName[100];                //string to contain wnd class name
    	TCHAR chCaption[256];                  //string to contain wnd caption
};
#endif

// creare file con:
// giocate
// nome giocate media mediagoal bravura goal resistenza parata
