#ifndef PARTITO_H
#define PARTITO_H

//#include <QTextStream>
//#include <QDataStream>

namespace common {

class Partito {

    enum TipoPartito
    {
        AndarePiano = 1,
        FareSpazioAlCanape,
        Killeraggio,
        DareLaMossa,
        Salva
    };

public:
    Partito();
    ~Partito();

    int contrada() const { return m_contrada; }
    int chiFermi() const { return m_chifermi; }
    int tipo() const { return m_tipo; }
    int premio() const { return m_soldi; }

    bool fatto() const { return m_eseguito; }
    //bool accettato() { return eseguito==1; };

    //void setAccettato() { eseguito = 1; };
    void setFatto() { m_eseguito = true; }
    void setPartito(int a, int b, int c);
    void setPartito(int a, int b, int c, int d);

//    friend QTextStream& operator<<(QTextStream& out, Partito x);
//    friend QDataStream& operator<<(QDataStream& out, Partito x);
//    friend QDataStream& operator>>(QDataStream& in, Partito& x);
//    friend QTextStream& operator>>(QTextStream& in, Partito& x);

private:
    int m_contrada;
    int m_chifermi;
    TipoPartito m_tipo;
    int m_soldi;
    bool m_eseguito;
};

} // common
#endif
