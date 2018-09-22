#include "formdialog.h"


// todo
// cambiare ruoli dei giocatori
// variare la lista dei giocatori disponibili via via che la formazione viene fatta
// gestire l'invio via mail della formazione
// rimuovere la parte vecchia
// gestione panchina
// aggiungere nuovi moduli
// aggiungere capitano

FormDialog::FormDialog(QList<Giocatore*> giocatori,
                       Punteggi* punteggi,
                       int partite,
                       QWidget *parent) : QDialog(parent),
    m_giocatori(giocatori),
    m_punteggi(punteggi),
    m_partite(partite) {

    m_ui.setupUi(this);

    m_giornata = -1;

    // TODO FIXME MOVE TO
    m_modules << "6-3-1" << "5-4-1" << "5-3-2" << "4-5-1"
           << "4-4-2" << "4-3-3" << "3-5-2" << "3-6-1" << "3-4-3";

    for (int i=0; i<9; i++)
    {
        if (m_punteggi->m_schemi[i] != 0)
            m_ui.comboBoxModulo->addItem(m_modules[i]);
    }

    connect(m_ui.comboBoxModulo, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePlayers(int)));

    foreach (Giocatore* g, m_giocatori)
    {
        QString nome = g->GetNomeCompleto().toUpper();

        if (g->GetRuolo() == 0)
            m_ui.comboPortieri->addItem(nome);
        if (g->GetRuolo() == 1)
            m_ui.comboDifensori->addItem(nome);
        if (g->GetRuolo() == 2)
            m_ui.comboCentrocampisti->addItem(nome);
        if (g->GetRuolo() == 3)
            m_ui.comboAttaccanti->addItem(nome);
    }

    if (m_partite != -1) {
        m_ui.giornataCombo->setEnabled(true);

        QStringList list;
        list << QString("Nuova Giornata");
        for(int i=0; i<partite; ++i)
            list << QString("Giornata %1").arg(i+1);
        m_ui.giornataCombo->insertItems(0, list);
        connect(m_ui.giornataCombo, SIGNAL(activated(int)), this, SLOT(setGiornata(int)));
    }

    connect(m_ui.textFormazione, SIGNAL(textChanged()), this, SLOT(checkModulo()));

}

void FormDialog::updatePlayers(const int& chosenModule)
{
    disableAllCombo();
    enableCombo(m_ui.comboBoxPortiere, 0);

    switch(chosenModule)
    {
    case 0:
        break;
    case 1: // 5-4-1
        enableCombo(m_ui.comboBoxDifensoreSx, 1);
        enableCombo(m_ui.comboBoxDifensoreDx, 1);
        enableCombo(m_ui.comboBoxDifensoreCx1, 1);
        enableCombo(m_ui.comboBoxDifensoreCx2, 1);
        enableCombo(m_ui.comboBoxDifensoreCx3, 1);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, 2);
        enableCombo(m_ui.comboBoxCentrocampistaSx, 2);
        enableCombo(m_ui.comboBoxCentrocampistaDx, 2);
        enableCombo(m_ui.comboBoxAttaccanteCx, 3);
        break;
    case 2: // 5-3-2
        enableCombo(m_ui.comboBoxDifensoreSx, 1);
        enableCombo(m_ui.comboBoxDifensoreDx, 1);
        enableCombo(m_ui.comboBoxDifensoreCx1, 1);
        enableCombo(m_ui.comboBoxDifensoreCx2, 1);
        enableCombo(m_ui.comboBoxDifensoreCx3, 1);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, 2);
        enableCombo(m_ui.comboBoxAttaccanteSx, 2);
        enableCombo(m_ui.comboBoxAttaccanteDx, 3);
        break;
    case 3: // 4-5-1
        enableCombo(m_ui.comboBoxDifensoreSx, 1);
        enableCombo(m_ui.comboBoxDifensoreDx, 1);
        enableCombo(m_ui.comboBoxDifensoreCx1, 1);
        enableCombo(m_ui.comboBoxDifensoreCx2, 1);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, 2);
        enableCombo(m_ui.comboBoxCentrocampistaSx, 2);
        enableCombo(m_ui.comboBoxCentrocampistaDx, 2);
        enableCombo(m_ui.comboBoxAttaccanteCx, 3);
        break;
    case 4: // 4-4-2
        enableCombo(m_ui.comboBoxDifensoreSx, 1);
        enableCombo(m_ui.comboBoxDifensoreDx, 1);
        enableCombo(m_ui.comboBoxDifensoreCx1, 1);
        enableCombo(m_ui.comboBoxDifensoreCx2, 1);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, 2);
        enableCombo(m_ui.comboBoxCentrocampistaSx, 2);
        enableCombo(m_ui.comboBoxCentrocampistaDx, 2);
        enableCombo(m_ui.comboBoxAttaccanteDx, 3);
        enableCombo(m_ui.comboBoxAttaccanteSx, 3);
        break;
    case 5: // 4-3-3
        enableCombo(m_ui.comboBoxDifensoreSx, 1);
        enableCombo(m_ui.comboBoxDifensoreDx, 1);
        enableCombo(m_ui.comboBoxDifensoreCx1, 1);
        enableCombo(m_ui.comboBoxDifensoreCx2, 1);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, 2);
        enableCombo(m_ui.comboBoxAttaccanteCx, 3);
        enableCombo(m_ui.comboBoxAttaccanteDx, 3);
        enableCombo(m_ui.comboBoxAttaccanteSx, 3);
        break;
    case 6: // 3-5-2
        enableCombo(m_ui.comboBoxDifensoreCx1, 1);
        enableCombo(m_ui.comboBoxDifensoreCx2, 1);
        enableCombo(m_ui.comboBoxDifensoreCx3, 1);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, 2);
        enableCombo(m_ui.comboBoxCentrocampistaSx, 2);
        enableCombo(m_ui.comboBoxCentrocampistaDx, 2);
        enableCombo(m_ui.comboBoxAttaccanteSx, 3);
        enableCombo(m_ui.comboBoxAttaccanteDx, 3);
        break;
    case 7: // 3-6-1
        break;
    case 8: // 3-4-3
        enableCombo(m_ui.comboBoxDifensoreCx1, 1);
        enableCombo(m_ui.comboBoxDifensoreCx2, 1);
        enableCombo(m_ui.comboBoxDifensoreCx3, 1);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, 2);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, 2);
        enableCombo(m_ui.comboBoxCentrocampistaSx, 2);
        enableCombo(m_ui.comboBoxCentrocampistaDx, 2);
        enableCombo(m_ui.comboBoxAttaccanteCx, 3);
        enableCombo(m_ui.comboBoxAttaccanteSx, 3);
        enableCombo(m_ui.comboBoxAttaccanteDx, 3);
        break;
    }
}

void FormDialog::enableCombo(QComboBox* combo, int ruolo)
{
    combo->setEnabled(true);
    combo->setVisible(true);
    foreach (Giocatore* g, m_giocatori)
    {
        if (g->GetRuolo() == ruolo)
            combo->addItem(g->GetNomeCompleto());
    }
}

void FormDialog::disableAllCombo()
{
    m_ui.comboBoxPortiere->setEnabled(false);
    m_ui.comboBoxDifensoreSx->setEnabled(false);
    m_ui.comboBoxDifensoreDx->setEnabled(false);
    m_ui.comboBoxDifensoreCx1->setEnabled(false);
    m_ui.comboBoxDifensoreCx2->setEnabled(false);
    m_ui.comboBoxDifensoreCx3->setEnabled(false);
    m_ui.comboBoxCentrocampistaCx1->setEnabled(false);
    m_ui.comboBoxCentrocampistaCx2->setEnabled(false);
    m_ui.comboBoxCentrocampistaCx3->setEnabled(false);
    m_ui.comboBoxCentrocampistaSx->setEnabled(false);
    m_ui.comboBoxCentrocampistaDx->setEnabled(false);
    m_ui.comboBoxAttaccanteCx->setEnabled(false);
    m_ui.comboBoxAttaccanteDx->setEnabled(false);
    m_ui.comboBoxAttaccanteSx->setEnabled(false);

    m_ui.comboBoxPortiere->setVisible(false);
    m_ui.comboBoxDifensoreSx->setVisible(false);
    m_ui.comboBoxDifensoreDx->setVisible(false);
    m_ui.comboBoxDifensoreCx1->setVisible(false);
    m_ui.comboBoxDifensoreCx2->setVisible(false);
    m_ui.comboBoxDifensoreCx3->setVisible(false);
    m_ui.comboBoxCentrocampistaCx1->setVisible(false);
    m_ui.comboBoxCentrocampistaCx2->setVisible(false);
    m_ui.comboBoxCentrocampistaCx3->setVisible(false);
    m_ui.comboBoxCentrocampistaSx->setVisible(false);
    m_ui.comboBoxCentrocampistaDx->setVisible(false);
    m_ui.comboBoxAttaccanteCx->setVisible(false);
    m_ui.comboBoxAttaccanteDx->setVisible(false);
    m_ui.comboBoxAttaccanteSx->setVisible(false);
}

void FormDialog::checkModulo() {
    int po = 0, di = 0, ce = 0, at = 0;

    QString s = m_ui.textFormazione->toPlainText();
    QStringList sL = s.split("\n");
    unsigned int limit;
    if (sL.size() > 10)
        limit = 11;
    else
        limit = sL.size();

    for(unsigned int i=0; i<limit; ++i) {
        foreach (Giocatore* it, m_giocatori)
        {
            if (sL[i] == it->GetNomeCompleto().toUpper()) {
                if (it->GetRuolo()%5 == 0)
                    po++;
                if (it->GetRuolo()%5 == 1)
                    di++;
                if (it->GetRuolo()%5 == 2)
                    ce++;
                if (it->GetRuolo()%5 == 3)
                    at++;
            }
        }
    }

    m_ui.labelPo->setText(QString("Portieri (%1)").arg(po));
    m_ui.labelDi->setText(QString("Difensori (%1)").arg(di));
    m_ui.labelCe->setText(QString("Centrocampisti (%1)").arg(ce));
    m_ui.labelAt->setText(QString("Attaccanti (%1)").arg(at));

    QStringList moduls;
    moduls << "6-3-1" << "5-4-1" << "5-3-2" << "4-5-1"
            << "4-4-2" << "4-3-3" << "3-5-2" << "3-6-1" << "3-4-3";

    for(int i=0; i<9; ++i) {
        if (m_punteggi->m_schemi[i] == 0)
            continue;

        QStringList l = moduls[i].split("-");
        if (limit < 11) {
            if ((po < 2) && (di < 6) && (ce < 6) && (at < 4)) {
                m_ui.buttonBox->setEnabled(true);
                return;
            }
        } else {
            if ((po == 1) && (di == l[0].toInt()) && (ce == l[1].toInt()) && (at == l[2].toInt())) {
                m_ui.buttonBox->setEnabled(true);
                return;
            }
        }
    }

    m_ui.buttonBox->setEnabled(false);
}

void FormDialog::setGiornata(int a) {
    QStringList lista1, lista2;
    vector<int> n1, n2;
    m_giornata = a;
    a -= 1;
    foreach(Giocatore* it, m_giocatori)
    {
        if (it->GetPartita(a).Formazione() == 1) {
            lista1 << it->GetNomeCompleto().toUpper();
            n1.push_back(it->GetRuolo()%5);
        }
    }

    foreach(Giocatore* it, m_giocatori)
    {
        if (it->GetPartita(a).Formazione() == 2) {
            lista2 << it->GetNomeCompleto().toUpper();
            n2.push_back(it->GetRuolo()%5);
        }
    }

    for(int i=0; i<lista1.size()-1; i++) {
        for(int j=i+1; j<lista1.size(); j++) {
            if (n1[i] > n1[j]) {
                QString l = lista1[i];
                lista1[i] = lista1[j];
                lista1[j] = l;
                int temp = n1[i];
                n1[i] = n1[j];
                n1[j] = temp;
            }
        }
    }

    for(int i=0; i<lista2.size()-1; i++) {
        for(int j=i+1; j<lista2.size(); j++) {
            if (n2[i] > n2[j]) {
                QString l = lista2[i];
                lista2[i] = lista2[j];
                lista2[j] = l;
                int temp = n2[i];
                n2[i] = n2[j];
                n2[j] = temp;
            }
        }
    }

    m_ui.textFormazione->clear();
    for(int i=0; i<lista1.size(); i++) {
        m_ui.textFormazione->insertPlainText(lista1[i]);
        m_ui.textFormazione->insertPlainText("\n");
    }
    for(int i=0; i<lista2.size(); i++) {
        m_ui.textFormazione->insertPlainText(lista2[i]);
        m_ui.textFormazione->insertPlainText("\n");
    }
}

QString FormDialog::readLines() {
    QString s = m_ui.textFormazione->toPlainText();
    return s;
}
