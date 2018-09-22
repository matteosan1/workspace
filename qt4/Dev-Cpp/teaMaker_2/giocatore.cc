#include "giocatore.h"

Giocatore::Giocatore()
{}

Giocatore::~Giocatore()
{}

void Giocatore::SetNome(string n)
{ nome = n; }

void Giocatore::SetGiocate(int a)
{ giocate = a; }

void Giocatore::SetMedia(float a)
{ media = a; }

void Giocatore::SetMediaGoal(float a)
{ media_goal = a; }

void Giocatore::SetBravura(float a)
{ bravura = a; }

void Giocatore::SetGoal(float a)
{ goal = a; }

void Giocatore::SetResistenza(float a)
{ resistenza = a; }

void Giocatore::SetParate(float a)
{ parate = a; }

istream& operator>>(istream& in, Giocatore& x)
{
	return (in >> x.nome >> x.giocate >> x.media 
			>> x.media_goal >> x.bravura >> x.goal 
			>> x.resistenza >>	x.parate);
}
