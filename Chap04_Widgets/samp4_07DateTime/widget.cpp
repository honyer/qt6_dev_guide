#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pbnGetCurrentDT_clicked()
{
    QDateTime dtCurrent = QDateTime::currentDateTime().toLocalTime();
    QString dtStr = dtCurrent.toString("yyyy-MM-dd HH:mm:ss");

    ui->letTime->setText(dtStr.right(8));
    ui->letDate->setText(dtStr.left(10));
    ui->letDateTime->setText(dtStr);

    ui->timeEdit->setTime(dtCurrent.time());
    ui->dateEdit->setDate(dtCurrent.date());
    ui->dateTimeEdit->setDateTime(dtCurrent);
}

void Widget::on_calendar_clicked(const QDate &date)
{
    ui->letCalendar->setText(date.toString("yyyy年M月d日"));
}

void Widget::on_pbnSetTime_clicked()
{
    QString strTime = ui->letTime->text();
    if (strTime.isEmpty() || strTime.length() < 8) {
        return;
    }
    QTime time = QTime::fromString(strTime, "HH:mm:ss");
    ui->timeEdit->setTime(time);
}

void Widget::on_pbnSetDate_clicked()
{
    QString strDate = ui->letDate->text();
    if (strDate.isEmpty() || strDate.length() < 10) {
        return;
    }
    QDate date = QDate::fromString(strDate, "yyyy-MM-dd");
    ui->dateEdit->setDate(date);
}

void Widget::on_pbnSetDatetime_clicked()
{
    QString strDateTime = ui->letDateTime->text();
    if (strDateTime.isEmpty() || strDateTime.length() < 19) {
        return;
    }
    QDateTime dateTime = QDateTime::fromString(strDateTime, "yyyy-MM-dd HH:mm:ss");
    ui->dateTimeEdit->setDateTime(dateTime);
}

void Widget::on_pbnDebugDatetime_clicked()
{
    QDateTime DT1 = QDateTime::currentDateTime(); //系统当前日期时间
    QString str = DT1.toString("yyyy-MM-dd hh:mm:ss");
    qDebug("DT1= %s", str.toLocal8Bit().data());
    QDate dt = DT1.date(); //日期部分
    str = dt.toString("yyyy-MM-dd");
    qDebug("DT1.date()= %s", str.toLocal8Bit().data());
    QTime tm = DT1.time(); //时间部分
    str = tm.toString("hh:mm:ss zzz");
    qDebug("DT1.time()= %s", str.toLocal8Bit().data());
    qint64 MS = DT1.toSecsSinceEpoch(); //转换为秒数
    qDebug("DT1.toSecsSinceEpoch()= %lld", MS);
    MS += 120;
    DT1.setSecsSinceEpoch(MS); //加 120 秒以后
    str = DT1.toString("yyyy-MM-dd hh:mm:ss");
    qDebug("DT1+120s= %s", str.toLocal8Bit().data());
}

void Widget::on_pbnDebugDate_clicked()
{
    QDate DT1(2021, 7, 6); //初始化日期
    QString str = DT1.toString("yyyy-MM-dd");
    qDebug("DT1= %s", str.toLocal8Bit().data());
    QDate DT2;
    DT2.setDate(2021, 8, 25); //设置日期
    str = DT2.toString("yyyy-MM-dd");
    qDebug("DT2= %s", str.toLocal8Bit().data());
    qDebug("Days between DT2 and DT1= %d", DT2.daysTo(DT1)); //DT2 与 DT1 相差的天数
    DT2 = QDate::currentDate();                              //获取当前日期
    str = DT2.toString("yyyy-MM-dd");
    qDebug("Current date= %s", str.toLocal8Bit().data());
    qDebug("Year= %d", DT2.year());
    qDebug("Month= %d", DT2.month());
    qDebug("Day= %d", DT2.day());
    qDebug("Day of week= %d", DT2.dayOfWeek()); //1 表示星期一，7 表示星期天
}

void Widget::on_pbnDebugTime_clicked()
{
    QTime TM1(13, 24, 5); //定义变量，初始化设置时间
    QString str = TM1.toString("HH:mm:ss");
    qDebug("Original time= %s", str.toLocal8Bit().data());
    QTime TM2 = TM1.addSecs(150); //延后 150 秒
    str = TM2.toString("HH:mm:ss");
    qDebug("150s later, time= %s", str.toLocal8Bit().data());
    TM2 = QTime::currentTime(); //获取当前时间
    str = TM2.toString("HH:mm:ss zzz");
    qDebug("Current time= %s", str.toLocal8Bit().data());
    qDebug("Hour= %d", TM2.hour());
    qDebug("Minute= %d", TM2.minute());
    qDebug("Second= %d", TM2.second());
    qDebug("MSecond= %d", TM2.msec());
}
