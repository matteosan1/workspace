#ifndef BARBERI_H
#define BARBERI_H

#include "contrada.h"
#include "fantino.h"
#include "cavallo.h"
#include "partito.h"

#include <QTextStream>
#include <QPair>

using namespace std;

typedef QVector<QPair<int, int> > ProveStrategie;

class Barbero {
    public:
        Barbero();
        virtual ~Barbero();

        void setContrada(Contrada* c) { contrada = c; };
        void setFantino(Fantino* c) { fantino = c; };
        void setCavallo(Cavallo* c) { cavallo = c; };

        bool insertPartito(int a, int b, int c);

        void setProve(ProveStrategie p);
        ProveStrategie getProve() { return prove; };

	    void setStrategia(int a) { theStrategia = a; };
	    int strategia() { return theStrategia; };

	    void setAvversaria(int a) { theAvversaria = a; };
	    int avversaria() { return theAvversaria; };

	    //void setForma(int f) { theForma = f; };
	    //int forma() { return theForma; };
        int getIndice(int i) { return indice[i]; };

        Contrada* getContrada() { return contrada; };
        Fantino* getFantino() { return fantino; };
        Cavallo* getCavallo() { return cavallo; };
        Partito partito(int i) { return partiti[i]; };
        int nPartiti() { return nPar; };

        friend QTextStream& operator<<(QTextStream& out, Barbero& x);
        friend QTextStream& operator>>(QTextStream& in, Barbero& x);

    private:
        Contrada* contrada;
        Fantino* fantino;
        Cavallo* cavallo;
        int nPar;
        Partito partiti[17];
	    int theStrategia;
	    int theAvversaria;
	    //int theForma;
        ProveStrategie prove;
        int indice[3];
};

#endif
