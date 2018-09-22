#include "utility.h"
#include <math.h>

void OrdinaI_fixed(int n, int* num, int* key) {

    for(int i=0; i<n; i++)
        num[i] = i;

    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if (key[i] > key[j]) {
                int temp = key[i];
                key[i] = key[j];
                key[j] = temp;
                int temp1 = num[i];
                num[i] = num[j];
                num[j] = temp1;
            }
        }
    }
}

void OrdinaF_fixed(int n, int* num, float* key) {

    for(int i=0; i<n; i++)
        num[i] = i;

    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if (key[i] > key[j]) {
                float temp = key[i];
                key[i] = key[j];
                key[j] = temp;
                int temp1 = num[i];
                num[i] = num[j];
                num[j] = temp1;
            }
        }
    }
}

void OrdinaI(int n, int* num, TRandom* r) {

    for(int i=0; i<n; i++)
        num[i] = i;

    float c[n];
    r->RndmArray(n, c);

    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if (c[i] > c[j]) {
                float temp = c[i];
                c[i] = c[j];
                c[j] = temp;
                int temp1 = num[i];
                num[i] = num[j];
                num[j] = temp1;
            }
        }
    }
}

void Ordina(int n, int* num, TRandom* r) {

    float c[n];
    r->RndmArray(n, c);

    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if (c[i] > c[j]) {
                float temp = c[i];
                c[i] = c[j];
                c[j] = temp;
                int temp1 = num[i];
                num[i] = num[j];
                num[j] = temp1;
            }
        }
    }
}

int Uniform_symmetric(int c, int interval, TRandom* r) {

    int n;
    n = r->Integer(interval*2);
    n = n + (c - interval);

    return n;
}

//cuffia, cavallo
int Strategia(int a, float b) {

    int i1, i2;
    if (a < 2)
        i1 = 0;
    if ((a < 6) && (a > 1))
        i1 = 1;
    if ((a < 11) && (a > 5))
        i1 = 2;
    if ((a < 16) && (a > 10))
        i1 = 3;
    if (a > 15)
        i1 = 4;
    if (b < 4.)
        i2 = 0;
    if ((b < 7.) && (b > 3.))
        i2 = 1;
    if ((b < 9.) && (b > 6.))
        i2 = 2;
    if (b > 8.)
        i2 = 3;

    int rate[][5] = {{3, 3, 3, 3, 3}, {3, 3, 4, 4, 8}, {13, 13, 12, 8, 8}, {9, 13, 8, 8, 8}};

    return rate[i1][i2];
}

/*
// cav1, cav2, cuffia, soldi
double Strategia::value(double in0, double in1, double in2, double in3) {
   input0 = (in0 - 0)/1;
   input1 = (in1 - 0)/1;
   input2 = (in2 - 0)/1;
   input3 = (in3 - 0)/500.;

   return ((neuron0x11d8def8()*1)+0);
}

double Strategia::neuron0x11d98d20() {
   return input0;
}

double Strategia::neuron0x11d8abb0() {
   return input1;
}

double Strategia::neuron0x11d8dba0() {
   return input2;
}

double Strategia::neuron0x11d8dcf8() {
   return input3;
}

double Strategia::input0x11d8e010() {
   double input = 2.7381;
   input += synapse0x11d8aa10();
   input += synapse0x11d98ac8();
   input += synapse0x11d8e120();
   input += synapse0x11d8aaf0();
   return input;
}

double Strategia::neuron0x11d8e010() {
   double input = input0x11d8e010();
   return ((1/(1+exp(-input))) * 1)+0;
}

double Strategia::input0x11de8780() {
   double input = -10.0596;
   input += synapse0x11de8968();
   input += synapse0x11de8998();
   input += synapse0x11de89c8();
   input += synapse0x11de89f8();
   return input;
}

double Strategia::neuron0x11de8780() {
   double input = input0x11de8780();
   return ((1/(1+exp(-input))) * 1)+0;
}

double Strategia::input0x11de8a28() {
   double input = -65.958;
   input += synapse0x11de8c10();
   input += synapse0x11de8c40();
   input += synapse0x11de8c70();
   input += synapse0x11de8ca0();
   return input;
}

double Strategia::neuron0x11de8a28() {
   double input = input0x11de8a28();
   return ((1/(1+exp(-input))) * 1)+0;
}

double Strategia::input0x11d8def8() {
   double input = 2.88285;
   input += synapse0x11de8de0();
   input += synapse0x11de8e10();
   input += synapse0x11de8e40();
   return input;
}

double Strategia::neuron0x11d8def8() {
   double input = input0x11d8def8();
   return (input * 1)+0;
}

double Strategia::synapse0x11d8aa10() {
   return (neuron0x11d98d20()*-0.21785);
}

double Strategia::synapse0x11d98ac8() {
   return (neuron0x11d8abb0()*0.226564);
}

double Strategia::synapse0x11d8e120() {
   return (neuron0x11d8dba0()*-0.114728);
}

double Strategia::synapse0x11d8aaf0() {
   return (neuron0x11d8dcf8()*-1.4433);
}

double Strategia::synapse0x11de8968() {
   return (neuron0x11d98d20()*-15.3484);
}

double Strategia::synapse0x11de8998() {
   return (neuron0x11d8abb0()*-35.4382);
}

double Strategia::synapse0x11de89c8() {
   return (neuron0x11d8dba0()*-0.571697);
}

double Strategia::synapse0x11de89f8() {
   return (neuron0x11d8dcf8()*29.2582);
}

double Strategia::synapse0x11de8c10() {
   return (neuron0x11d98d20()*8.24552);
}

double Strategia::synapse0x11de8c40() {
   return (neuron0x11d8abb0()*0.730877);
}

double Strategia::synapse0x11de8c70() {
   return (neuron0x11d8dba0()*0.109585);
}

double Strategia::synapse0x11de8ca0() {
   return (neuron0x11d8dcf8()*9.66052);
}

double Strategia::synapse0x11de8de0() {
   return (neuron0x11d8e010()*-2.08714);
}

double Strategia::synapse0x11de8e10() {
   return (neuron0x11de8780()*-10.6656);
}

double Strategia::synapse0x11de8e40() {
   return (neuron0x11de8a28()*1.2431);
}
*/
