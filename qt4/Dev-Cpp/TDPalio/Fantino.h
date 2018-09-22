// Fantino.h: interface for the Fantino class.
//
//////////////////////////////////////////////////////////////////////

#ifndef FANTINO_H
#define FANTINO_H

#include <fstream>
#include <string>

using namespace std;

class Fantino  
{
public:
	Fantino();
	void SetFantino(string a, int b, int c, int d, int e);
	virtual ~Fantino();
	friend istream& operator>>(istream& p, Fantino& x);
	friend ostream& operator<<(ostream& p, Fantino x);
	string GetNome() { return nome;}
	int GetPrezzo(int i);
	void SetPrezzo();
	int GetMedia();
	int GetAnni() { return anni; }
	int GetCorsi() { return corsi; }
	int GetVinti() { return vinti; }
	int GetProntezza() { return prontezza; }
	int GetRischio() { return rischio; }
	int GetAllenamento() { return allenamento; }
	int GetAffidabilita() { return affidabilita; }
	void SetProntezza(int i);
	void SetAllenamento(int i);

private:
	string nome;
	int prezzo;
	int anni;
	int corsi;
	int vinti;
	int prontezza;
	int rischio;
	int allenamento;
	int affidabilita;
};

#endif 
