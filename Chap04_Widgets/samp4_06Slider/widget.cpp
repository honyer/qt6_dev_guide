#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    settingUi();
    initSlots();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_sbr_clicked(int value)
{
    ui->pbr->setValue(value);
}

void Widget::do_cbx_clicked(bool checked)
{
    QObject *obj = QObject::sender();

    if (obj == ui->cbxTextVisible) {
        ui->pbr->setTextVisible(checked);

    } else if (obj == ui->cbxInvertedAppearance) {
        ui->pbr->setInvertedAppearance(checked);
    }
}

void Widget::do_rbn_clicked(bool checked)
{
    QObject *obj = QObject::sender();

    if (obj == ui->rbxDisplayPercent) {
        ui->pbr->setFormat("%p%");

    } else if (obj == ui->rbxDisplayValue) {
        ui->pbr->setFormat("%v");
    }
}

void Widget::settingUi()
{
    this->setWindowTitle("Slider和ProgressBar");
    int max = 255;
    ui->dialInput->setMaximum(max);
    ui->dialInput->setNotchesVisible(true); // 显示刻度
    ui->dialInput->setNotchTarget(10.0);    // 刻度最小值

    ui->hsbInput->setMaximum(max);
    ui->hsrInput->setMaximum(max);

    ui->pbr->setMaximum(max);
}

void Widget::initSlots()
{
    connect(ui->dialInput, &QDial::valueChanged, this, &Widget::do_sbr_clicked);
    connect(ui->hsbInput, &QScrollBar::valueChanged, this, &Widget::do_sbr_clicked);
    connect(ui->hsrInput, &QSlider::valueChanged, this, &Widget::do_sbr_clicked);

    connect(ui->cbxTextVisible, &QCheckBox::clicked, this, &Widget::do_cbx_clicked);
    connect(ui->cbxInvertedAppearance, &QCheckBox::clicked, this, &Widget::do_cbx_clicked);

    connect(ui->rbxDisplayPercent, &QRadioButton::clicked, this, &Widget::do_rbn_clicked);
    connect(ui->rbxDisplayValue, &QRadioButton::clicked, this, &Widget::do_rbn_clicked);
}
