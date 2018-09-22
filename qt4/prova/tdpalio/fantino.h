#ifndef FANTINO_H
#define FANTINO_H

#include <QVector>
#include <QString>
#include <QTextStream>

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
        // questo non viene usato per ora
        void creaFantino(int a0, QString a, int b, int c, int d, int e, int f, Offerta* g);
        void creaFantino(int a0, QString a, int b, int c, int d, int e);

        int indice() { return index; };
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

        QString getNome() { return Nome; };

        unsigned int nOfferte() { return offerte.size(); };
        void setOfferta(int a, int b, int c, int d);
        Offerta getOfferta(int i) { return offerte[i]; };
        QVector<Offerta> getOfferte() { return offerte; };
        void clearOfferte(int i, int j=-1);

        friend QTextStream& operator<<(QTextStream& out, Fantino x);
        friend QTextStream& operator>>(QTextStream& in, Fantino& x);

    private:
        int index;
        QString Nome;
        int Capacita[3];       // prontezza, determinazione, bravura
        int Score[4];          // anni, palii corsi, palii vinti
        int Feeling[17];
        int contrada;
        int nOff;
        QVector<Offerta> offerte;
};

#endif
