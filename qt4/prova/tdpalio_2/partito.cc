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
