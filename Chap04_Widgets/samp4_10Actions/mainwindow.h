#pragma once

#include <QActionGroup>
#include <QFontComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QSpinBox *sbxFontSize;      // 字体大小控件
    QFontComboBox *fcbFontName; // 字体控件
    QActionGroup *agpCnEn;      // 中英互斥Group
    QLabel *lblFile;            // 状态栏标签
    QLabel *lblInfo;            // 状态栏标签
    QProgressBar *pbrFontSize;  // 状态栏progressBar显示字体大小

    void settingUi();
    void initSlots();
private slots:
    void do_fontFize_Changed(int size);      // sbxFontSize值变化信号槽函数
    void do_fontSelected(const QFont &font); // fcbFontName选择变化信号槽函数
    void do_font_checked(bool checked);      // QAction粗体、斜体、下划线信号槽函数
    void do_file_operation_triggled();       // QAction文件新建、保存、打开信号槽函数

    void on_plainTextEdit_copyAvailable(bool b);

    void on_plainTextEdit_selectionChanged();

    void on_actSys_ToggleText_triggered(bool checked);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
