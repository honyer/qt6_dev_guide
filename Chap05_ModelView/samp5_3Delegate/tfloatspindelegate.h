#ifndef TFLOATSPINDELEGATE_H
#define TFLOATSPINDELEGATE_H

#include <QStyledItemDelegate>

class TFloatSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TFloatSpinDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // TFLOATSPINDELEGATE_H
