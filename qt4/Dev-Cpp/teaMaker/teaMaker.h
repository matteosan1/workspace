#ifndef teaMaker_h
int C[22][22];
int cardCombset(int n, int k);
void rank2comb(int rank, int* comb, int ncomb, int n, int m);
void nextComb(int* combA, int* combB, int n, int m);
float chiSquare(int* comb, int n, int m, float* chi, float chitot);
#endif
