#include "formtipo.h"

#include <iostream>

FormTipo::FormTipo(QList<Giocatore*> g, QWidget *parent,  Punteggi* p)
    : QDialog(parent), giocatori(g), punt(p) {

    ui.setupUi(this);

    scene = new QGraphicsScene(parent);

    ui.graphicsView->setScene(scene);
    ui.graphicsView->show();
    setCampo();

    list << "6-3-1" << "5-4-1" << "5-3-2" << "4-5-1"
            << "4-4-2" << "4-3-3" << "3-5-2" << "3-6-1" << "3-4-3";

    for(int i=0; i<9; ++i)
        if (punt->m_schemi[i] == 0)
            list.removeAt(i);

    fillCombo();
    ordina();
    connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFormazione(int)));
}

void FormTipo::changeFormazione(int a) {

    QStringList l = list[a].split("-");

    for(int j=0; j<3; ++j) {
        n[j] = l[j].toInt();
        for(int i=0; i<n[j]; ++i)
            nomi << pairs[j][i].first;
    }
}

void FormTipo::ordina() {
    QPair<QString, float> temp;

    for(int j=0; j<3; ++j) {
        for(unsigned int i=0; i<giocatori->size(); ++i)
            if (giocatori[i]->GetRuolo() == j+1) {
                temp.first = giocatori[i]->GetCognome();
                temp.second = giocatori[i]->GetMedia(punt);
                pairs[j].push_back(temp);
            }
    }

    // cambiare ordinamento in base anche al numero di partite giocate
    for(int j=0; j<3; ++j) {
        for(int i=0; i<pairs[j].size()-1; ++i) {
            for(int y=i+1; y<pairs[j].size(); ++y) {
                if (pairs[j][i].second < pairs[j][y].second)
                    pairs[j].swap(i, y);
            }
        }
    }
}

void FormTipo::fillCombo() {
    ui.comboBox->insertItems(0, list);
}

void FormTipo::setScene() {
    scene->addText("Matteo");
    scene->addText("Matteo");
    //
    scene->addText("Matteo");
    //
    scene->addText("Matteo");
    //
    scene->addText("Matteo");
    //
    scene->addText("Matteo");
    //
    scene->addText("Matteo");
    //
    scene->addText("Matteo");
    //
    scene->addText("Matteo");
    //
//    1

//  1 1 1  (2)
// 1 1 1 1 (2)
//   1 1   (1)

//   1 1   (1)
//  1 1 1  (2)
// 1 1 1 1 (2)

//   1   (1)
//  1 1  (2)
}

void FormTipo::setCampo() {

    scene->setBackgroundBrush(Qt::green);
    //scene->addLine();
    //scene->addCircle();
    //scene->addLine();
    //scene->addLine();
    //scene->addLine();
}
