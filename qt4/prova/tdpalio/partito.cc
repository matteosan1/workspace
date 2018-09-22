#include "partito.h"

Partito::Partito() {}

void Partito::setPartito(int a, int b, int c) {

    contrada = a;
    tipo = b;
    soldi = c;
    eseguito = false;
}

Partito::~Partito() {}

void Partito::setPartito(int a, int b, int c, int d) {

    contrada = a;
    contrada2 = b;
    tipo = c;
    soldi = d;
    eseguito = false;
}

QTextStream& operator<<(QTextStream& out, Partito& x) {

    out << x.contrada << " ";
    out << x.contrada2 << " ";
    out << x.tipo << " ";
    out << x.soldi << " ";
    out << x.eseguito << "\n";

    return out;
}

QTextStream& operator>>(QTextStream& in, Partito& x) {

    int a = (int)x.eseguito;
    in >> x.contrada >> x.contrada2 >> x.tipo >> x.soldi >> a;

    return in;
}

