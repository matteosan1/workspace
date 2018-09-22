#include "Giocatore.h"

Giocatore::Giocatore()
{
    nome = "";
	anni = 0;
	consenso = 0.;
	contrada = 0;
	corsi = 0;
	vinti = 0;
}

Giocatore::~Giocatore()
{}

void Giocatore::SetGiocatore(string a, int b, float c)
{
    nome = a;
	anni = 0;
	consenso = c;
	contrada = b;
	corsi = 0;
	vinti = 0;
}
/*
ostream& Giocatore::operator<<(ostream& out)
{
	return (out << this.nome << " " << this.contrada << " " << this.anni 
			<< " " << this.corsi << " " << this.consenso << '\n');
}

istream& Giocatore::operator>>(istream& in, Giocatore& x)
{
	return (in >> x.nome >> x.contrada >> x.anni >>
			x.corsi >> x.consenso);
}
*/
