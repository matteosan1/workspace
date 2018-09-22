#ifndef CONTRADA_H
#define CONTRADA_H

#include <fstream>
#include <string>

using namespace std;

class Contrada  
{
public:
	Contrada();
	virtual ~Contrada();
	friend istream& operator>>(istream& p, Contrada& x);
	friend ostream& operator<<(ostream& p, Contrada x);
	void SetContrada(string a, int b, int c);
	int GetVittorie(int i) { return vittorie[i]; }
	string GetNome() { return nome; }
	int GetNemica() { return avversaria; }
	int GetPopolo() { return int(popolo*maxpopolo); }
	int GetSoldi() { return soldi; }
	int GetCuffia() { return astinenza; }
	void Spesa(int i) { soldi -= i; }
	void Incasso(int i) { soldi += i; }
	void Vittoria(int i);
	void FineAnno();

private:
	string nome;
	int vittorie[3];
	int astinenza;
	float popolo;
	int soldi;
	int avversaria;
	int maxpopolo;
	int risultato;
};
#endif
