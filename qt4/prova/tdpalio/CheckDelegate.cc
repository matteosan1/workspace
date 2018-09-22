#include <QtGui>

#include "CheckDelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    : QItemDelegate(parent)
{}

QWidget* CheckBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &/* option */,
                                        const QModelIndex& index) const {
    QCheckBox *editor = new QCheckBox(parent);
    //editor->setMinimum(0);
    //editor->setMaximum(100);

    return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const {

    int value = index.model()->data(index, Qt::DisplayRole).toInt();

    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
    checkBox->setChecked(value);
}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const {

    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
    //checkBox->interpretText();
    int value = checkBox->isChecked();

    model->setData(index, value, Qt::EditRole);
}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &/* index */) const {
    editor->setGeometry(option.rect);
}
