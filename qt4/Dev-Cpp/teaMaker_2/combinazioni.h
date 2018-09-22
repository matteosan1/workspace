#ifndef _COMBINAZIONI_
#define _COMBINAZIONI_

using namespace std;

class Combinazioni
{
    public:
        Combinazioni(int, int);
        virtual ~Combinazioni();
        int cardCombset();
        void GetComb(int* v);
        void rank2comb(int rank);
        void nextComb();
        void Print();
        
    private:
	    int n, k;
	    int C[22][22];
	    int comb[22], comb2[22];
};
#endif 

