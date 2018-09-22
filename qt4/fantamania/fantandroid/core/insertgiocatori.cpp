#include "insertgiocatori.h"

GiocatoriInsert::GiocatoriInsert(QObject *parent)
  : QAbstractTableModel(parent) {
  
  m_giocatori.append(new Giocatore());
  
}

int GiocatoriInsert::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 5;
}

int GiocatoriInsert::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_giocatori.size();
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
                m_giocatori[index.row()]->setCognome(value.toString().toUpper());
                break;
            case 1:
                m_giocatori[index.row()]->setNome(value.toString().toUpper());
                break;
            case 3:
                m_giocatori[index.row()]->setSquadra(value.toString().toUpper());
                break;
            case 4:
                m_giocatori[index.row()]->setPrezzo(value.toInt());
                break;
            case 2:
                m_giocatori[index.row()]->setRuolo(convertToRuoloEnum(value.toInt()));
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

RuoloEnum GiocatoriInsert::convertToRuoloEnum(const int value)
{
    switch (value)
    {
    case 0:
        return Portiere;
    case 1:
        return DifensoreLaterale;
    case 2:
        return DifensoreCentrale;
    case 3:
        return CentrocampistaEsterno;
    case 4:
        return CentrocampistaCentrale;
    case 5:
        return CentrocampistaTrequartista;
    case 6:
        return AttaccanteCentrale;
    case 7:
        return AttaccanteMovimento;
    default:
        return Portiere;
    }
}

QVariant GiocatoriInsert::data(const QModelIndex &index, int role) const {

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_giocatori.size())
        return QVariant();

    Giocatore* temp = m_giocatori[index.row()];
    if (role == Qt::TextAlignmentRole)
        return int(Qt::AlignHCenter | Qt::AlignVCenter);

    if (role == Qt::DisplayRole) {
        switch(index.column()) {
            case 0:
                return temp->cognome();
            case 1:
                return temp->nome();
            case 2:
                if (temp->ruolo() == Portiere)
                    return QString("P");
                else if (temp->ruolo() == DifensoreCentrale)
                    return QString("DC");
                else if (temp->ruolo() == DifensoreLaterale)
                    return QString("DL");
                else if (temp->ruolo() == CentrocampistaCentrale)
                    return QString("CC");
                else if (temp->ruolo() == CentrocampistaEsterno)
                    return QString("CE");
                else if (temp->ruolo() == CentrocampistaTrequartista)
                    return QString("CT");
                else if (temp->ruolo() == AttaccanteCentrale)
                    return QString("AC");
                else if (temp->ruolo() == AttaccanteMovimento)
                    return QString("AM");

                return QString("");
            case 3:
                return temp->squadra();
            case 4:
                return temp->prezzo();
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
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        m_giocatori.append(new Giocatore());
    }

    endInsertRows();
    return true;
}

bool GiocatoriInsert::removeRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for(int i=position; i<m_giocatori.size()-1; ++i)
        m_giocatori[i] = m_giocatori[i+1];

    m_giocatori.removeLast();

    endRemoveRows();
    return true;
}
