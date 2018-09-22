#include "InsertPlayerModel.h"

InsertPlayerModel::InsertPlayerModel(QObject *parent, QVector<QString> v)
    : QAbstractTableModel(parent) {
    players = v;
}

int InsertPlayerModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

int InsertPlayerModel::rowCount(const QModelIndex &parent) const {
    return players.size();
}

Qt::ItemFlags InsertPlayerModel::flags(const QModelIndex &index) const {

    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool InsertPlayerModel::setData(const QModelIndex &index,
                                 const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        if (index.isValid() && role == Qt::EditRole) {
            players[index.row()] = value.toString().toUpper();
            emit dataChanged(index, index);
            return true;
        }
        return false;
    }
}



QVariant InsertPlayerModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid())
        return QVariant();

    if ((unsigned int)index.row() >= players.size())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
        return int(Qt::AlignHCenter | Qt::AlignVCenter);

    if (role == Qt::DisplayRole) {
        return players[index.row()];
    }

    return QVariant();
}

QVariant InsertPlayerModel::headerData(int section, Qt::Orientation orientation, int role) const {

    QStringList legenda;
    legenda << "Player Name";

    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return legenda[0];

    return QVariant();
}

bool InsertPlayerModel::insertRows(int position, int rows, const QModelIndex &parent) {

    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row)
        players.push_back(QString(""));

    endInsertRows();
    return true;
}

bool InsertPlayerModel::removeRows(int position, int rows, const QModelIndex &parent) {

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for(int i=position; i<players.size()-1; ++i)
        players[i] = players[i+1];

    players.erase(players.end());

    endRemoveRows();
    return true;
}
