#ifndef CAVALLO_H
#define CAVALLO_H

#include <string>
#include <fstream>

using namespace std;

class Cavallo {
    public:
        Cavallo();
        virtual ~Cavallo();

        int indice() { return indice; };
        int eta() { return Score[0]; };
        int tratte() { return Score[1]; };
        int paliCorsi() { return Score[2]; };
        int paliVinti() { return Score[3]; };

        int scatto() { return Capacita[0]; };
        int velocita() { return Capacita[1]; };
        int precisione() { return Capacita[2]; };

	    float media();

        string getNome() { return Nome; };
        int getColore() { return colore; };

        friend ostream& operator<<(ostream& out, Cavallo x);
        friend istream& operator>>(istream& in, Cavallo& x);

    private:
        string Nome;
        int indice;
        int colore;
        int Capacita[3];      // scatto(ripresa), velocita(v max), precisione(capacita` di infilarsi nei pertugi)
        int Score[4];         // anni, tratte, palii corsi, palii vinti
};

#endif
