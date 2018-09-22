#include "barbero.h"

Barbero::Barbero() {

    nPar = 0;
    contrada = 0;
    fantino = 0;
    cavallo = 0;
    prove.resize(6);
}

Barbero::~Barbero()
{}

bool Barbero::insertPartito(int a, int b, int c) {

    if (nPar == 16)
        return false;

    partiti[nPar].setPartito(a, b, c);
    nPar++;

    return true;
}

void Barbero::setProve(ProveStrategie p) {
    prove = p;
}

QTextStream& operator<<(QTextStream& out, Barbero& x) {

    out << x.contrada->indice() << " ";
    out << x.fantino->indice() << " ";
    out << x.cavallo->indice() << " ";
    out << x.nPar << "\n";
    for(int i=0; i<x.nPar; ++i)
        out << x.partiti << "\n";
    out << x.theStrategia << " " << x.theAvversaria << " " << x.theForma << "\n";
    for(int i=0; i<6; ++i)
        out << x.prove[i].first << " " << x.prove[i].second << "\n";

    return out;
}

QTextStream& operator>>(QTextStream& in, Barbero& x) {

    int a, b;
    in >> x.indice[0] >> x.indice[1] >> x.indice[2] >> x.nPar;

    for(int i=0; i<x.nPar; ++i)
        in >> x.partiti[i];

    in >> x.theStrategia >> x.theAvversaria >> x.theForma;

    for(int i=0; i<6; ++i) {
        in >> a >> b;
        x.prove[i].first = a;
        x.prove[i].second = b;
    }


    return in;
}

