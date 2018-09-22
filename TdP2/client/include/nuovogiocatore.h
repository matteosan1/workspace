#ifndef NUOVOGIOCATORE_H
#define NUOVOGIOCATORE_H

#include "ui_nuovogiocatore.h"

#include "../tdpaliocommon/giocatore.h"

#include <QVector>

class NuovoGiocatoreDialog : public QDialog {
    Q_OBJECT

public:
    NuovoGiocatoreDialog(QWidget* parent = 0);
    ~NuovoGiocatoreDialog();

    Giocatore getGiocatore();

public slots:
    void enableCombo(int state);
    void accept();
    void setContrade(QStringList lista, QVector<int> index);
    int assegnaContrada();

private:
    QVector<int> indice;
    Giocatore g;

    Ui::NuovoGiocatore ui;
};
#endif // NUOVOGIOCATORE_H
