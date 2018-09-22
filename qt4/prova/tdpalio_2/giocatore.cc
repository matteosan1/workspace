#include "giocatore.h"

Giocatore::Giocatore() {
    Nome = "";
    Cognome = "";
    Contrada = -1;
    Tempo_in_carica = 0;
    Score[0] = 0;
    Score[1] = 0;
}

Giocatore::~Giocatore()
{}

ostream& operator<<(ostream& out, Giocatore x) {
	  
    out << x.Nome << " ";
    out << x.Cognome << " ";
    out << x.Contrada << " ";
    out << x.Tempo_in_carica << " ";
       
    for(int i=0; i<2; i++)
        out << x.Score[i] << " ";
    out << '\n';
    
    return out;
}

istream& operator>>(istream& in, Giocatore& x) {
        
    in >> x.Nome;
    in >> x.Cognome;
    in >> x.Contrada;
    in >> x.Tempo_in_carica;
       
    for(int i=0; i<2; i++)
        in >> x.Score[i];

    return in;
}
