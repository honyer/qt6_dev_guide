#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Spinbox测试");
    initUiSetting();
    initSlots();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initSlots()
{
    connect(ui->sbxNumber, &QSpinBox::valueChanged, this, &Widget::on_btnCount_clicked);
    connect(ui->sbxPrice, &QDoubleSpinBox::valueChanged, this, &Widget::on_btnCount_clicked);

    connect(ui->sbxDec, &QSpinBox::valueChanged, this, &Widget::do_sbxBinary_valueChanged);
    connect(ui->sbxBin, &QSpinBox::valueChanged, this, &Widget::do_sbxBinary_valueChanged);
    connect(ui->sbxHex, &QSpinBox::valueChanged, this, &Widget::do_sbxBinary_valueChanged);
}

void Widget::on_btnCount_clicked()
{
    int num = ui->sbxNumber->value();
    double price = ui->sbxPrice->value();
    ui->sbxTotal->setValue(price * num);
}

void Widget::do_sbxBinary_valueChanged()
{
    QSpinBox *sbx = qobject_cast<QSpinBox *>(sender());
    int num;
    if (sbx == ui->sbxDec) {
        num = ui->sbxDec->value();
        ui->sbxBin->setValue(num);
        ui->sbxHex->setValue(num);
    } else if (sbx == ui->sbxBin) {
        num = ui->sbxBin->value();
        ui->sbxDec->setValue(num);
        ui->sbxHex->setValue(num);
    } else if (sbx == ui->sbxHex) {
        num = ui->sbxHex->value();
        ui->sbxDec->setValue(num);
        ui->sbxBin->setValue(num);
    }
}

void Widget::initUiSetting()
{
    ui->sbxNumber->setRange(0, 999999);
    ui->sbxPrice->setRange(0, 999999.99);
    ui->sbxTotal->setRange(0, 9999999999999.99);

    ui->sbxDec->setMaximum(65535);
    ui->sbxBin->setMaximum(65535);
    ui->sbxHex->setMaximum(65535);

    ui->sbxBin->setDisplayIntegerBase(2);
    ui->sbxHex->setDisplayIntegerBase(16);
}
