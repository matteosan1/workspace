#include "time.h"
#include "stdlib.h"
#include <iostream>
#include "tdpalio.h"
#include "main.h"
#include "NewGameDlg.h"
#include "NewPlayerDlg.h"

void Ordina(int* numero, int num)
{
    int y[25];
    srand(time(NULL));    
    
    for(int i=0; i<num+1; i++)
    {
        numero[i] = i;
        y[i] = rand();     
    }

	for(int i=0; i<num-1; i++)
	{
		for(int k=i+1; k<num; k++)
		{
			if (y[i] > y[k])
			{
				int temp = numero[i];
				numero[i] = numero[k];
				numero[k] = temp;
				temp = y[i];
				y[i] = y[k];
				y[k] = temp;
			}
		}
	} 
}	

void Ordina (int* numero, int* n, int num)
{
    for(int i=0; i<num; i++)
        numero[i] = i;

	for(int i=0; i<num-1; i++)
	{
		for(int k=i+1; k<num; k++)
		{
			if (n[i] > n[k])
			{
				int temp = numero[i];
				numero[i] = numero[k];
				numero[k] = temp;
				temp = n[i];
				n[i] = n[k];
				n[k] = temp;
			}
		}
	} 
}	

Gioco* InizioGioco(HWND hwnd)
{
    Gioco* g;
    Contrada contrade[17];
    Cavallo cavalli[20];
    Fantino fantini[15];
    
    NewGameDlg ngd(hwnd);
    
    if (ngd.GetAnno() == -1)
        return NULL;
    
    string nome(ngd.GetNome());
    int a, b, c, d, f;
    int numero[17];
    
    g = new Gioco(nome, ngd.GetAnno());
    Ordina(numero, 17);
    
    for (int i=0; i<ngd.GetGiocatori(); i++)
    {
        NewPlayerDlg npd(hwnd);
        string gioc(npd.GetNome());
        g->AddGiocatore(gioc, numero[i], 0.75);
    }    

    ifstream f1("contrade.dat");
    for(int i=0; i<17; i++)
    {
        f1 >> nome >> a >> b;
        contrade[i].SetContrada(nome, a, b);
    }
    f1.close();
    g->SetContrade(contrade);

    ifstream f2("cavalli.dat");
    for(int i=0; i<20; i++)
    {
        f2 >> nome >> a >> b >> c >> d >> f;
        cavalli[i].SetCavallo(nome, a, b, c, d, f);
    }
    f2.close();
    g->SetCavalli(cavalli);

    ifstream f3("fantini.dat");
    for(int i=0; i<15; i++)
    {
        f3 >> nome >> a >> b >> c >> d;
        fantini[i].SetFantino(nome, a, b, c, d);
    }
    f3.close();
    g->SetFantini(fantini);
   
    return g;
}

void Gara(Accoppiata* accoppiata, int tipo)
{
    int giri, ncontrade;

    if (tipo == 1)
    {
        giri = 1;
        ncontrade = 5;
    }
        
    int num[10];
    Ordina(num, ncontrade);
/*           
    cout << "ORDINE ALLA MOSSA:" << endl;

    if (tipo == 1)
    {
        for(int i=0; i<ncontrade; i++)
        {
            cout << num[i] << endl;        
        }   
    }
*/    
    int max = 0;
    
    // Mossa
    for (int i=0; i<ncontrade; i++)
        accoppiata[num[i]].Partenza();
    
    // Corsa
    do
    {
        for(int i=0; i<ncontrade; i++)
        {
            accoppiata[num[i]].Avanzamento();
            cout << accoppiata[num[i]].GetCavallo() << "  " 
                 << accoppiata[num[i]].GetPosizione() << endl;    
            if (max < accoppiata[num[i]].GetPosizione())
                max = accoppiata[num[i]].GetPosizione();   
        }
    } while(max < giri); 
    
    // ordina le accoppiate per i risultati
    
    for(int i=0; i<ncontrade-1; i++)
    {
        for(int j=i+1; j<ncontrade; j++)
        {
            if (accoppiata[i].GetPosizione() < accoppiata[j].GetPosizione())
            {
                Accoppiata temp = accoppiata[i]; 
                accoppiata[i] = accoppiata[j];
                accoppiata[j] = temp;
            }    
        }    
    }
    
    for(int i=0; i<ncontrade; i++)
    {
        accoppiata[i].SetRisultato(i+1);
    }    
}
