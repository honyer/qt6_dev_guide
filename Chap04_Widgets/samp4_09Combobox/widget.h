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
    void on_pbnClearContent_clicked();

    void on_pbnInitList_clicked();

    void on_pbnClearList_clicked();

    void on_pbnInitCityCode_clicked();

    void on_cbxEditable_clicked(bool checked);

    void do_cbxitem_indexChanged();

private:
    Ui::Widget *ui;
};
