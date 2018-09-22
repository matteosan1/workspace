#include "fantino.h"

Fantino::Fantino() {
    /*
    Nome = "";
    for(int i=0; i<3; i++) {
        Capacita[i] = 0;
        Score[i] = 0;
    }

    for(int i=0; i<17; i++)
        Feeling[i] = 6;

    contrada = -1;
    */
}

Fantino::~Fantino() {}

Offerta::~Offerta() {}

Offerta::Offerta() {}

void Offerta::setOfferta(int a, int b, int c, int d) {

    chi = a;
    controchi = b;
    avincere = c;
    aperdere = d;
}

void Fantino::clearOfferte(int i , int j) {

    vector<Offerta> newVector;
    for(int k=0; k<(int)offerte.size(); ++k)
        if ((k==i) || (k==j))
            newVector.push_back(offerte[k]);

    offerte = newVector;
}

void Fantino::setOfferta(int a, int b, int c, int d) {

    Offerta o;
    o.setOfferta(a, b, c, d);
    offerte.push_back(o);
}

void Fantino::creaFantino(int a0, string a, int b, int c, int d, int e, int f, Offerta* g) {

    Nome = a;
    indice = a0;
    Capacita[0] = b;
    Capacita[1] = c;
    Capacita[2] = d;
    for(int i=0; i<4; i++)
        Score[i] = 0;

    for(int i=0; i<17; i++)
        Feeling[i] = 0;

    contrada = e;
    nOff = f;
    for(int i=0; i<18; i++)
        offerte[i] = *(g+i);
}

void Fantino::setPiazza(int i) {

    if ((i<5) && (i>1))
        Score[3] += 100;
    if (i>4)
        Score[3] += 1;
}

int Fantino::prezzo() {
    int prezzo = 20;
    if ((paliCorsi() != 0) && (paliCorsi() < 5))
        prezzo += 10 * paliCorsi();

    int secondi = (int)(piazzamenti()/100);
    int ultimi = piazzamenti()-secondi*100;

    if (eta() < 11) {
        prezzo += 20 * secondi;
        prezzo -= 10 * ultimi;
    } else {
        prezzo -= 10 * secondi;
        prezzo -= 20 * ultimi;
    }
    prezzo += paliVinti() * 50;

    if ((paliCorsi() > 4) && (prezzo < 60))
        prezzo = 50;

    return prezzo;
}

ostream& operator<<(ostream& out, Fantino x)
{
    string s = x.Nome;
    for(unsigned int i=0; i<s.length(); i++) {
        if (s.substr(i,1) == " ")
            s.replace(i,1,"_");
    }

	out << s << "\n";
    out << x.indice << " ";
    for(int i=0; i<3; i++)
        out << x.Capacita[i] << " ";
    for(int i=0; i<4; i++)
        out << x.Score[i] << " ";
    for(int i=0; i<17; i++)
        out << x.Feeling[i] << " ";
    out << x.contrada << "\n";

    return out;
}

istream& operator>>(istream& in, Fantino& x)
{
    string s;
    in >> s;
    for(unsigned int i=0; i<s.length(); i++) {
        if (s.substr(i,1) == "_")
            s.replace(i,1," ");
    }

    in >> x.indice;
    for(int i=0; i<3; i++)
        in >> x.Capacita[i];
    for(int i=0; i<4; i++)
        in >> x.Score[i];
    for(int i=0; i<17; i++)
        in >> x.Feeling[i];
    in >> x.contrada;

    x.Nome = s;
    return in;
}

