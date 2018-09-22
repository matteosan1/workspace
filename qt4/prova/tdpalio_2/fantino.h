#ifndef FANTINO_H
#define FANTINO_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Offerta {
    public:
        Offerta();
        virtual ~Offerta();

        void setOfferta(int a, int b, int c, int d);

        int getChi() { return chi; };
        int getControChi() { return controchi; };
        int getAVincere() { return avincere; };
        int getAPerdere() { return aperdere; };

    private:
        int chi;
        int controchi;
        int avincere;
        int aperdere;
};

class Fantino {
    public:
        Fantino();
        virtual ~Fantino();

        void creaFantino(string a, int b, int c, int d, int e, int f, Offerta* g);

        int indice() { return indice; };
        int eta() { return Score[0]; };
        int paliCorsi() { return Score[1]; };
        int paliVinti() { return Score[2]; };
        int piazzamenti() { return Score[3]; };
        void setPiazza(int i);

        int prezzo();
        int prontezza() { return Capacita[0]; };
        int determinazione() { return Capacita[1]; };
        int bravura() { return Capacita[2]; };

        int feeling(int i) { return Feeling[i]; };
        int correper() { return contrada; };
        void setContrada(int i) { contrada = i; };

        string getNome() { return Nome; };

        unsigned int nOfferte() { return offerte.size(); };
        void setOfferta(int a, int b, int c, int d);
        Offerta getOfferta(int i) { return offerte[i]; };
        vector<Offerta> getOfferte() { return offerte; };
        void clearOfferte(int i, int j=-1);

        friend ostream& operator<<(ostream& out, Fantino x);
        friend istream& operator>>(istream& in, Fantino& x);

    private:
        int indice;
        string Nome;
        int Capacita[3];       // prontezza, determinazione, bravura
        int Score[4];          // anni, palii corsi, palii vinti
        int Feeling[17];
        int contrada;
        int nOff;
        vector<Offerta> offerte;
};

#endif
