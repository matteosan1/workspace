#include "GiocatoriList.h"

#include <QColor>
#include <QFont>

//#include <iostream>

int GiocatoriList::columnCount(const QModelIndex &parent) const {
    if (!toggle)
        return giornate;
    else
        return 8;
}

int GiocatoriList::rowCount(const QModelIndex &parent) const {

    if (!toggle) {
        int rows = (int)giocatori.size() + 2;
        return rows;
    }
    else
        return giocatori.size();
}

QVariant GiocatoriList::data(const QModelIndex &index, int role) const {

    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
        return int(Qt::AlignHCenter | Qt::AlignVCenter);

    if ((unsigned int)index.row() < giocatori.size()) {
        Giocatore temp = giocatori[index.row()];

        if (role == Qt::FontRole) {
            if (!temp.GetPartita(index.column()).HaGiocato() && (!toggle))
                return QFont("Sans Serif", 8);
            else
                return QFont("Sans Serif", 12, QFont::Bold);
        }

        if (!toggle) {
            if (role == Qt::ForegroundRole) {
                if (temp.GetPartita(index.column()).isGoal())
                    return QColor(Qt::darkRed);
            }

            if (role == Qt::BackgroundRole) {
                if (temp.GetPartita(index.column()).isAmmonizione())
                    return QColor(Qt::yellow);
                if (temp.GetPartita(index.column()).isEspulsione())
                    return QColor(Qt::red);
            }
        }
    }

    if (role == Qt::DisplayRole) {
        if ((unsigned int)index.row() < giocatori.size()) {
            Giocatore temp = giocatori[index.row()];

            if (!toggle) {

                float voto = temp.GetVoto(index.column(), p);
                if (temp.GetPartita(index.column()).GetVoto() != 0)
                    return QString("%1").arg(voto);
                else
                    return QString("");
                } else {
                    switch(index.column()) {
                        case 0:
                            if (temp.GetMedia(p) != 0)
                                return QString("%1").arg(temp.GetMedia(p), 0, 'f', 2);
                            else
                                return "-";
                            break;
                        case 1:
                            return temp.GetGiocate();
                            break;
                        case 2:
                            return temp.GetPresenze();
                            break;
                        case 3:
                            return temp.GetAmmonizioni();
                            break;
                        case 4:
                            return temp.GetEspulsioni();
                            break;
                        case 5:
                            return temp.GetGoal();
                            break;
                        case 6:
                            return temp.GetAutogoal();
                            break;
                        case 7:
                            return temp.GetRigori();
                            break;
                        default:
                            return QVariant();
                            break;
                    }
                }
          }

          if ((unsigned int)index.row() == giocatori.size())
            return schemaPerGiornata(index.column());
          if ((unsigned int)index.row() == giocatori.size()+1)
              return QString("%1").arg(votoPerGiornata(index.column()), 0, 'f', 1);
     }

     return QVariant();
}

QVariant GiocatoriList::headerData(int section, Qt::Orientation orientation,
				   int role) const {

    QStringList legenda;
    legenda << "Media" << "Giocate" << "Presenze" << "Ammonizioni"
            << "Espulsioni" << "Goal" << "Autogoal" << "Rigori";

    Giocatore temp;
    if (section < giocatori.size()) {
        temp = giocatori[section];
        if (role == Qt::BackgroundRole && orientation == Qt::Vertical)  {
            if (temp.GetRuolo() == 0)
                return QColor(Qt::green);
            if (temp.GetRuolo() == 1)
                return QColor(Qt::cyan);
            if (temp.GetRuolo() == 2)
                return QColor(Qt::gray);
            if (temp.GetRuolo() == 3)
                return QColor(Qt::blue);
            if (temp.GetRuolo() > 4)
                return QColor(Qt::magenta);
        }
    }

    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        if (!toggle)
            return QString("Giornata %1").arg(section+1);
        else
            return legenda[section];
    } else {
        if (!toggle) {
            if ((unsigned int)section == giocatori.size())
                return QString("SCHEMA");

            if ((unsigned int)section == giocatori.size()+1)
                return QString("PUNTEGGI");
        }
        if ((unsigned int)section < giocatori.size()) {
            temp = giocatori[section];
            return temp.GetNomeCompleto();
        }
    }

    return QVariant();
}

float GiocatoriList::votoPerGiornata(int g) const {

    float result = 0;
    vector<Giocatore>::const_iterator it;
    for(it = giocatori.begin(); it != giocatori.end(); ++it) {
        Giocatore temp = *it;
        if (temp.GetPartita(g).HaGiocato())
            result += temp.GetVoto(g, p);
    }
    //std::cout << result << std::endl;
    return result;
}

QString GiocatoriList::schemaPerGiornata(int g) const {

    int attaccanti = 0, difensori = 0, centrocampisti = 0, giocano = 0, portieri = 0;
    QString result;
    vector<Giocatore>::const_iterator it;

    for(it = giocatori.begin(); it != giocatori.end(); ++it) {
        Giocatore temp = *it;
        if (temp.GetPartita(g).Formazione() == 1) {
            if (temp.GetRuolo()%5 == 0)
                portieri++;
            if (temp.GetRuolo()%5 == 1)
                difensori++;
            if (temp.GetRuolo()%5 == 2)
                centrocampisti++;
            if (temp.GetRuolo()%5 == 3)
                attaccanti++;
        }
        if (temp.GetPartita(g).HaGiocato() == 1)
            giocano++;
    }

    // TODO mettere la protezione per modulo illegale
    if (giocano == 11)
        result = QString("%1-%2-%3").arg(difensori).arg(centrocampisti).arg(attaccanti);
    else
        result = QString("<11");

    return result;
}
