#ifndef MYSQLDELEGATE_H
#define MYSQLDELEGATE_H

#include <QStyledItemDelegate>

class MySqlDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MySqlDelegate(QObject* parent=0);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const;

};

#endif
