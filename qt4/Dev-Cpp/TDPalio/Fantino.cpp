// Fantino.cpp: implementation of the Fantino class.
//
//////////////////////////////////////////////////////////////////////

#include "Fantino.h"
#include "time.h"
#include "stdlib.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Fantino::Fantino()
{
	nome = "";
	affidabilita = 0;
	allenamento = 0;
	anni = 0;
	corsi = 0;
	vinti = 0;
	prontezza = 0;
	rischio = 0;
}

Fantino::~Fantino()
{
}

void Fantino::SetFantino(string a, int b, int c, int d, int e)
{
	nome = a;
	affidabilita = d;
	allenamento = e;
	anni = 0;
	corsi = 0;
	vinti = 0;
	prontezza = b;
	rischio = c;
	prezzo = 50;
}

int Fantino::GetMedia()
{
	return int((affidabilita+prontezza+rischio)/3);
}

int Fantino::GetPrezzo(int i)
{
    if (i == 1)
    {
        if (corsi < 3)
            return 15;
        else
            return prezzo;    
    }
    if (i > 1)
    {
        srand((unsigned) time(NULL));
        
        if (i == 2)
        {
            int pippo = (rand() % 50);
            return (int) prezzo*i*(1+pippo/100);
        }    
        if (i == 4)
        {
            int pippo = (rand() % 30);
            return (int) prezzo*i*(1+pippo/100);
        }    
        if (i == 6)
        {
            int pippo = (rand() % 10);
            return (int) prezzo*i*(1+pippo/100);
        }                    
    }    
}

ostream& operator<<(ostream& out, Fantino x)
{
	return (out << x.nome << " " << x.anni << " " << x.corsi 
			<< " " << x.vinti << " " << x.prontezza << " "
			<< x.rischio << " " << x.allenamento << " " << x.affidabilita << '\n');
}

istream& operator>>(istream& in, Fantino& x)
{
	return (in >> x.nome >> x.anni >> x.corsi 
			>> x.vinti >> x.prontezza 
			>> x.rischio >> x.allenamento >> x.affidabilita);
}
