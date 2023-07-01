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
    void on_pbnGetCurrentDT_clicked();

    void on_calendar_clicked(const QDate &date);

    void on_pbnSetTime_clicked();

    void on_pbnSetDate_clicked();

    void on_pbnSetDatetime_clicked();

    void on_pbnDebugDatetime_clicked();

    void on_pbnDebugDate_clicked();

    void on_pbnDebugTime_clicked();

private:
    Ui::Widget *ui;
};
