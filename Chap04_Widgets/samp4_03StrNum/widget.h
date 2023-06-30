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
    void on_pbnDebug_clicked();

    void on_pbnCount_clicked();

    void on_pbnDecToOhter_clicked();

    void on_pbnBinToOhter_clicked();

    void on_pbnHexToOhter_clicked();

private:
    Ui::Widget *ui;
    void validateInput();
};
