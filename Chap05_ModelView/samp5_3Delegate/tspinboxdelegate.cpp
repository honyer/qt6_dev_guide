#include "tspinboxdelegate.h"
#include <QSpinBox>

TSpinBoxDelegate::TSpinBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

QWidget *TSpinBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QSpinBox *editor = new QSpinBox(parent);

    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(20000);
    return editor;
}

void TSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
    spinBox->setValue(value);
}

void TSpinBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
    int value = spinBox->value();
    QString str = QString::asprintf("%d", value);
    model->setData(index, str, Qt::EditRole);
}

void TSpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
