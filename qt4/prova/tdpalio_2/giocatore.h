#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <string>
#include <fstream>

using namespace std;

class Giocatore
{
    public:
        Giocatore();
        virtual ~Giocatore();
        
        void setNome(string n) { Nome = n; };
        void setCognome(string n) { Cognome = n; };
        void setContrada(int a) { Contrada = a; };

        string nome() { return Nome; };
        string cognome() { return Cognome; };
        string nomeCompleto() { return Nome + " " + Cognome; };
        
        int contrada() { return Contrada; };
        int tempo() { return Tempo_in_carica; };
        int corsi() { return Score[0]; };
        int vittorie() { return Score[1]; };

        friend ostream& operator<<(ostream& out, Giocatore x);
        friend istream& operator>>(istream& in, Giocatore& x);

    private:
        string Nome, Cognome;
        int Contrada;
        int Tempo_in_carica;
        int Score[2];
};
#endif
