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
    void on_btnCount_clicked();
    void do_sbxBinary_valueChanged();

private:
    Ui::Widget *ui;
    void initUiSetting();
    void initSlots();
};
