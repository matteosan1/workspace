#include "customsqlmodel.h"

#include <QByteArray>
#include <QIcon>
#include <QPixmap>

#include <QDebug>

QVariant CustomSqlModel::data(const QModelIndex &idx, int role) const
{
    if (idx.column() == 2) {
         if (role == Qt::DisplayRole)
             return QString();

         if (role == Qt::DecorationRole)
         {
             QByteArray imageData = idx.data(Qt::EditRole).toByteArray();
             QPixmap pixmap;
             if (pixmap.loadFromData(imageData))
             {
                 pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation);
             }

             return pixmap;   // return QPixmap for decoration role
         }

         //if (role == Qt::SizeHintRole)
         //   return pixmap.size(); // in case need the image size
    }

    return QSqlTableModel::data( idx, role ); // use original data() outside the imageColumn
}
