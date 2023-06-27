#pragma once

#include <QCheckBox>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void do_cbxUnderLine(bool checked);
    void do_cbxItalic(bool checked);
    void do_cbxBold(bool checked);
    void do_setFontColor();
    void do_clearButtonClicked();
    void do_quitButtonClicked();

private:
    QCheckBox *cbxUnderLine; // 3个复选框
    QCheckBox *cbxItalic;
    QCheckBox *cbxBold;

    QRadioButton *rbtnBlack; // 3个单选按钮
    QRadioButton *rbtnRed;
    QRadioButton *rbtnBlue;

    QPlainTextEdit *ptextEdit; // 文本编辑框

    QPushButton *btnClear; // 3个按钮
    QPushButton *btnOk;
    QPushButton *btnQuit;

    QFont font;

    void setupUI();         // 初始化UI
    void beautifyUI();      //美化UI组件
    void initSignalSlots(); // 初始化信号与槽的连接
};
