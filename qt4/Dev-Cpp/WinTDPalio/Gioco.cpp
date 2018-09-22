// Gioco.cpp: implementation of the Gioco class.
//
//////////////////////////////////////////////////////////////////////

#include "stdlib.h"
#include "time.h"
#include "Gioco.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Gioco::Gioco()
{
	nome = "";
	anno = 0;
	palio = true;
	ngiocatori = 0;
}

Gioco::~Gioco()
{
}

Gioco::Gioco(string a, int b)
{
	srand(time(NULL));
	int y[34];
	nome = a;
	anno = b;
	palio = true;
	ngiocatori = 0;
	for(int i=0; i<17; i++)
	{
		luglio[i] = i;
		agosto[i] = i;
		for(int j=0; j<2; j++)
		{
			y[i+17*j] = rand();
		}
	}
	for(int i=0; i<16; i++)
	{
		for(int j=i+1; j<17; j++)
		{
			if (y[i] > y[j])
			{
				int temp = luglio[i];
				luglio[i] = luglio[j];
				luglio[j] = temp;
			}
			if (y[i+17] > y[j+17])
			{
				int temp = agosto[i];
				agosto[i] = agosto[j];
				agosto[j] = temp;
			}
		}
	}
}

void Gioco::SetContrade(Contrada* c)
{
    for(int i=0; i<17; i++)
        theContrade[i] = c[i];
}

void Gioco::SetFantini(Fantino* c)
{
    for(int i=0; i<15; i++)
        theFantini[i] = c[i];
}

void Gioco::SetCavalli(Cavallo* c)
{
    for(int i=0; i<20; i++)
        theCavalli[i] = c[i];
}

void Gioco::AddGiocatore(string n, int b, float c)
{
	theGiocatori[ngiocatori].SetGiocatore(n, b, c);
	ngiocatori++;
}

void Gioco::Estrazione()
{
	int y[10];
	
	srand(time(NULL));
	
	for(int i=0; i<10; i++)
		y[10] = rand();
	
	for(int i=0; i<9; i++)
	{
		for(int j=i+1; j<10; j++)
		{
			if (y[i] > y[j])
			{
				int temp = luglio[i];
				luglio[i] = luglio[j];
				luglio[j] = temp;
			}
		}
	}

	for(int i=0; i<10; i++)
		y[i] = luglio[i];
	for(int i=0; i<7; i++)
		luglio[i] = luglio[i+10];
	for(int i=7; i<17; i++)
		luglio[i] = y[i-7];

	for(int i=0; i<10; i++)
		y[10] = rand();
	
	for(int i=0; i<9; i++)
	{
		for(int j=i+1; j<10; j++)
		{
			if (y[i] > y[j])
			{
				int temp = agosto[i];
				agosto[i] = agosto[j];
				agosto[j] = temp;
			}
		}
	}

	for(int i=0; i<10; i++)
		y[i] = agosto[i];
	for(int i=0; i<7; i++)
		agosto[i] = agosto[i+10];
	for(int i=7; i<17; i++)
		agosto[i] = y[i-7];
}

istream& operator>>(istream& in, Gioco& x)
{
    in >> x.nome >> x.anno >> x.palio >> x.ngiocatori;
    for(int i=0; i<x.ngiocatori; i++)
    {
        in >> x.theGiocatori[i];
    }  
    for(int i=0; i<17; i++)
    {
        in >> x.theContrade[i];
    }
    for(int i=0; i<17; i++)
    {
        in >> x.luglio[i];
    }
    for(int i=0; i<17; i++)
    {
        in >> x.agosto[i];
    }
	return in;
}

ostream& operator<<(ostream& out, Gioco x)
{
    out << x.nome << " " << x.anno << " " << " " << x.palio << " " << x.ngiocatori << '\n';
    for(int i=0; i<x.ngiocatori; i++)
    {
        out << x.theGiocatori[i] << '\n';
    }  
    for(int i=0; i<17; i++)
    {
        out << x.theContrade[i] << '\n';
    }
    for(int i=0; i<17; i++)
    {
        out << x.luglio[i] << '\n';
    }
    for(int i=0; i<17; i++)
    {
        out << x.agosto[i] << '\n';
    }
	return out;
}
