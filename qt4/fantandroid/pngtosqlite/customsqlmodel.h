#ifndef CUSTOMSQLMODEL_H
#define CUSTOMSQLMODEL_H

#include <QObject>
#include <QSqlTableModel>

class CustomSqlModel : public QSqlTableModel
{
    Q_OBJECT

public:
    CustomSqlModel(QObject *parent = Q_NULLPTR, QSqlDatabase db = QSqlDatabase()) : QSqlTableModel(parent, db) {}

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
};

#endif // CUSTOMSQLMODEL_H
