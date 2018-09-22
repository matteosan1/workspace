#include "picloadingdelegate.h"

#include <QPushButton>
#include <QByteArray>
#include <QBuffer>
#include <QPixmap>
#include <QSize>

void PicLoadingDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QItemDelegate::setEditorData(editor, index);

    if (index.column() == 1)
    {
        QPushButton* button = qobject_cast<QPushButton*>(editor);
        if (button)
        {
            QByteArray imageData = index.data(Qt::EditRole).toByteArray();
            QPixmap pixmap;
            if (pixmap.loadFromData(imageData))
            {
                pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation);
                QIcon buttonIcon(pixmap);
                button->setIcon(buttonIcon);
                button->setIconSize(pixmap.rect().size());
            }
        }
    }
}

void PicLoadingDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index ) const
{
    QItemDelegate::setModelData(editor, model, index);
    QPushButton* button = qobject_cast<QPushButton*> (editor);
    if (button)
    {
        QBuffer buf;
        buf.open(QIODevice::WriteOnly);
        QIcon icon = button->icon();
        if (icon.pixmap(icon.actualSize(QSize(100, 100))).save(&buf))
            model->setData(index, buf.data(), Qt::EditRole);
    }
}
