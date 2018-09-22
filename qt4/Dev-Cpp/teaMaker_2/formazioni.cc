#include "formazioni.h"
#include "combinazioni.h"
#include "resource.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>

HWND Formazioni::Create(HWND hParent)
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
    wcx.lpszMenuName     = NULL;                             //Name of wnd menu
    wcx.lpszClassName    = GetWndClassName();                 //Name of this wnd 'class'
    wcx.hIconSm          = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wcx.hbrBackground    = (HBRUSH)(COLOR_BTNFACE+1);
    LOGBRUSH background;
    //background.lbStyle = BS_PATTERN;
    //background.lbHatch = (long) LoadImage(hInst,"Bitmap.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);														
    //background.lbHatch = (long) LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MYBITMAP));
    //wcx.hbrBackground = CreateBrushIndirect(&background);

    if (!RegisterClassEx(&wcx))
    {
        MessageBox( NULL,
                TEXT("Failed to register wnd class"),
                TEXT("ERROR"),
                MB_OK|MB_ICONERROR);
        return NULL;
    }

    HWND hwnd;    //the wnd handle
    
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,                     //more or 'extended' styles
                    chClassName,                        //the 'class' of window to create
                    chCaption,                          //the window title
                    nStyle,                             //window style: how it looks
                    Left,                               //window position: left
                    Top,                                //window position: top
                    Width,                              //window width
                    Height,                             //window height
                    hParent,                            //parent window handle
                    (HMENU)NULL,                 //handle to wnd menu or cntrl ID
                    hInst,                              //application instance
                    (VOID*)this);                       //store pointer to class
    
    //hwnd = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2),
    //    hParent, MainWndProc);    
    
    if (!hwnd)
    {
        MessageBox( NULL,
                TEXT("Failed to create wnd"),
                TEXT("ERROR"), 
                MB_OK|MB_ICONERROR);
        return NULL;
    }

    if (!hAppWnd)
        hAppWnd = hwnd;
        
    ShowWindow(hwnd, SW_SHOW); 
    UpdateWindow(hwnd);
    return hwnd;
}

Formazioni::Formazioni()
{ 
    giocate = 0;
    random = 0.2;
    nloop = 2;
    SetWndCaption(TEXT("teaMaker"));
    SetWndClassName(TEXT("teaMaker"));
    hAppWnd=NULL;
//set wnd default dimensions
//Left=GetSystemMetrics(SM_CXSCREEN)/4;
//Top=GetSystemMetrics(SM_CYSCREEN)/4;
//Width=GetSystemMetrics(SM_CXSCREEN)/2;
//Height=GetSystemMetrics(SM_CYSCREEN)/2;
    Left = 100;
    Top = 100;
    Width = 555;
    Height = 450;
//set default window style - don't make it resizable
    nStyle=WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_THICKFRAME;
//set default class style used in wnd registration
    nClassStyle=CS_HREDRAW|CS_VREDRAW;
}

Formazioni::~Formazioni()
{}

LRESULT CALLBACK Formazioni::WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
    POINT pt;
    switch (Message)
    {
        case WM_COMMAND:
            return OnCommand((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        case WM_CREATE:
            hAppWnd = hwnd;	
            return OnCreate((CREATESTRUCT*)lParam);
        case WM_DESTROY:
            return OnDestroy();
        case WM_HSCROLL:
            return OnSlider((HWND)lParam, LOWORD(wParam), HIWORD(wParam));    
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);  //let system deal with msg
	}
}

BOOL Formazioni::OnSlider(HWND hwndCtl,int nID,UINT uNotifyCode)
{
    int slider = GetDlgCtrlID(hwndCtl);   
    DWORD dwPos;    // current position of slider 
    switch (uNotifyCode)
    { 
        case TB_ENDTRACK: 
            dwPos = SendMessage(hwndCtl, TBM_GETPOS, 0, 0); 
            if (dwPos > 10) 
                SendMessage(hwndCtl, TBM_SETPOS, (WPARAM) TRUE, (LPARAM) 10); 
            else if (dwPos < 0) 
                SendMessage(hwndCtl, TBM_SETPOS, (WPARAM) TRUE, (LPARAM) 0); 
            break; 
        default: 
            break; 
    }
    if (slider == IDC_CASUALITA)
    {
        random = SendMessage(hwndCtl, TBM_GETPOS, 0, 0);
        random = random /10;
    }    
    if (slider == IDC_SIMULAZIONI)
    {
        nloop = SendMessage(hwndCtl, TBM_GETPOS, 0, 0); 
    }   
    return true;    
}                    

void Formazioni::LoadGiocatori()
{
    Giocatore g;
    std::ifstream f;
    f.open("dati_giocatori.dat");
    f >> giocate;
    int limite;
    if (giocate < 15)
        limite = (int)giocate/2;
    else 
        limite = (int)giocate/3;    
        
    while(!f.eof()) 
    {
        f >> g;
        if (g.GetGiocate() > limite)
        {
            if (g.GetMedia() > maxbravura)
                maxbravura = g.GetMedia();
            if (g.GetMedia() < minbravura)
                minbravura = g.GetMedia();    
            if (g.GetMediaGoal() > maxgoal)
                maxgoal = g.GetMediaGoal();
            if (g.GetMediaGoal() < mingoal)
                mingoal = g.GetMediaGoal();    
        }    
        giocatori.push_back(g);
    } 
    f.close();
    giocatori.pop_back();
    for(int i=0; i<giocatori.size(); i++)
    {
        if (giocatori[i].GetGiocate() < limite)
        {
            float media = (giocatori[i].GetMedia()*giocatori[i].GetGiocate() +
                    giocatori[i].GetBravura()*(limite - giocatori[i].GetGiocate()))/limite;
            float media_goal = (giocatori[i].GetMediaGoal()*giocatori[i].GetGiocate() +
                    giocatori[i].GetGoal()*(limite - giocatori[i].GetGiocate()))/limite;                     
            giocatori[i].SetMedia(media);
            giocatori[i].SetMediaGoal(media_goal);        
        }    
    }    
    
    vector<Giocatore>::iterator it, jt;
    for(it=giocatori.begin(); it!=giocatori.end()-1; it++)
        for(jt=it+1; jt!=giocatori.end(); jt++)
            if (it->GetNome() > jt->GetNome())
                swap(*it, *jt);
            
    for(int i=0; i<giocatori.size(); i++)
    {
        string s = giocatori[i].GetNome();
        SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)s.c_str());
    }   
}

void Formazioni::SelezioneGiocatori()
{
    giocanti.clear();
    int nSel[100];
    int n = SendMessage(hList1,LB_GETSELITEMS,100,(LPARAM)&nSel);
    
    if (n > 22)
    {
         MessageBox( NULL,
                TEXT("Troppi giocatori, si gioca massimo in 11..."),
                TEXT("ERRORE !!!"),
                MB_OK|MB_ICONERROR);
        return;
    }
    else
    {
        for(int i=0; i < n; i++)
            giocanti.push_back(giocatori[nSel[i]]);
    }           
}

void Formazioni::Simulazione()
{
    int squadra1[22], squadra2[22];
    int punti1=0, punti2=0, diff=-1;
    float limite1, limite2;
    n = giocanti.size();
    m = (int)(n/2);
    SendMessage(hProgress, PBM_SETRANGE, 0, (LPARAM) MAKELONG(0, n*(n-m)));
    Combinazioni comb(n, m);
    comb.rank2comb(0);
    for (int squadre=0; squadre<comb.cardCombset()-1; squadre++)
    {    
        comb.GetComb(squadra1);
        bool isIn;
        int indice = 0;
        for(int i=0; i<n; i++)
        {
            isIn = false;
            for(int j=0; j<m; j++)
                if (squadra1[j] == i)
                    isIn = true;     
            if (!isIn)
            {
                squadra2[indice] = i;
                indice++;
            }    
        }
        
        for(int g1=0; g1<m; g1++)
        {
            for(int g2=0; g2<(n-m); g2++)
            {
                for(int loop=0; loop<pow(10.,nloop); loop++)
                {
                    for(int incontri=1; incontri<4; incontri++)
                    {
                        switch(incontri)
                        {
                            case 0:
                                limite1 = giocanti[squadra1[g1]].GetParate();
                                limite2 = giocanti[squadra2[g2]].GetMediaGoal(); 
                                break;   
                            case 1:
                                limite1 = giocanti[squadra1[g1]].GetMediaGoal();
                                limite2 = giocanti[squadra2[g2]].GetParate(); 
                                break;   
                            default:
                                limite1 = giocanti[squadra1[g1]].GetMedia();
                                limite2 = giocanti[squadra2[g2]].GetMedia(); 
                                break;   
                        }
                        if (((float)loop/(float)nloop) > giocanti[squadra1[g1]].GetResistenza())
                            limite1 = limite1 * (((float)loop/(float)nloop) - giocanti[squadra1[g1]].GetResistenza());
                        
                        if (((float)loop/(float)nloop) > giocanti[squadra2[g2]].GetResistenza())
                            limite2 = limite2 * (((float)loop/(float)nloop) - giocanti[squadra2[g2]].GetResistenza());
                        
                        float goal1 = Numero_casuale(limite1);
                        float goal2 = Numero_casuale(limite2);
                        
                        if (goal1 > goal2)
                            punti1++;
                        if (goal1 < goal2)
                            punti2++;                           
                                                         
                        //cout << giocanti[squadra1[g1]].GetNome() << "  " << punti1 << " " 
                        //        << giocanti[squadra2[g2]].GetNome() << "  " << punti2 << endl;    
                    }   // incontri
                }   // loop
                SendMessage(hProgress, PBM_STEPIT, 0, 0);
            }   // g2
        }   // g1
        
        if ((diff == -1) || ((diff != -1) && (abs(punti1-punti2) < diff)))
        {
            diff = abs(punti1-punti2);
            
            for(int i=0;i<m; i++)
                form1[i] = squadra1[i];
            
            for(int i=0;i<n-m; i++)
                form2[i] = squadra2[i];
        }
        punti1=0;
        punti2=0;    
        comb.nextComb();
    } // squadre
}

float Formazioni::Numero_casuale(float l)
{
    float goal = (float)rand()*(2*random*l) + (1-random)*l;
    return goal;
}

void Formazioni::CalcolaFormazioni()
{
    srand(time(NULL));
    SendMessage(hProgress, PBM_SETPOS, 0, 0);
    SendMessage(hProgress, PBM_SETSTEP, 1, 0);
    SelezioneGiocatori();
    Simulazione();
    PrintSquadre();
}

void Formazioni::PrintSquadre()
{
    SendMessage(hList2, LB_RESETCONTENT, 0, 0);
    SendMessage(hList3, LB_RESETCONTENT, 0, 0);
    
    for(int i=0; i<m; i++)
    {
        string s = giocanti[form1[i]].GetNome();
        SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)s.c_str());
    }   
    
    for(int i=0; i<n-m; i++)
    {
        string s = giocanti[form2[i]].GetNome();
        SendMessage(hList3, LB_ADDSTRING, 0, (LPARAM)s.c_str());
    }   
}

BOOL Formazioni::OnCommand(HWND hwndCtl, int nID, UINT uNotifyCode)
{
    int iIndex;
    if (hwndCtl)
    {
        if (uNotifyCode == BN_CLICKED)
        {
            if (nID == ID_ESCI)
                DestroyWindow(hAppWnd);
                
            if (nID == ID_FORMAZIONI)   
                CalcolaFormazioni();
                
            /*if (nID == ID_MODIFICA)
                DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG), hwndCtl, WndProc);
                Change();
                SendDlgItemMessage(hAppWnd, IDC_LIST_MULTI, LB_RESETCONTENT, 0, 0);
                FillListBoxes();
            }*/
        }  
    } 		
    return 0;
}

int Formazioni::OnCreate(CREATESTRUCT *cs)
{
    RECT rc;
    int pippo = 1;
    GetClientRect(hAppWnd, &rc);
    hList1 = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", "",
        WS_CHILD|WS_VISIBLE|LBS_SORT|LBS_MULTIPLESEL|LBS_NOINTEGRALHEIGHT|WS_VSCROLL|WS_TABSTOP,
        27, 26, 210, 314, hAppWnd, (HMENU)IDC_GIOCATORI, GetModuleHandle(NULL), NULL);
    hList2 = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", "",
        WS_CHILD|WS_VISIBLE|LBS_SORT|LBS_NOINTEGRALHEIGHT|LBS_NOSEL|WS_VSCROLL|WS_TABSTOP,
        305, 145, 210, 76, hAppWnd, (HMENU)IDC_SQUADRA1, GetModuleHandle(NULL), NULL);
    hList3 = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", "",
        WS_CHILD|WS_VISIBLE|LBS_SORT|LBS_NOINTEGRALHEIGHT|LBS_NOSEL|WS_VSCROLL|WS_TABSTOP,
        305, 265, 210, 76, hAppWnd, (HMENU)IDC_SQUADRA2, GetModuleHandle(NULL), NULL);
    HWND hGroup = CreateWindowEx(0, "BUTTON", "Casualità", BS_GROUPBOX|WS_VISIBLE|WS_CHILD, 
        298, 5, 224, 48, hAppWnd, (HMENU)IDC_STATIC, GetModuleHandle(NULL), NULL);
    hGroup = CreateWindowEx(0, "BUTTON", "Giocatori", BS_GROUPBOX|WS_VISIBLE|WS_CHILD, 
        20, 5, 224, 342, hAppWnd, (HMENU)IDC_STATIC, GetModuleHandle(NULL), NULL);
    hGroup = CreateWindowEx(0, "BUTTON", "Squadra 1", BS_GROUPBOX|WS_VISIBLE|WS_CHILD, 
        298, 124, 224, 104, hAppWnd, (HMENU)IDC_STATIC, GetModuleHandle(NULL), NULL);
    hGroup = CreateWindowEx(0, "BUTTON", "Squadra 2", BS_GROUPBOX|WS_VISIBLE|WS_CHILD, 
        298, 244, 224, 104, hAppWnd, (HMENU)IDC_STATIC, GetModuleHandle(NULL), NULL);
    hGroup = CreateWindowEx(0, "BUTTON", "Simulazioni", BS_GROUPBOX|WS_VISIBLE|WS_CHILD, 
        298, 59, 224, 48, hAppWnd, (HMENU)IDC_STATIC, GetModuleHandle(NULL), NULL);
    hButton1 = CreateWindowEx(0, "BUTTON", "Formazioni", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
        368, 373, 85, 21, hAppWnd, (HMENU)ID_FORMAZIONI, GetModuleHandle(NULL), NULL);
    hButton2 = CreateWindowEx(0, "BUTTON", "Esci", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
        20, 373, 75, 21, hAppWnd, (HMENU)ID_ESCI, GetModuleHandle(NULL), NULL);
    hButton3 = CreateWindowEx(0, "BUTTON", "Modifica", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
        169, 373, 75, 21, hAppWnd, (HMENU)ID_MODIFICA, GetModuleHandle(NULL), NULL);
    hSlider1 = CreateWindowEx(0, "msctls_trackbar32", "", WS_CHILD|WS_VISIBLE|TBS_BOTTOM|TBS_AUTOTICKS|WS_TABSTOP,
        305, 26, 210, 20, hAppWnd, (HMENU)IDC_CASUALITA, GetModuleHandle(NULL), NULL);        
    hSlider2 = CreateWindowEx(0, "msctls_trackbar32", "", WS_CHILD|WS_VISIBLE|TBS_BOTTOM|TBS_AUTOTICKS|WS_TABSTOP,
        305, 80, 210, 20, hAppWnd, (HMENU)IDC_SIMULAZIONI, GetModuleHandle(NULL), NULL);        
    hProgress = CreateWindowEx(0, "msctls_progress32", "", WS_CHILD|WS_VISIBLE,
        305, 80, 210, 20, hAppWnd, (HMENU)IDC_SIMULAZIONI, GetModuleHandle(NULL), NULL);        
    
    SendMessage(hSlider1, TBM_SETRANGE, 1, (LPARAM) MAKELONG(0, 10));    
    SendMessage(hSlider1, TBM_SETPOS, 1, (int)(random*10));    
    SendMessage(hSlider2, TBM_SETRANGE, 1, (LPARAM) MAKELONG(0, 10));    
    SendMessage(hSlider2, TBM_SETPOS, 1, nloop);    
    LoadGiocatori();    
    return 0;
}

BOOL Formazioni::OnDestroy()
{
    PostQuitMessage(0);    //signal end of application
    return 0;
}

TCHAR* Formazioni::GetWndCaption()
{
    return chCaption;
}

TCHAR* Formazioni::GetWndClassName()
{
    return chClassName;
}

void Formazioni::SetInstance(HINSTANCE	hInstance)
{
    hInst = hInstance;
}

void Formazioni::SetWndCaption(TCHAR* chCap)
{
    if ((chCap)&&(lstrlen(TEXT(chCap))<256))
	{
		lstrcpy(chCaption,chCap);
	}
}

void Formazioni::SetWndClassName(TCHAR* chClass)
{
    if ((chClass)&&(lstrlen(TEXT(chClass))<100))
	{
		lstrcpy(chClassName,chClass);
	}
}

