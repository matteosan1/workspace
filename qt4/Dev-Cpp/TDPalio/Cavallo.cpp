// Cavallo.cpp: implementation of the CCavallo class.
//
//////////////////////////////////////////////////////////////////////

#include "Cavallo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cavallo::Cavallo()
{
	nome = "";
	anni = 0;
	colore = 0;
	corsi = 0;
	prontezza = 0;
	resistenza = 0;
	tratte = 0;
	velocita = 0;
	vinti = 0;
	precisione = 0;
	risultato = 0;
}

Cavallo::~Cavallo()
{
}

void Cavallo::SetCavallo(string a, int b, int c, int d, int e, int f)
{
    precisione = f;
	nome = a;
	anni = 0;
	colore = b;
	corsi = 0;
	prontezza = c;
	resistenza = d;
	tratte = 0;
	velocita = e;
	vinti = 0;
	risultato = 0;
}

ostream& operator<<(ostream& out, Cavallo x)
{
    srand(time(NULL));
    x.precisione = (rand()%9);
	return (out << x.nome << " " << x.anni << " " << x.corsi 
			<< " " << x.tratte << " " << x.vinti << " "
			<< x.colore << " " << x.prontezza << " " << 
			x.resistenza << " " << x.precisione << " " 
            << x.velocita << '\n');
}

istream& operator>>(istream& in, Cavallo& x)
{
	(in >> x.nome >> x.anni >> x.corsi 
		>> x.tratte >> x.vinti >> x.colore 
		>> x.prontezza >> x.resistenza >> x.velocita);
	return in;	
}
