#pragma once

#include <QElapsedTimer>
#include <QTimer>
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
    void do_timer_timeout();
    void do_timer_shot();

    void on_pbnStart_clicked();

    void on_pbnStop_clicked();

    void on_pbnDynamicTimer_clicked();

private:
    Ui::Widget *ui;
    QTimer *m_timer;
    QElapsedTimer m_counter;
    void settingUI();
};
