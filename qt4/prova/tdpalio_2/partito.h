#ifndef PARTITO_H
#define PARTITO_H

using namespace std;

class Partito {
    public:
        Partito();
        virtual ~Partito();

        int getContrada() { return contrada; };
        int getFermata() { return contrada2; };
        int getTipo() { return tipo; };
        int getPremio() { return soldi; };
        bool fatto() { return eseguito; };

        void setFatto() { eseguito = true; };
        void setPartito(int a, int b, int c);
        void setPartito(int a, int b, int c, int d);

    private:
        int contrada;
        int contrada2;
        int tipo;
        int soldi;
        bool eseguito;
};

#endif
