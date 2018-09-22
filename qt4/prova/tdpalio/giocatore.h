#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <QString>
#include <QTextStream>

using namespace std;
//FIXME da ogni classe "base" togliere namespace std;
class Giocatore
{
    public:
        Giocatore();
        virtual ~Giocatore();

        void setNome(QString n) { Nome = n; };
        void setCognome(QString n) { Cognome = n; };
        void setContrada(int a) { Contrada = a; };

        QString nome() { return Nome; };
        QString cognome() { return Cognome; };
        QString nomeCompleto() { return Nome + " " + Cognome; };

        int contrada() { return Contrada; };
        int tempo() { return Tempo_in_carica; };
        int corsi() { return Score[0]; };
        int vittorie() { return Score[1]; };

        friend QTextStream& operator<<(QTextStream& out, Giocatore x);
        friend QTextStream& operator>>(QTextStream& in, Giocatore& x);

    private:
        QString Nome, Cognome;
        int Contrada;
        int Tempo_in_carica;
        int Score[2];
};
#endif
