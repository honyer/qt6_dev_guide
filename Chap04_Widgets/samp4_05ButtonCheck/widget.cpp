#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("按钮的使用");
    initSlots();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_button_clicked(bool checked)
{
    QAbstractButton *btn = qobject_cast<QAbstractButton *>(sender());

    // 布局按钮
    if (btn == ui->pbnAlignLeft) {
        ui->letContent->setAlignment(Qt::AlignLeft);
    } else if (btn == ui->pbnAlignCenter) {
        ui->letContent->setAlignment(Qt::AlignCenter);
    } else if (btn == ui->pbnAlignRight) {
        ui->letContent->setAlignment(Qt::AlignRight);
    }

    // 字体按钮
    QFont font = ui->letContent->font();
    if (btn == ui->pbnFontBold) {
        font.setBold(checked);
    } else if (btn == ui->pbnFontItalic) {
        font.setItalic(checked);
    } else if (btn == ui->pbnFontUnderline) {
        font.setUnderline(checked);
    }
    ui->letContent->setFont(font);

    // 属性按钮
    if (btn == ui->cbxReadonly) {
        ui->letContent->setReadOnly(checked);
    } else if (btn == ui->cbxEnabled) {
        ui->letContent->setEnabled(checked);
    } else if (btn == ui->cbxClear) {
        ui->letContent->setClearButtonEnabled(checked);
    }

    // 颜色按钮
    QPalette pal = ui->letContent->palette();
    if (btn == ui->rbnBlack) {
        pal.setColor(QPalette::Text, Qt::black);
    } else if (btn == ui->rbnRed) {
        pal.setColor(QPalette::Text, Qt::red);
    } else if (btn == ui->rbnBlue) {
        pal.setColor(QPalette::Text, Qt::blue);
    }
    ui->letContent->setPalette(pal);
}

void Widget::initSlots()
{
    connect(ui->pbnAlignLeft, &QPushButton::clicked, this, &Widget::do_button_clicked);
    connect(ui->pbnAlignCenter, &QPushButton::clicked, this, &Widget::do_button_clicked);
    connect(ui->pbnAlignRight, &QPushButton::clicked, this, &Widget::do_button_clicked);

    connect(ui->pbnFontBold, &QPushButton::clicked, this, &Widget::do_button_clicked);
    connect(ui->pbnFontItalic, &QPushButton::clicked, this, &Widget::do_button_clicked);
    connect(ui->pbnFontUnderline, &QPushButton::clicked, this, &Widget::do_button_clicked);

    connect(ui->cbxReadonly, &QCheckBox::clicked, this, &Widget::do_button_clicked);
    connect(ui->cbxEnabled, &QCheckBox::clicked, this, &Widget::do_button_clicked);
    connect(ui->cbxClear, &QCheckBox::clicked, this, &Widget::do_button_clicked);

    connect(ui->rbnBlack, &QRadioButton::clicked, this, &Widget::do_button_clicked);
    connect(ui->rbnRed, &QRadioButton::clicked, this, &Widget::do_button_clicked);
    connect(ui->rbnBlue, &QRadioButton::clicked, this, &Widget::do_button_clicked);
}
