// Giocatore.h: interface for the Giocatore class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GIOCATORE_H 
#define GIOCATORE_H

#include <fstream>
#include <string>

using namespace std;

class Giocatore  
{
public:
	Giocatore();
	virtual ~Giocatore();
	friend ostream& operator<<(ostream& p, Giocatore x);
	friend istream& operator>>(istream& p, Giocatore& x);
	void SetGiocatore(string a, int b, float c);
	string GetNome() { return nome; }
	int GetContrada() { return contrada; }
	int GetCorsi() { return corsi; }
	int GetVinti() { return vinti; }
	int GetAnni() { return anni; }
	float GetConsenso() { return consenso; }
	void SetConsenso(float i);
	void SetContrada(int i) { contrada = i; }

private:
	string nome;
	int contrada;
	int corsi;
	int vinti;
	int anni;
	float consenso;
};

#endif
