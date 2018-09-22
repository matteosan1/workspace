#ifndef FANTINO_H
#define FANTINO_H

#include <QVector>
#include <QString>
#include <QTextStream>
#include <QDataStream>

using namespace std;

class Offerta {
    public:
        Offerta();
        virtual ~Offerta();

        void setOfferta(int a, int b, int c, int d);

        int chi() { return chi_; };
        int controChi() { return controchi_; };
        int aVincere() { return avincere_; };
        int aPerdere() { return aperdere_; };
	void setCoefficiente(float a) { coefficiente_ = a; };
	float coefficiente() { return coefficiente_; };

        friend QDataStream& operator<<(QDataStream& out, Offerta x);
        friend QTextStream& operator<<(QTextStream& out, Offerta x);
        friend QDataStream& operator>>(QDataStream& in, Offerta& x);	

    private:
        int chi_;
        int controchi_;
        int avincere_;
        int aperdere_;
	float coefficiente_;
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
	int killer() { return Capacita[3]; };
	
	float media() { return (float)(Capacita[0]+Capacita[1]+Capacita[2])/(float)3; };
	QVector<int> caratteristiche();

        int feeling(int i) { return Feeling[i]; };
        int correper() { return contrada; };
        void setContrada(int i) { contrada = i; };

        QString getNome() { return Nome; };

	void setInfortunio(int i) { infortunio_ = i; };

        unsigned int nOfferte() { return offerte.size(); };
        void setOfferta(int a, int b, int c, int d);
	void setOfferta(Offerta a) { offerte.push_back(a); };
        Offerta getOfferta(int i) { return offerte[i]; };
        QVector<Offerta> getOfferte() { return offerte; };
        void clearOfferte(int i, int j=-1);

        friend QDataStream& operator<<(QDataStream& out, Fantino x);
        friend QTextStream& operator<<(QTextStream& out, Fantino x);
        friend QTextStream& operator>>(QTextStream& in, Fantino& x);
        friend QDataStream& operator>>(QDataStream& in, Fantino& x);

    private:
        int index;
        QString Nome;
        int Capacita[4];       // prontezza, determinazione, bravura, killer
        int Score[4];          // anni, palii corsi, palii vinti
        int Feeling[17];
        int contrada;
        int nOff;
	int infortunio_;
        QVector<Offerta> offerte;
};

#endif
