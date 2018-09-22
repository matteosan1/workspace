#include "punteggi.h"

Punteggi::Punteggi() {

    n_portieri = 0;
    n_difensori = 0;
    n_centrocampisti = 0;
    n_attaccanti = 0;
    auto_portiere = 0;
    sv_portiere = 0;
    sei_politico = 0;
    for(int i=0; i<10; ++i)
        reti[i] = 0;
//    for(int i=0; i<9; ++i)
//        schemi[i] = 0;
    gsu = 0;
    rp = 0;
    rsb = 0;
    gse = 0;
    as = 0;
    am = 0;
    es = 0;
    rse = 0;
    au = 0;
}

Punteggi::~Punteggi()
{}

QTextStream& operator>>(QTextStream& in, Punteggi& x) {

    in >> x.n_portieri >> x.n_difensori >> x.n_centrocampisti >> x.n_attaccanti;
    in >> x.auto_portiere >> x.sv_portiere >> x.sei_politico;
    in >> x.gsu >> x.rp >> x.rsb >> x.gse >> x.as >> x.am >> x.es >> x.rse >> x.au;
    for(int i=0; i<10; ++i)
        in >> x.reti[i];

    int schema;
    for (int i=0; i<9; i++)
    {
        in >> schema;
        x.m_schemi.append(i);
    }

    return in;
}

QTextStream& operator<<(QTextStream& out, Punteggi x) {

    out << x.n_portieri << " " << x.n_difensori
        << " " << x.n_centrocampisti << " " << x.n_attaccanti << "\n";
    out << x.auto_portiere << " " << x.sv_portiere << " " << x.sei_politico  << "\n";
    out << x.gsu << " " << x.rp << " " << x.rsb << " " << x.gse
        << " " << x.as << " " << x.am << " "
        << x.es << " " << x.rse << " " << x.au << "\n";

    for (int i=0; i<10; ++i)
        out << x.reti[i] << " ";

    out << "\n";

    for (int i=0; i<9; ++i)
        out << x.m_schemi[i] << " ";
    out << "\n";

    return out;
}
