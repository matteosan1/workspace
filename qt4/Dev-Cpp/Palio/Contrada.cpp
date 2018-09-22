#include "Contrada.h"

Contrada::Contrada()
{
	nome = "";
	astinenza = 0;
	avversaria = 0;
	maxpopolo = 0;
	popolo = 0.;
	soldi = 0;
	for(int i=0; i<3; i++)
		vittorie[i] = 0;
	risultato = 0;	
}

Contrada::~Contrada()
{
}

void Contrada::SetContrada(string a, int b, int c)
{
	nome = a;
	astinenza = 0;
	avversaria = c;
	maxpopolo = b;
	popolo = 0.8;
	soldi = 10000;
	for(int i=0; i<3; i++)
		vittorie[i] = 0;
    risultato = 0;
}

void Contrada::Vittoria(int i)
{
	vittorie[i]++;
	astinenza = 0;
	maxpopolo += int(maxpopolo*0.05);
	soldi -= 250;
}

void Contrada::FineAnno()
{
	astinenza++;
	soldi += int(maxpopolo*popolo*0.1);
	popolo = popolo*(1+2.8) - 2.8*popolo*popolo;
}

ostream& operator<<(ostream& out, Contrada x)
{
	return (out << x.nome << " " << x.maxpopolo << " " << x.popolo 
			<< " " << x.soldi << " " << x.avversaria << " "
			<< x.vittorie[0] << " " << x.vittorie[1] << " " << 
			x.vittorie[2] << " " << x.astinenza << '\n');
}

istream& operator>>(istream& in, Contrada& x)
{
	return (in >> x.nome >> x.maxpopolo >> x.popolo 
			>> x.soldi >> x.avversaria >> x.vittorie[0] 
			>> x.vittorie[1] >>	x.vittorie[2] >> x.astinenza);
}

