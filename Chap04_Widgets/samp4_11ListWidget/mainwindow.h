#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_listAction_trigled(); // listWidget的初始化，清除，插入，添加，删除操作

    void do_listItem_Selection(); // listWidget里面item的全选，反选，不选操作

    void do_tbnSort_clicked(bool checked); // ToolButton排序操作

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_itemSelectionChanged();

    void on_tbnTextClear_clicked();

    void on_tbnTextAddLine_clicked();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    void initSlots();
    void setActionsForButton();
    void createSelectionMenu();
};
