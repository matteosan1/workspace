// Cavallo.h: interface for the Cavallo class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CAVALLO_H
#define CAVALLO_H

#include <fstream>
#include <string>

using namespace std;

class Cavallo  
{
public:
	Cavallo();
	virtual ~Cavallo();
	friend istream& operator>>(istream& p, Cavallo& x);
	friend ostream& operator<<(ostream& p, Cavallo x);
	void SetCavallo(string a, int b, int c, int d, int e, int f);
	string GetNome() { return nome; }
	int GetPrecisione() { return precisione; }
	void SetRisultato(int i) { risultato = i; }
	void AddTratta() { tratte++; }
	int GetRisultato() { return risultato; }
	int GetProntezza() { return prontezza; }
	int GetColore() { return colore; }
	int GetAnni() { return anni; }
	int GetCorsi() { return corsi; }
	int GetTratte() { return tratte; }
	int GetVinti() { return vinti; }
	int GetResistenza() { return resistenza; }
	int GetVelocita() { return velocita; }

private:
	string nome;
	int colore;
	int corsi;
	int anni;
	int tratte;
	int vinti;
	int prontezza;
	int resistenza;
	int velocita;
	int precisione;
	int risultato;
};

#endif 
