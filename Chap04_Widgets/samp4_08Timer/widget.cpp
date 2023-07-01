#include "widget.h"
#include "./ui_widget.h"

#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    settingUI();

    m_timer = new QTimer(this);
    m_timer->stop();
    m_timer->setInterval(1000);
    m_timer->setTimerType(Qt::CoarseTimer);

    connect(m_timer, &QTimer::timeout, this, &Widget::do_timer_timeout);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_timer_timeout()
{
    QApplication::beep();

    QTime tmCur = QTime::currentTime();
    ui->lcdHour->display(QString("%1").arg(tmCur.hour(), 2, 10, QChar('0')));
    ui->lcdMinute->display(QString("%1").arg(tmCur.minute(), 2, 10, QChar('0')));
    ui->lcdSecond->display(QString("%1").arg(tmCur.second(), 2, 10, QChar('0')));

    //    qDebug() << QDateTime::currentDateTime();

    if (m_timer->isSingleShot()) {
        qint64 elapsedTm = m_counter.elapsed();
        QString strElapsed = QString("流逝的时间：%1毫秒").arg(elapsedTm);

        ui->lblElapsedTime->setText(strElapsed);

        ui->pbnStart->setEnabled(true);
        ui->pbnStop->setEnabled(false);
        ui->pbnDynamicTimer->setEnabled(true);
    }
}

void Widget::do_timer_shot()
{
    QApplication::beep();
    qint64 elapsedTm = m_counter.elapsed();
    QString strElapsed = QString("流逝的时间：%1毫秒").arg(elapsedTm);

    ui->lblElapsedTime->setText(strElapsed);
    ui->pbnDynamicTimer->setEnabled(true);

    ui->pbnStart->setEnabled(true);
}

void Widget::settingUI()
{
    this->setWindowTitle("定时器");
    ui->pbnStop->setEnabled(false);
    ui->rbnContinuousTimer->setChecked(true);
    ui->rbnCoarseTimer->setChecked(true);
}

void Widget::on_pbnStart_clicked()
{
    // 设置定时器周期
    bool singleShot = false;
    if (ui->rbnSingleTimer->isChecked()) {
        singleShot = true;
    }
    m_timer->setSingleShot(singleShot);

    // 设置定时器精度
    Qt::TimerType atype = Qt::CoarseTimer;
    if (ui->rbnPreciseTimer->isChecked()) {
        atype = Qt::PreciseTimer;
    } else if (ui->rbnVeryCoarseTimer->isChecked()) {
        atype = Qt::VeryCoarseTimer;
    }
    m_timer->setTimerType(atype);

    m_timer->start();
    m_counter.start();

    ui->pbnStart->setEnabled(false);
    ui->pbnStop->setEnabled(true);
    ui->pbnDynamicTimer->setEnabled(false);
}

void Widget::on_pbnStop_clicked()
{
    m_timer->stop();
    qint64 elapsedTm = m_counter.elapsed();
    QString strElapsed = QString("流逝的时间：%1秒,%2毫秒")
                             .arg(elapsedTm / 1000)
                             .arg(elapsedTm % 1000, 3, 10, QChar('0'));

    ui->lblElapsedTime->setText(strElapsed);

    ui->pbnStart->setEnabled(true);
    ui->pbnStop->setEnabled(false);
    ui->pbnDynamicTimer->setEnabled(true);
}

void Widget::on_pbnDynamicTimer_clicked()
{
    int delay = ui->sbxMilliSecond->value();
    QTimer::singleShot(delay, Qt::PreciseTimer, this, &Widget::do_timer_shot);
    m_counter.start();
    ui->pbnDynamicTimer->setEnabled(false);

    ui->pbnStart->setEnabled(false);
}
