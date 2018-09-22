#include "GiocatoriInsert.h"

GiocatoriInsert::GiocatoriInsert(QObject *parent)
  : QAbstractTableModel(parent) {
  
  giocatori.append(new Giocatore());
  
}

int GiocatoriInsert::columnCount(const QModelIndex &parent) const {
    return 5;
}

int GiocatoriInsert::rowCount(const QModelIndex &parent) const {
    return giocatori.size();
}

Qt::ItemFlags GiocatoriInsert::flags(const QModelIndex &index) const {

    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool GiocatoriInsert::setData(const QModelIndex &index,
                              const QVariant &value, int role) {

    if (index.isValid() && role == Qt::EditRole) {
        switch(index.column()) {
            case 0:
                giocatori[index.row()].SetCognome(value.toString().toUpper());
                break;
            case 1:
                giocatori[index.row()].SetNome(value.toString().toUpper());
                break;
            case 3:
                giocatori[index.row()].SetSquadra(value.toString().toUpper());
                break;
            case 4:
                giocatori[index.row()].SetPrezzo(value.toInt());
                break;
            case 2:
                giocatori[index.row()].SetRuolo(value.toInt());
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant GiocatoriInsert::data(const QModelIndex &index, int role) const {

    if (!index.isValid())
        return QVariant();

    if ((unsigned int)index.row() >= giocatori.size())
        return QVariant();

    Giocatore temp = giocatori[index.row()];
    if (role == Qt::TextAlignmentRole)
        return int(Qt::AlignHCenter | Qt::AlignVCenter);

    if (role == Qt::DisplayRole) {
        switch(index.column()) {
            case 0:
                return temp.GetCognome();
            case 1:
                return temp.GetNome();
            case 2:
                if (temp.GetRuolo() == 0)
                    return QString("Purtiere");
                if (temp.GetRuolo() == 1)
                    return QString("Difensore");
                if (temp.GetRuolo() == 2)
                    return QString("Centrocampista");
                if (temp.GetRuolo() == 3)
                    return QString("Attaccante");
                return QString("");
            case 3:
                return temp.GetSquadra();
            case 4:
                return temp.GetPrezzo();
            default:
                return QVariant();
        }
    }

    return QVariant();
}

QVariant GiocatoriInsert::headerData(int section, Qt::Orientation orientation, int role) const {

    QStringList legenda;
    legenda << "Cognome" << "Nome" << "Ruolo" << "Squadra" << "Prezzo";

    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return legenda[section];

    return QVariant();
}

bool GiocatoriInsert::insertRows(int position, int rows, const QModelIndex &parent) {

    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        giocatori.push_back(Giocatore());
    }

    endInsertRows();
    return true;
}

bool GiocatoriInsert::removeRows(int position, int rows, const QModelIndex &parent) {

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for(int i=position; i<giocatori.size()-1; ++i)
        giocatori[i] = giocatori[i+1];

    giocatori.erase(giocatori.end());

    endRemoveRows();
    return true;
}
