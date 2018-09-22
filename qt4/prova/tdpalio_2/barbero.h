#ifndef BARBERI_H
#define BARBERI_H

#include "contrada.h"
#include "fantino.h"
#include "cavallo.h"
#include "partito.h"

#include <vector>
#include <pair>

using namespace std;

//typedef vector<pair<int, int> > StrategiaProve;

class Barbero {
    public:
        Barbero();
        virtual ~Barbero();

        void setContrada(Contrada* c) { contrada = c; };
        void setFantino(Fantino* c) { fantino = c; };
        void setCavallo(Cavallo* c) { cavallo = c; };

        bool insertPartito(int a, int b, int c);

        void setProve(vector<pair<int, int> > p);
        vector<pair<int, int> > getProve() { return prove; };

	    void setStrategia(float a) { theStrategia = a; };
	    float strategia() { return theStrategia; };

	    void setAvversaria(int a) { theAvversaria = a; };
	    int avversaria() { return theAvversaria; };

	    void setForma(int f) { theForma = f; };
	    int forma() { return theForma; };

        int getIndice(int i) { return indice[i]; };
        Contrada* getContrada() { return contrada; };
        Fantino* getFantino() { return fantino; };
        Cavallo* getCavallo() { return cavallo; };
        Partito partito(int i) { return partiti[i]; };
        int nPartiti() { return nPar; };

        friend ostream& operator<<(ostream& out, Barbero x);
        friend istream& operator>>(istream& in, Barbero& x);

    private:
        Contrada* contrada;
        Fantino* fantino;
        Cavallo* cavallo;
        int nPar;
        Partito partiti[17];
	    float theStrategia;
	    int theAvversaria;
	    int theForma;
        vector<pair<int, int> > prove;
        int indici[3];
};

#endif
