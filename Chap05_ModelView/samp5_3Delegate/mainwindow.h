#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelectionModel>
#include <QLabel>
#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>
#include "tcomboboxdelegate.h"
#include "tfloatspindelegate.h"
#include "tspinboxdelegate.h"

#define FixedColumnCount 6

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initSetting();
    void loadFileData(const QString &fileName, QStringList &strContent);
    void loadDataForTable(const QStringList &strContent);

private slots:
    void do_currentChanged(const QModelIndex &current, const QModelIndex &previous); // 选择项变化

    void on_actOpen_triggered();

    void on_actPreview_triggered();

    void on_acAlignLeft_triggered();

    void on_acAlignCenter_triggered();

    void on_acAlignRight_triggered();

    void on_actFontBold_triggered();

    void on_actExit_triggered();

    void on_actAppend_triggered();

    void on_actInsert_triggered();

    void on_actDel_triggered();

private:
    Ui::MainWindow *ui;
    // 自定义代理
    TSpinBoxDelegate *intSpinDelegate;
    TFloatSpinDelegate *floatSpinDelegate;
    TComboBoxDelegate *comboDelegate;
    // item模型
    QStandardItemModel *m_model;
    QItemSelectionModel *m_selection;
    // 状态栏标签
    QLabel *lblFileName;
    QLabel *lblIndex;
    QLabel *lblItemText;
    // 默认文件名
    QString fileName;
    QStringList qualityType;
};
#endif // MAINWINDOW_H
