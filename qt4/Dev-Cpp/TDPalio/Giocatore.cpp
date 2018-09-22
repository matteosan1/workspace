// Giocatore.cpp: implementation of the Giocatore class.
//
//////////////////////////////////////////////////////////////////////

#include "Giocatore.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Giocatore::Giocatore()
{
    nome = "";
//	strcpy(nome, "");
	anni = 0;
	consenso = 0.;
	contrada = 0;
	corsi = 0;
	vinti = 0;
}

Giocatore::~Giocatore()
{

}

void Giocatore::SetGiocatore(string a, int b, float c)
{
    nome = a;
//	strcpy(nome, a);
	anni = 0;
	consenso = c;
	contrada = b;
	corsi = 0;
	vinti = 0;
}

ostream& operator<<(ostream& out, Giocatore x)
{
	return (out << x.nome << " " << x.contrada << " " << x.anni 
			<< " " << x.corsi << " " << x.consenso << '\n');
}

istream& operator>>(istream& in, Giocatore& x)
{
	return (in >> x.nome >> x.contrada >> x.anni >>
			x.corsi >> x.consenso);
}

