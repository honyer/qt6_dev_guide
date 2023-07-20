#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelectionModel>
#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>

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
private slots:

    void do_actionAlign_triggerd(); // 居左,居中,居右

    void do_actionFont_tridderd(bool checked); // 粗体

    void do_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actAppendRow_triggered(); // 添加行

    void on_actInsertRow_triggered(); // 插入行

    void on_actDelRow_triggered(); // 删除行

    void on_actOpen_triggered(); // 打开文件

    void on_actExit_triggered(); // 退出

    void on_actPreview_triggered(); // 预览数据

private:
    void initSetting();

    void loadFileData(QString &aFileName, QStringList &strContent);

    void initData(const QStringList &aFileName);

    void initSlots();

private:
    Ui::MainWindow *ui;
    QLabel *lblCurFile;
    QLabel *lblCellPos;
    QLabel *lblCellText;
    QStandardItemModel *m_model;
    QItemSelectionModel *m_selection;
    QString defaultFile = "JingXie.txt";
};
#endif // MAINWINDOW_H
