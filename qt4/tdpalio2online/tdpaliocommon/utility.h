#ifndef UTILITY_H
#define UTILITY_H

#include "TRandom.h"
#include <QVector>

float compatibilita(QVector<int>, QVector<int>);
float amicizia(int);
void OrdinaI(int n, int* num, TRandom* r);
void Ordina(int n, int* num, TRandom* r);
void OrdinaI_fixed(int n, int* num, int* key);
void OrdinaF_fixed(int n, int* num, float* key);
int Uniform_symmetric(int c, int i, TRandom* r);

int Strategia(int, float);

/*
class Strategia {
public:
   Strategia() {}
   ~Strategia() {}
   double value(double in0, double in1, double in2, double in3);
private:
   double input0;
   double input1;
   double input2;
   double input3;
   double neuron0x11d98d20();
   double neuron0x11d8abb0();
   double neuron0x11d8dba0();
   double neuron0x11d8dcf8();
   double input0x11d8e010();
   double neuron0x11d8e010();
   double input0x11de8780();
   double neuron0x11de8780();
   double input0x11de8a28();
   double neuron0x11de8a28();
   double input0x11d8def8();
   double neuron0x11d8def8();
   double synapse0x11d8aa10();
   double synapse0x11d98ac8();
   double synapse0x11d8e120();
   double synapse0x11d8aaf0();
   double synapse0x11de8968();
   double synapse0x11de8998();
   double synapse0x11de89c8();
   double synapse0x11de89f8();
   double synapse0x11de8c10();
   double synapse0x11de8c40();
   double synapse0x11de8c70();
   double synapse0x11de8ca0();
   double synapse0x11de8de0();
   double synapse0x11de8e10();
   double synapse0x11de8e40();
};
*/

#endif
