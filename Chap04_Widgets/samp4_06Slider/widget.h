#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void do_sbr_clicked(int value);    // 滑动按钮处理
    void do_cbx_clicked(bool checked); // 复选框点击处理
    void do_rbn_clicked(bool checked); // 单选框点击处理

private:
    Ui::Widget *ui;
    void settingUi();
    void initSlots();
};
