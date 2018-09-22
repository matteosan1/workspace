// Corsa.h: interface for the CCorsa class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CORSA_H
#define CORSA_H

#include "Gioco.h"
#include "accoppiata.h"

class Corsa  
{
public:
	Corsa();
	virtual ~Corsa();
	void Batterie(Cavallo* c);
	void SceltaCavalli(Gioco* c);
	void SceltaFantini(Fantino* f);
	void Assegnazione(Gioco* c);
	void Prove();
	void Palio();
	void Partiti();
	void FineCorsa();

private:
  	Accoppiata theAccoppiate[10];
  	Contrada theCorrenti[10];
  	Fantino theFantini[10];
  	Cavallo theCavalli[10];
  	Giocatore thePlayer[10];
  	int* buffer;
};

#endif 