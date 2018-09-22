#ifndef PICLOADINGDELEGATE_H
#define PICLOADINGDELEGATE_H

#include <QObject>
#include <QItemDelegate>

class PicLoadingDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    PicLoadingDelegate(QObject* parent = 0):QItemDelegate(parent) {}

    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index ) const;

};

#endif // PICLOADINGDELEGATE_H
