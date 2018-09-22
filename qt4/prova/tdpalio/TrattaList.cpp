#include "TrattaList.h"

//#include <QColor>
//#include <QFont>

#include <QStringList>

//#include <iostream>

int TrattaList::columnCount(const QModelIndex &parent) const {
    return 4;
}

int TrattaList::rowCount(const QModelIndex &parent) const {
    return cavalli->size();
}

QVariant TrattaList::data(const QModelIndex &index, int role) const {

    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
        return int(Qt::AlignHCenter | Qt::AlignVCenter);

    //if ((unsigned int)index.row() < giocatori.size()) {
    //    Giocatore temp = giocatori[index.row()];
/*
    if (role == Qt::FontRole) {
       if (!temp.GetPartita(index.column()).HaGiocato() && (!toggle))
                return QFont("Sans Serif", 8);
            else
                return QFont("Sans Serif", 12, QFont::Bold);
        }

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
*/
    if (role == Qt::DisplayRole) {
        switch(index.column()) {
            case 0:
                return QString("%1").arg((*cavalli)[index.row()].paliCorsi());
                break;
            case 1:
                return QString("%1").arg((*cavalli)[index.row()].paliVinti());
                break;
            case 2:
                return QString("%1").arg((*cavalli)[index.row()].media(), 0, 'f', 2);
                break;
            case 3:
                return selezione[index.row()];//temp.GetAmmonizioni();
                break;
            default:
                return QVariant();
                break;
        }
     }

     return QVariant();
}

Qt::ItemFlags TrattaList::flags(const QModelIndex &index) const {

    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


QVariant TrattaList::headerData(int section, Qt::Orientation orientation,
				   int role) const {

    QStringList legenda;
    legenda << "Corsi" << "Vittorie" << "Media" << "Voto";

    //Cavallo temp;
 /*
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
            if (temp.GetRuolo() == 4)
                return QColor(Qt::magenta);
        }
    }
*/
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return legenda[section];
    else
        return (*cavalli)[section].getNome();

    return QVariant();
}
