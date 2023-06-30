#include "widget.h"
#include "./ui_widget.h"

#include <QRegularExpressionValidator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->letTotalPirce->setReadOnly(true);
    this->setWindowTitle("字符串与数值之间的转换");

    validateInput();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pbnDebug_clicked()
{
    QString str;
    double num = 1245.2783;
    qDebug("num= %f", num);
    str.setNum(num, 'f', 5); //小数点后 5 位，str ="1245.27830"
    qDebug("str= %s", str.toLocal8Bit().data());
    str.setNum(num, 'E', 5); //基数的小数点后 5 位，str ="1.24528E+03"
    qDebug("str= %s", str.toLocal8Bit().data());
    str.setNum(num, 'g', 5); //整数和小数总共 5 位，str ="1245.3"
    qDebug("str= %s", str.toLocal8Bit().data());
    str.setNum(num, 'g', 3); //整数和小数总共 3 位，str ="1.25e+03"
    qDebug("str= %s", str.toLocal8Bit().data());
}

void Widget::on_pbnCount_clicked()
{
    int num = ui->letNumber->text().toInt();
    double price = ui->letUnitPrice->text().toDouble();
    double total = num * price;
    ui->letTotalPirce->setText(QString::number(total, 'f', 2));
}

void Widget::on_pbnDecToOhter_clicked()
{
    qint64 dcmNum = ui->letDec->text().toLongLong();
    ui->letBin->setText(QString::number(dcmNum, 2));
    ui->letHex->setText(QString::number(dcmNum, 16).toUpper());
}

void Widget::on_pbnBinToOhter_clicked()
{
    qint64 binNum = ui->letBin->text().toLongLong(nullptr, 2);
    ui->letDec->setText(QString::number(binNum, 10));
    ui->letHex->setText(QString::number(binNum, 16).toUpper());
}

void Widget::on_pbnHexToOhter_clicked()
{
    qint64 hexNum = ui->letHex->text().toLongLong(nullptr, 16);
    ui->letDec->setText(QString::number(hexNum, 10));
    ui->letBin->setText(QString::number(hexNum, 2));
}

void Widget::validateInput()
{
    // 大于0且位数小于8位的数字的正则表达式校验
    QValidator *validNumber = new QRegularExpressionValidator(
        QRegularExpression("^[1-9][0-9]{0,7}$"));
    ui->letNumber->setValidator(validNumber);

    // 浮点数校验整数部分是6位长度,小数部分是2位
    QValidator *validDouble = new QRegularExpressionValidator(
        QRegularExpression("^[0-9]{0,6}+\\.[0-9]{1,2}$"));
    ui->letUnitPrice->setValidator(validDouble);

    // 十进制校验
    QValidator *validDec = new QRegularExpressionValidator(
        QRegularExpression("^[1-9][0-9]{0,16}$"));
    ui->letDec->setValidator(validDec);

    // 二进制校验
    QValidator *validBin = new QRegularExpressionValidator(QRegularExpression("^[01]{64}+$"));
    ui->letBin->setValidator(validDouble);

    // 十六进制校验
    QValidator *validHex = new QRegularExpressionValidator(
        QRegularExpression("0x[0-9A-Fa-f]{16}+$"));
    ui->letHex->setValidator(validDouble);
}
