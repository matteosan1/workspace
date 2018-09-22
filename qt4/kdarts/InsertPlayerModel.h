#ifndef INSERTPLAYERMODEL_H
#define INSERTPLAYERMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>

class InsertPlayerModel : public QAbstractTableModel {

    Q_OBJECT

    public:
        InsertPlayerModel(QObject *parent = 0, QVector<QString> v=QVector<QString>());
        QVector<QString> GetPlayers() { return players; }

        int columnCount(const QModelIndex &parent = QModelIndex()) const;
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value,
                     int role = Qt::EditRole);
        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    private:
        QVector<QString> players;
};
#endif
