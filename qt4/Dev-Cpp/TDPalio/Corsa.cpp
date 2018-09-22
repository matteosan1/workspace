// Corsa.cpp: implementation of the CCorsa class.
//
//////////////////////////////////////////////////////////////////////

#include "Corsa.h"
#include "tdpalio.h"
#include "time.h"
#include "stdlib.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Corsa::Corsa()
{
}

Corsa::~Corsa()
{
}

void Corsa::Batterie(Cavallo* c)
{
    int n[20];
    Ordina(n, 20);
        
    for(int batteria=0; batteria<4; batteria++)
    {
        cout << "BATTERIA N° " << batteria+1 << endl;
        for(int i=0; i<5; i++)
        {
                theAccoppiate[i].Set(c[n[i+5*batteria]]);
                cout << c[n[i+5*batteria]].GetNome() << endl;
        }
        
        Gara(theAccoppiate, 1);      
        
        for(int i=0; i<20; i++)
        {
            for(int j=0; j<5; j++)
            {
                if (theAccoppiate[j].GetCavallo() == c[i].GetNome())
                {
                    c[i].SetRisultato(theAccoppiate[j].GetRisultato());
                    c[i].AddTratta();
                }    
            }
        }                    
    }                
}    
    
void Corsa::SceltaCavalli(Gioco* g)
{
    int scelti = 0, old_scelti = 0;
    int voti[20];
    Cavallo* c = g->GetCavalli();
    
    for(int i=0; i<20; i++)
    {   
        if (c[i].GetRisultato() == 1)
        {
            voti[i] = 10;
            old_scelti++;
            scelti++;
        }    
    }       
        
    int* n;
    if (g->IsLuglio())
        n = g->GetLuglio();
    else
        n = g->GetAgosto();    
    
    for(int i=0; i<10; i++)
    {
        theCorrenti[i] = g->GetContrada(n[i]);
        for(int j=0; j<g->GetNumGiocatori(); j++)
        {
            if (g->GetGiocatore(j).GetContrada() == n[i])
                thePlayer[i] = g->GetGiocatore(j);    
        }
    }    
    
    int j=0;
    int z=0;
    while ((scelti != 10) && ((scelti == 10) && (z < 2) && (j != 0)));
    {
        cout << c[j].GetNome() << "  " << c[j].GetRisultato() 
            << "  " << c[j].GetCorsi() << "  " << c[j].GetVinti() 
            << "  " << voti[j] << endl;
        
        if ((voti[j] != 10) && (((old_scelti < 10) && (voti[j] < 6)) || ((old_scelti > 10) && (voti[j] >= 5))))
        {
            voti[j] = 0;
            for(int i=0; i<10; i++)
            {
                if(thePlayer[i].GetNome() == "")
                {
                    srand(time(NULL));
                    
                    int indice = (c[j].GetCorsi() % 5);
                    indice += 5-c[j].GetRisultato();
                    if ((c[j].GetVinti() > 0) && (c[j].GetVinti() < 3))
                        indice += 2;
                    if (c[j].GetVinti() > 2)
                        indice += 4;    
                    int pippo = rand() % 16;
                    if (pippo < indice)
                        voti[j]++; 
                }
                else
                {
                    int a=0;
                    cout << "Vuoi scegliere questo cavallo (0/1) ";
                    cin >> a;
                    if (a == 1)
                        voti[j]++;
                }
                if ((old_scelti < 10) && (voti[j] < 6)) 
                    scelti++;
                if ((old_scelti > 10) && (voti[j] >= 5))
                    scelti--;    
            }
        }
        j++;
        if (j == 20)
        {
            j = 0;
            z++;
            old_scelti = scelti;
        } 
     } 
    
    j=0;
    for(int i=0; i<20; i++)
    {
        if (voti[i] > 5)
        {
            buffer[j] = i;    
            j++;
        }
    }    
} 
    
void Corsa::Assegnazione(Gioco* g)
{   
    SceltaCavalli(g);
    
    int n[10];
    Ordina(n, 10);
    for(int i=0; i<10; i++)
    {
        theCavalli[i] = g->GetCavallo(buffer[n[i]]);
        int pippo = (int)(theCavalli[i].GetProntezza()*.3 + theCavalli[i].GetVelocita()*.3
            + theCavalli[i].GetResistenza()*.4);
        theAccoppiate[i].SetTipoCavallo(pippo);
        
        pippo = 0;
        if (theAccoppiate[i].IsBono() > 6)
            pippo += 10;
        if ((theAccoppiate[i].IsBono() < 7) && (theAccoppiate[i].IsBono() > 3))
            pippo += 5;
        if (theCorrenti[i].GetCuffia() > 38)
            pippo += 9;     
        if ((theCorrenti[i].GetCuffia() > 1) && (theCorrenti[i].GetCuffia() < 10))
            pippo += 2;     
        if ((theCorrenti[i].GetCuffia() > 9) && (theCorrenti[i].GetCuffia() < 21))
            pippo += 3;     
        if ((theCorrenti[i].GetCuffia() > 20) && (theCorrenti[i].GetCuffia() < 39))
            pippo += 8;     
        if (theCorrenti[i].GetCuffia() < 2)
            pippo += 3;     
        
        theAccoppiate[i].SetStrategia(pippo);        
    }    
} 

void Corsa::SceltaFantini(Fantino* f)
{
    int fan_prezzo[15], valore[15], con_strategia[10];
    int scelta[15];
    int inizio, modo_scelta;
    
    for(int i=0; i<15; i++)
    {
        valore[i] = f[i].GetPrezzo(1);
        scelta[i] = 0;
    }    
    Ordina(fan_prezzo, valore, 15);
    for(int i=0; i<10; i++)
        valore[i] = theAccoppiate[i].GetStrategia();
    Ordina(con_strategia, valore, 10);
    
    // scelta Contrade con fantino "fisso"
    
    for(int k=0; k<10; k++)
    {
        // contrada con giocatore umano
        
        int strategia = theAccoppiate[con_strategia[k]].GetStrategia();
        if (strategia > 13)
        {
            inizio = 0;
            modo_scelta = 1;
        }
        if ((strategia > 11) && (strategia < 14))
        {
            inizio = 5;
            modo_scelta = 1;
        }
        if ((strategia > 7) && (strategia < 12))
        {
            inizio = 5;
            modo_scelta = 0;
        }
        if (strategia < 8)
        {
            inizio = 10;
            modo_scelta = 0;
        }
        
        if (modo_scelta == 0)
        {
            int numero;
            srand((unsigned) time(NULL));
            do
            {
                numero = (rand() % (15 - inizio)) + inizio;                
            } while(scelta[numero] == 0);
            scelta[numero] = 1;
            theFantini[k] = f[fan_prezzo[numero]];    
        }
        
        if (modo_scelta == 1)
        {
            
            
            
        }
        
    }
              
                                  
}
    
    
