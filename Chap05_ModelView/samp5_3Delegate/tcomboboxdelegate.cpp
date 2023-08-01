#include "tcomboboxdelegate.h"
#include <QComboBox>

TComboBoxDelegate::TComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}
QWidget *TComboBoxDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    Q_UNUSED(index);
    Q_UNUSED(option);
    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(m_editable);
    for (int i = 0; i < m_itemList.count(); ++i) {
        editor->addItem(m_itemList.at(i));
    }
    return editor;
}

void TComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comBox = static_cast<QComboBox *>(editor);
    comBox->setCurrentText(str);
}

void TComboBoxDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    QComboBox *comBox = static_cast<QComboBox *>(editor);
    QString str = comBox->currentText();
    model->setData(index, str, Qt::EditRole);
}

void TComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

void TComboBoxDelegate::setItems(QStringList items, bool editable)
{
    m_itemList = items;
    m_editable = editable;
}
