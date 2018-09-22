#include "barbero.h"

Barbero::Barbero() {

    nPar = 0;
    contrada = 0;
    fantino = 0;
    cavallo = 0;
    for(int i=0; i<3; ++i)
        indice[i] = -1;
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

void Barbero::setProve(StrategiaProve p) {
    prove = p;
}

ostream& operator<<(ostream& out, Barbero x) {

    out << x.contrada->indice() << " ";
    out << x.fantino->indice() << " ";
    out << x.cavallo->indice() << " ";
    out << nPar << "\n";
    for(int i=0; i<nPar; ++i)
        out << partiti << "\n";
    out << theStrategia << " " << theAvversaria << " " << theForma << "\n";
    for(int i=0; i<6; ++i)
        out << prove[i] << "\n";

    return out;
}

istream& operator>>(istream& in, Barbero& x) {

    in >> x.indice[0] >> x.indice[1] >> x.indice[2] >> nPar;
    for(int i=0; i<nPar; ++i)
        in >> partiti;
    in >> theStrategia >> theAvversaria >> theForma;
    for(int i=0; i<6; ++i)
        in >> prove[i];

    return in;
}

