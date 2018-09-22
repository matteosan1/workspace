#include <QCoreApplication>
#include <main.h>

#include <QFile>

int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);

    ran = new TRandom(1001);
    mese = Luglio;
    fase = eEstrazione;
    nProva = 0;
    contrade.resize(17);
    fantini.resize(16);
    cavalli.resize(21);
    barberi.resize(10);

    QFile file("../setup.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("Errore irreversibile. TDPalio non riesce a trovare il file setup.dat.");
        abort();
    }

    QTextStream fin(&file);

    for(int i=0; i<17; ++i)
        fin >> contrade[i];
    for(int i=0; i<16; ++i)
        fin >> fantini[i];
    for(int i=0; i<21; ++i)
        fin >> cavalli[i];
    file.close();

    estrazione(0);

    int anno = 0;
    while(anno != 1) {
        //TODO controllare il seme casuale
        // estrazione
        switch(mese) {
            case Luglio:
                for(int i=0; i<10; i++)
                    barberi[i].setContrada(&contrade[luglio[i]]);
                break;
            case Agosto:
                for(int i=0; i<10; i++)
                    barberi[i].setContrada(&contrade[agosto[i]]);
                break;
            case Straordinario:
                for(int i=0; i<10; i++)
                    barberi[i].setContrada(&contrade[settembre[i]]);
                break;
        }
        //TODO controllare che i cavalli vengano scelti in modo giusto
        //TODO in pratica che corrano di piu` i piu` bravi
        // scelta dei cavalli e tratta
        formaCavalli();
        SceltaCavalli();
        //TODO controllare che la scelta della strategia sia corretta
        SceltaStrategia();

        for(; nProva<6; nProva++) {
            if (nProva == 0) {
                // FIXME Prima scelta del fantino (tutte le contrade devono avere un fantino prima di ogni prova
                SceltaFantino();
            }

            Prove();
            InserisciPartito();
            SceltaFantino();
        }

        Segnatura();
        // corsa

        anno++;
    }

    qDebug("Hello from Qt 4!");
    return 0;
}

