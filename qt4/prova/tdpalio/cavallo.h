#ifndef CAVALLO_H
#define CAVALLO_H

#include <QString>
#include <QTextStream>

using namespace std;

class Cavallo {
    public:
        Cavallo();
        virtual ~Cavallo();

        int indice() { return index; };
        int eta() { return Score[0]; };
        int tratte() { return Score[1]; };
        int paliCorsi() { return Score[2]; };
        int paliVinti() { return Score[3]; };

        int scatto() { return Capacita[0]; };
        int velocita() { return Capacita[1]; };
        int precisione() { return Capacita[2]; };

	    float media();

        QString getNome() { return Nome; };
        int getColore() { return colore; };

        friend QTextStream& operator<<(QTextStream& out, Cavallo x);
        friend QTextStream& operator>>(QTextStream& in, Cavallo& x);

    private:
        int index;
        QString Nome;
        int colore;
        int Capacita[3];      // scatto(ripresa), velocita(v max), precisione(capacita` di infilarsi nei pertugi)
        int Score[4];         // anni, tratte, palii corsi, palii vinti
};

#endif
