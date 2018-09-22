#include "combinazioni.h"
#include <iostream>

Combinazioni::Combinazioni(int a, int b)
{
    n = a;
    k = b;
}

void Combinazioni::GetComb(int* v)
{
    for(int i=0; i<k; i++)
        *(v+i) = comb[i];
}

Combinazioni::~Combinazioni()
{}

/*
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

void MainWin::FillListBoxes()
{
    OrdinaData();
    for (int i=0; i < giocatori; i++)
        SendMessage(listMulti.hCntrl,LB_ADDSTRING,0,(LPARAM) nome[i].c_str());
}
*/

int Combinazioni::cardCombset()
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

void Combinazioni::rank2comb(int rank)
{
    int i,j,leftover;
    int complement[22];
    
    int ncomb = cardCombset();

    leftover=ncomb-rank-1;
    j=n-1;
    for (i=k-1;i>=0;i--)
    {
      for (;leftover < C[j][i+1]; j--)
          ;
      complement[i]=j;
      leftover -= C[j][i+1];
      j--;
    }
    for (i=0;i<k;i++)
      comb[i]=n-1-complement[k-1-i];
}

void Combinazioni::nextComb()
{
    int i,j;

    for (i=0;i<k;i++)
      comb2[i]=comb[i];
    for (j=k-1;comb[j]==n-k+j;j--)
      ;
      comb2[j]++;
    for (j++;j<k;j++)
      comb2[j]=comb2[j-1]+1;
    
    for (i=0;i<k;i++)
      comb[i]=comb2[i];
}

void Combinazioni::Print()
{
    for(int i=0; i<k; i++)
        cout << comb[i];
    cout << endl;    
}

/*
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

*/
