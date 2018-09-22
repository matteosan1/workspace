#include "mysqldelegate.h"

#include <QPainter>
#include <QImage>
#include <QSize>
#include <QFileDialog>

#include <QDebug>

MySqlDelegate::MySqlDelegate(QObject* parent) : QStyledItemDelegate(parent)
{}

void MySqlDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    if (index.column() == 2)
    {
        painter->fillRect(option.rect, QColor(191,222,185));
        QString path = index.data().toString();

        if (path != "")
        {
        qDebug() << path;
        QImage image = QImage(path);
        QPixmap pixmap = QPixmap::fromImage(image);
        //pixmap.scaled(50, 40, Qt::KeepAspectRatio);
        painter->drawPixmap(option.rect, pixmap);
        }
    }
}

QSize MySqlDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex& index) const
{
    QSize ret = QStyledItemDelegate::sizeHint(option, index);

    if (index.column() == 2)
    {
        ret = QSize(100, 100);
    }

    return ret;
}

void MySqlDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

QWidget *MySqlDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    QFileDialog* editor = new QFileDialog(parent);
   //QString value = dialog->getOpenFileName(0, "Team Image", "/home/sani/Pictures", "*.jpg");
    //editor->setFileMode(QFileDialog::Directory);
    //                editor.resize(400, 400)
    return editor;

//                    QString filename = QFileDialog::getOpenFileName(0, "Team Image", "/home/sani/Pictures", "*.jpg");

//    QSpinBox *editor = new QSpinBox(parent);
//    editor->setFrame(false);
//    editor->setMinimum(0);
//    editor->setMaximum(100);

//    return editor;
}

void MySqlDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    qDebug() << "setEditor";
    if (index.column() != 2)
        QStyledItemDelegate::setEditorData(editor, index);

//    {
//        // Get image data back from database
//        //        if( !query.exec( "SELECT imagedata from imgTable" ))
//        //            qDebug() << "Error getting image from table:\n" << query.lastError();
//        //            query.first();
//        QByteArray outByteArray = index.model()->data(index, Qt::EditRole).toByteArray();
//        QPixmap outPixmap = QPixmap();
//        outPixmap.loadFromData(outByteArray);
//        //db.close();


    // simply display the image taken from the model
    //QPushButton* button = qobject_cast<QPushButton*>(editor);
//    //if (button)
//    {
//        QByteArray imageData = index.data(Qt::EditRole).toByteArray();
//        QPixmap pixmap;
//        if (pixmap.loadFromData(imageData))
//        {
//            pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation);
//            QIcon buttonIcon(pixmap);
//            button->setIcon(buttonIcon);
//            button->setIconSize(pixmap.rect().size());
//        }
//    }
//    int value = index.model()->data(index, Qt::EditRole).toInt();

//    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
//    spinBox->setValue(value);
}

void MySqlDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    qDebug() << "setModel";
    QFileDialog *dialog = static_cast<QFileDialog*>(editor);
    //QString filename = dialog->getOpenFileName(0, "Team Image", "/home/sani", "*.jpg");
    qDebug() << dialog->selectedFiles().at(0);
    QFile file(dialog->selectedFiles().at(0));

    if (!file.open(QIODevice::ReadOnly))
        return;
    QByteArray inByteArray = file.readAll();

    model->setData(index, inByteArray, Qt::DecorationRole);
}

