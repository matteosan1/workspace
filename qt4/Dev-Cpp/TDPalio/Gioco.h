// Gioco.h: interface for the Gioco class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GIOCO_H
#define GIOCO_H

#include "Giocatore.h"
#include "Fantino.h"
#include "Contrada.h"
#include "Cavallo.h"
#include <fstream>
#include <string>

class Gioco  
{
public:
	Gioco();
	Gioco(string a, int b);
	virtual ~Gioco();
	friend istream& operator>>(istream& p, Gioco& x);
	friend ostream& operator<<(ostream& p, Gioco x);
	void SetContrade(Contrada* c);
	void SetCavalli(Cavallo* c);
	void SetFantini(Fantino* c);
	void SetGiocatori(Giocatore* c);
	string GetNome() { return nome; }
	int GetAnno() { return anno; }
	void AddGiocatore(string n, int b, float c);
	int GetNumGiocatori() { return ngiocatori; }
	Giocatore* GetGiocatori() { return theGiocatori; }
	Contrada* GetContrade() { return theContrade; }
	Cavallo* GetCavalli() { return theCavalli; }
	Fantino* GetFantini() { return theFantini;}
	Contrada& GetContrada(int i) { return theContrade[i]; }
	Cavallo& GetCavallo(int i) { return theCavalli[i]; }
	Fantino& GetFantino(int i) { return theFantini[i]; }
	Giocatore& GetGiocatore(int i) { return theGiocatori[i]; }
	void Estrazione();
	int* GetLuglio() { return luglio; }
	int* GetAgosto() { return agosto; }
	bool IsLuglio() { return palio; }

private:
	string nome;
	int anno;
	bool palio;
	int luglio[17];
	int agosto[17];
	int ngiocatori;
	Giocatore theGiocatori[17];
	Contrada theContrade[17];
	Cavallo theCavalli[20];
	Fantino theFantini[15];
};

#endif

