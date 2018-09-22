#include "MainWin.h"	//include important stuff
#include "math.h"
#include "resource.h"
#include <fstream>
#include <string>

#define IDC_LIST_MULTI  501
#define IDC_EDIT_SQU_1  502
#define IDC_EDIT_SQU_2  503
#define IDC_BUTTON_1    504
#define IDC_BUTTON_2    505

//-------------------------------------------------------------------------------------------
//DEFINITIONS OF CppWnd
//-------------------------------------------------------------------------------------------
MainWin::MainWin()
{
//set a default value for the wnd caption
SetWndCaption(TEXT("teaMaker"));
//set a default value for the wnd class name
SetWndClassName(TEXT("PIPPO"));
//nullify wnd handle to make later checking easier
hAppWnd=NULL;
//set wnd default dimensions
Left=GetSystemMetrics(SM_CXSCREEN)/4;
Top=GetSystemMetrics(SM_CYSCREEN)/4;
Width=GetSystemMetrics(SM_CXSCREEN)/2;
Height=GetSystemMetrics(SM_CYSCREEN)/2;
//set default window style - don't make it resizable
nStyle=WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_THICKFRAME;
//set default class style used in wnd registration
nClassStyle=CS_HREDRAW|CS_VREDRAW;
//set default colours to -1 (no colour)
clrMulti=GetSysColor(COLOR_BTNFACE);
minpoint = 3.;
maxpoint = 0.;
}
//-------------------------------------------------------------------------------------------
MainWin::~MainWin()
{}
//-------------------------------------------------------------------------------------------
HWND MainWin::Create(HWND hParent)
{
WNDCLASSEX wcx;    //this structure is used for storing information about the wnd 'class'
wcx.cbSize           = sizeof(WNDCLASSEX);                //byte size of WNDCLASSEX struct
wcx.style            = nClassStyle;                       //ensure wnd is always redrawn
wcx.lpfnWndProc      = (WNDPROC)MainWndProc;              //pointer to the Window Procedure
wcx.cbClsExtra       = 0;                                 //Extra bytes for 'class' wnds
wcx.cbWndExtra       = 0;                                 //Extra bytes for this wnd
wcx.hInstance        = hInst;				              //Application instance
wcx.hIcon            = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
wcx.hCursor          = LoadCursor(NULL,IDC_ARROW);        //Cursor for wnd
wcx.hbrBackground    = (HBRUSH)(COLOR_BTNFACE+1);         //Background wnd colour
wcx.lpszMenuName     = NULL;                              //Name of wnd menu
wcx.lpszClassName    = GetWndClassName();                 //Name of this wnd 'class'
wcx.hIconSm          = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
//Register the wnd class with the Windows system
if (!RegisterClassEx(&wcx))
    {
    //Registration has failed so inform the user
    MessageBox( NULL,
                TEXT("Failed to register wnd class"),
                TEXT("ERROR"),
                MB_OK|MB_ICONERROR);
    return NULL;
    }
//create wnd of the 'class' just registered by calling base class function
HWND hwnd;    //the wnd handle
hwnd=CppProtoWnd::Create();
if (!hwnd)
    {
    //wnd creation has failed so inform the user
    MessageBox( NULL,
                TEXT("Failed to create wnd"),
                TEXT("ERROR"), 
                MB_OK|MB_ICONERROR);
    return NULL;
    }
//store the wnd handle
if (!hAppWnd)
    {
    hAppWnd=hwnd;
    }
//Display the wnd
ShowWindow(hwnd,SW_SHOW); 
UpdateWindow(hwnd);
LoadData();
OrdinaData();
aggio = new CppWnd(hwnd, giocatori, nome, valutazione);
return hwnd;
}
//-------------------------------------------------------------------------------------------

LRESULT CALLBACK MainWin::CppWndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
//all the msgs are routed through here. The msgs are 'cracked' ie the wParam and lParam are
//converted into meaningful parameters which are then forwarded to specific handler functions.
switch (Message)
    {
    case WM_COMMAND:
        return OnCommand((HWND)lParam,LOWORD(wParam),HIWORD(wParam));
    case WM_CREATE:
        hAppWnd=hwnd;	//store wnd handle here
        return OnCreate((CREATESTRUCT*)lParam);
    case WM_DESTROY:
        return OnDestroy();
    default:
        return DefWindowProc(hwnd,Message,wParam,lParam);  //let system deal with msg
	}
}
//-------------------------------------------------------------------------------------------
//MESSAGE HANDLER FUNCTIONS
//-------------------------------------------------------------------------------------------
BOOL MainWin::OnCommand(HWND hwndCtl,int nID,UINT uNotifyCode)
{
    //check if msg has come from a cntrl
    if (hwndCtl)
    {
        if (uNotifyCode == BN_CLICKED)
        {
            if (nID == IDOK)
            {
                SaveData();
                DestroyWindow(hAppWnd);
            } 
            if (nID == IDC_BUTTON_1)   
            {
                // Calcola formazioni
                CalcolaFormazioni();
            }
            if (nID == IDC_BUTTON_2)
            {
                DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG), hwndCtl, WndProc);
                Change();
                SendDlgItemMessage(hAppWnd, IDC_LIST_MULTI, LB_RESETCONTENT, 0, 0);
                FillListBoxes();
            }
        }   		
//check if selection has changed in single or multi-selection listboxes
//	if (uNotifyCode==LBN_SELCHANGE)
//	   {
//	       ChangeColour(nID);
//        
//	   }
	}
    return 0;
}
//-------------------------------------------------------------------------------------------
int MainWin::OnCreate(CREATESTRUCT *cs)
{
    //get dimensions of the client area of the wnd
    RECT rc;
    GetClientRect(hAppWnd,&rc);
    //put three groupboxes onto wnd
    grpList[0].SetWndCaption("Giocatori");
    grpList[0].SetWndClassName("BUTTON");
    grpList[0].nStyle|=BS_GROUPBOX|BS_CENTER;
    grpList[0].Top=0;
    grpList[0].Left=0;
    grpList[0].Height=rc.bottom;
    grpList[0].Width=rc.right/2;
    grpList[0].Create(hAppWnd);

    grpList[1].SetWndCaption("Squadra 1");
    grpList[1].SetWndClassName("BUTTON");
    grpList[1].nStyle|=BS_GROUPBOX|BS_CENTER;
    grpList[1].Top=0;
    grpList[1].Left=rc.right/2 + 16;
    grpList[1].Height=rc.bottom/3;
    grpList[1].Width=rc.right/2 - 32;
    grpList[1].Create(hAppWnd);
    
    grpList[2].SetWndCaption("Squadra 2");
    grpList[2].SetWndClassName("BUTTON");
    grpList[2].nStyle|=BS_GROUPBOX|BS_CENTER;
    grpList[2].Top=rc.bottom/3+16;
    grpList[2].Left=rc.right/2 + 16;;
    grpList[2].Height=rc.bottom/3;
    grpList[2].Width=rc.right/2 - 32;
    grpList[2].Create(hAppWnd);
    
    //create an 'ok' default pushbutton
    grpList[3].SetWndClassName("BUTTON");
    grpList[3].SetWndCaption(TEXT("Formazioni"));
    grpList[3].nStyle|=BS_DEFPUSHBUTTON;
    grpList[3].Top=270;
    grpList[3].Left=rc.right/2 + 86 - 60;
    grpList[3].Width=80;
    grpList[3].Height=25;
    grpList[3].nID=IDC_BUTTON_1;	
    grpList[3].Create(hAppWnd);
    
    grpList[4].SetWndClassName("BUTTON");
    grpList[4].SetWndCaption(TEXT("Modifica"));
    grpList[4].nStyle|=BS_DEFPUSHBUTTON;
    grpList[4].Top=270;
    grpList[4].Left=rc.right/2 + 86 + 60;
    grpList[4].Width=80;
    grpList[4].Height=25;
    grpList[4].nID=IDC_BUTTON_2;	
    grpList[4].Create(hAppWnd);
    
    grpList[5].SetWndClassName("BUTTON");
    grpList[5].SetWndCaption(TEXT("Esci"));
    grpList[5].nStyle|=BS_DEFPUSHBUTTON;
    grpList[5].Top=320;
    grpList[5].Left=rc.right/2 + 86;
    grpList[5].Width=80;
    grpList[5].Height=25;
    grpList[5].nID=IDOK;	
    grpList[5].Create(hAppWnd);
    
    editSqu1.SetWndClassName("EDIT");
    editSqu1.nExStyle = WS_EX_CLIENTEDGE;
    editSqu1.nStyle|=ES_MULTILINE|WS_VSCROLL;
    editSqu1.Top = 16;
    editSqu1.Left=rc.right/2 + 32;
    editSqu1.Height=rc.bottom/3 - 24;
    editSqu1.Width=rc.right/2 - 64;
    editSqu1.nID=IDC_EDIT_SQU_1;
    editSqu1.Create(hAppWnd);
    
    editSqu2.SetWndClassName("EDIT");
    editSqu2.nExStyle = WS_EX_CLIENTEDGE;
    editSqu2.nStyle|=ES_MULTILINE|WS_VSCROLL;
    editSqu2.Top = rc.bottom/3 + 32;
    editSqu2.Left=rc.right/2 + 32;
    editSqu2.Height=rc.bottom/3 - 24;
    editSqu2.Width=rc.right/2 - 64;
    editSqu2.nID=IDC_EDIT_SQU_2;
    editSqu2.Create(hAppWnd);
    
    //create a multi selection listbox
    listMulti.SetWndClassName("LISTBOX");
    listMulti.nID=IDC_LIST_MULTI;
    //enable mutltiple selections, sort strings added to listbox and ensure listbox 
    //selections are routed through parent WM_COMMAND
    listMulti.nStyle|=LBS_SORT|LBS_MULTIPLESEL|LBS_NOTIFY|WS_VSCROLL;    
    listMulti.nExStyle=WS_EX_CLIENTEDGE;  //sunken border
    listMulti.Top=24;
    listMulti.Left=16;
    listMulti.Height=rc.bottom - 32;
    listMulti.Width=(rc.right/2) - 32;
    listMulti.Create(hAppWnd);
    //fill list boxes with data
    LoadData();
    FillListBoxes();
    return 0;	//return -1 to fail wnd creation
}
//-------------------------------------------------------------------------------------------
BOOL MainWin::OnDestroy()
{
    PostQuitMessage(0);    //signal end of application
    return 0;
}
//-------------------------------------------------------------------------------------------
//Non Msg Functions
//-------------------------------------------------------------------------------------------

void MainWin::CalcolaFormazioni()
{
    std::string player[22];
    float v[22], avg[22], chi[22], match[22], reti[22], limite;
    float chitot = .0;
    int nSel[100];
    int n = SendMessage(listMulti.hCntrl,LB_GETSELITEMS,100,(LPARAM)&nSel);
       
    if (n > 22)
    {
         MessageBox( NULL,
                TEXT("Troppi giocatori, si gioca in 11..."),
                TEXT("ERRORE !!!"),
                MB_OK|MB_ICONERROR);
        return;
    }
    int m = n/2; 
    
    if (giocate > 15)
        limite = giocate/3;
    else 
        limite = giocate/2;    
    
    for(int i=0; i < n; i++)
    {
        player[i] = nome[nSel[i]];
        v[i] = atof(valutazione[nSel[i]].c_str());
        avg[i] = media[nSel[i]];
        match[i] = partite[nSel[i]];
        reti[i] = goal[nSel[i]];
    }        
                                                                                                  
    for(int i=0; i < n; i++)
    {
        chi[i] = (avg[i]*(giocate - match[i]) + 
                 (v[i]/10*(maxpoint-minpoint)+ minpoint) + 
                 reti[i] * 0.20);
            
        chitot += chi[i];         
    }               

    int comb[22], comb2[22];
    int squ[22];
    int *combA, *combB, *temp;
    int ncomb = cardCombset(n, m); 
    float chifin = 10000., chitemp;

    rank2comb(0, comb, ncomb, n, m);
    combB=comb;
    combA=comb2;
 
    for (int i=0;i<ncomb-1;i++)
    {
        chitemp = chiSquare(combB, n, m, chi, chitot);
        if (chitemp < chifin)
        {
            chifin = chitemp;
            for(int i=0; i<m; i++)
                squ[i] = combB[i];
        }      
        temp=combA;
        combA=combB;
        combB=temp;
        nextComb(combA, combB, n, m);
    }
    
    bool in;
    std::string squadra1, squadra2;
        
    for(int i=0; i < n; i++)
    {
        in = false;
        for(int j=0; j < m; j++)
        {
            if (i == squ[j])
            {
                squadra1 = squadra1 + player[i] + TEXT("\r\n");
                in = true;
            }
        }
        if (!in)    
            squadra2 = squadra2 + player[i] + TEXT("\r\n");         
    }   
    SetWindowText(editSqu1.hCntrl, squadra1.c_str());
    SetWindowText(editSqu2.hCntrl, squadra2.c_str());
}

//-------------------------------------------------------------------------------------------
void MainWin::FillListBoxes()
{
    OrdinaData();
    for (int i=0; i < giocatori; i++)
        SendMessage(listMulti.hCntrl,LB_ADDSTRING,0,(LPARAM) nome[i].c_str());
}

void MainWin::SaveData()
{
    std::ofstream f;
    f.open("giocatori.dat");
    f << giocate << "\n";
    for(int i=0; i<giocatori; i++)
    f << nome[i] << " " << partite[i] << " " << var[i][0] << " " 
        << var[i][1] << " " << var[i][2] << " " << goal[i] << " " 
        << var[i][3] << " " << media[i] << " " << var[i][4] << " " << var[i][5] << " "
        << var[i][6] << " " << valutazione[i] << "\n";
    f.close();
}

void MainWin::OrdinaData()
{
    std::string temps;
    float temp;
    
    for(int i=0; i<giocatori-1; i++)
    {
        for(int j=i+1; j<giocatori; j++)
        {
            if (nome[i] > nome[j])
            {
                temps = nome[j];
                nome[j] = nome[i];
                nome[i] = temps;
                temps = valutazione[j];                
                valutazione[j] = valutazione[i];
                valutazione[i] = temps;
                temp = media[j];
                media[j] = media[i];
                media[i] = temp;
                temp = partite[j];
                partite[j] = partite[i];
                partite[i] = temp;
                temp = goal[j];
                goal[j] = goal[i];
                goal[i] = temp;
                for(int y=0; y<7; y++)
                {
                    temp = var[j][y]; 
                    var[j][y] = var[i][y];
                    var[i][y] = temp;
                }    
            }
        }
    }
}
void MainWin::LoadData()
{
    giocatori = 0;
    std::ifstream f;
    f.open("giocatori.dat");
    f >> giocate;
    while(!f.eof()) 
    {
        f >> nome[giocatori] >> partite[giocatori] >> var[giocatori][0] >> var[giocatori][1] 
            >> var[giocatori][2] >> goal[giocatori] >> var[giocatori][3] >> media[giocatori] 
            >> var[giocatori][4] >> var[giocatori][5] >> var[giocatori][6] >> valutazione[giocatori];
        if (((giocate < 15) && (partite[giocatori] > giocate/2)) || 
            ((giocate >= 15) && (partite[giocatori] > giocate/3)))
        {
            if (media[giocatori] > maxpoint)
                maxpoint = media[giocatori];
            if (media[giocatori] < minpoint)
                minpoint = media[giocatori];    
        }    
        giocatori++;
    } 
    f.close();
    giocatori--;
}

int MainWin::cardCombset(int n, int k)
{
    int i,j,card;

    for (i=0;i<=n;i++)
    {
      C[i][0]=1;
      C[i][i]=1;
    }
    for (i=2;i<=n;i++)
      for (j=1;j<i;j++)
          C[i][j]=C[i-1][j-1]+C[i-1][j];
    card=C[n][k];

    return card;
}

void MainWin::rank2comb(int rank, int* comb, int ncomb, int n, int m)
{
    int i,j,leftover;
    int complement[22];

    leftover=ncomb-rank-1;
    j=n-1;
    for (i=m-1;i>=0;i--)
    {
      for (;leftover < C[j][i+1]; j--)
          ;
      complement[i]=j;
      leftover -= C[j][i+1];
      j--;
    }
    for (i=0;i<m;i++)
      comb[i]=n-1-complement[m-1-i];
}

void MainWin::nextComb(int* combA, int* combB, int n, int m)
{
    int i,j;

    for (i=0;i<m;i++)
      combB[i]=combA[i];
    for (j=m-1;combB[j]==n-m+j;j--)
      ;
      combB[j]++;
    for (j++;j<m;j++)
      combB[j]=combB[j-1]+1;
}

float MainWin::chiSquare(int* comb, int n, int m, float* chi, float chitot)
{
    float chi1=.0, chi2;
    for(int j=0; j<m; j++)
       chi1 += chi[comb[j]];
       
    chi2 = chitot - chi1;
    
    if (n == 7)
        return fabs(chi2 - chi1); 
    else     
        return fabs(chi2/(n-m) - chi1/m); 
}

void MainWin::Change()
{
    giocatori = aggio->giocatori;
    for(int i=0; i<giocatori; i++)
    {
        nome[i] = aggio->nome[i];
        valutazione[i] = aggio->valutazione[i];
    }    
}

//-------------------------------------------------------------------------------------------
//DEFINITIONS OF CppProtoWnd
//-------------------------------------------------------------------------------------------
CppProtoWnd::CppProtoWnd()
{
//nullify instance to make checking it easier later on
hInst=NULL;
nExStyle=0;	//no extended wnd style
nID=0;	        //no identifier or menu
}
//-------------------------------------------------------------------------------------------
CppProtoWnd::~CppProtoWnd()
{
}
//-------------------------------------------------------------------------------------------
//NON MSG FUNCTIONS
//-------------------------------------------------------------------------------------------
HWND CppProtoWnd::Create(HWND hParent)
{
HWND hwnd;    //the wnd handle
hwnd=CreateWindowEx(nExStyle,                           //more or 'extended' styles
                    chClassName,                        //the 'class' of window to create
                    chCaption,                          //the window title
                    nStyle,                             //window style: how it looks
                    Left,                               //window position: left
                    Top,                                //window position: top
                    Width,                              //window width
                    Height,                             //window height
                    hParent,                            //parent window handle
                    (HMENU)nID,                         //handle to wnd menu or cntrl ID
                    hInst,                              //application instance
                    (VOID*)this);                       //store pointer to class
return hwnd;
}
//-------------------------------------------------------------------------------------------
TCHAR* CppProtoWnd::GetWndCaption()
{
return chCaption;
}
//-------------------------------------------------------------------------------------------
TCHAR* CppProtoWnd::GetWndClassName()
{
return chClassName;
}
//-------------------------------------------------------------------------------------------
void CppProtoWnd::SetInstance(HINSTANCE	hInstance)
{
hInst=hInstance;
}
//-------------------------------------------------------------------------------------------
void CppProtoWnd::SetWndCaption(TCHAR* chCap)
{
//check to make sure chCap is valid
if ((chCap)&&(lstrlen(TEXT(chCap))<256))
	{
	//it is so store it
	lstrcpy(chCaption,chCap);
	}
}
//-------------------------------------------------------------------------------------------
void CppProtoWnd::SetWndClassName(TCHAR* chClass)
{
//check to make sure chClass is valid
if ((chClass)&&(lstrlen(TEXT(chClass))<100))
	{
	//it is so store it
	lstrcpy(chClassName,chClass);
	}
}
//-------------------------------------------------------------------------------------------
//DEFINITIONS OF CppCntrl
//-------------------------------------------------------------------------------------------
CppCntrl::CppCntrl()
{
    //set default wnd style
    nStyle=WS_CHILD|WS_VISIBLE;
    //nullify control handle
    hCntrl=NULL;
    Width=100;
    Height=30;
}
//-------------------------------------------------------------------------------------------
CppCntrl::~CppCntrl()
{
//if the handle is still valid then destroy the control
if (hCntrl)
    {
    DestroyWindow(hCntrl);
    }
}
//-------------------------------------------------------------------------------------------
HWND CppCntrl::Create(HWND hParent)
{
//get the application instance from the parent
if (!hInst)
    {
    hInst=(HINSTANCE)GetWindowLong(hParent,GWL_HINSTANCE);
    }
//create the control by calling the base class function
hCntrl=CppProtoWnd::Create(hParent);
return hCntrl;
}
