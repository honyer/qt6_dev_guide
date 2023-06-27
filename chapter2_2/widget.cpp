#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 三个radioButton点击事件绑定到do_setFontColor()
    connect(ui->rbtnBlack, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(ui->rbtnRed, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(ui->rbtnBlue, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_cbxUnderLine_clicked(bool checked)
{
    font = ui->ptextEdit->font();
    font.setUnderline(checked);
    ui->ptextEdit->setFont(font);
}

void Widget::on_cbxItalic_clicked(bool checked)
{
    font = ui->ptextEdit->font();
    font.setItalic(checked);
    ui->ptextEdit->setFont(font);
}

void Widget::on_cbxBold_clicked(bool checked)
{
    font = ui->ptextEdit->font();
    font.setBold(checked);
    ui->ptextEdit->setFont(font);
}

// 自定义的颜色设置槽函数
void Widget::do_setFontColor()
{
    QPalette pal = ui->ptextEdit->palette();
    if (ui->rbtnRed->isChecked()) {
        pal.setColor(QPalette::Text, Qt::red);
    } else if (ui->rbtnBlue->isChecked()) {
        pal.setColor(QPalette::Text, Qt::blue);
    } else if (ui->rbtnBlack->isChecked()) {
        pal.setColor(QPalette::Text, Qt::black);
    } else {
        pal.setColor(QPalette::Text, Qt::black);
    }
    ui->ptextEdit->setPalette(pal);
}

void Widget::on_btnClear_clicked()
{
    // 清空复选框选择
    ui->cbxUnderLine->setChecked(false);
    ui->cbxItalic->setChecked(false);
    ui->cbxBold->setChecked(false);

    // 清空单选框
    ui->rbtnBlack->setChecked(true);
    ui->rbtnRed->setChecked(false);
    ui->rbtnBlue->setChecked(false);
    qDebug() << ui->rbtnBlack->isChecked() << ui->rbtnRed->isChecked() << ui->rbtnBlue->isChecked();

    // 清空文本框，设置默认font
    font = QFont(); // 重新初始化font对象
    QPalette pal = QPalette();
    ui->ptextEdit->clear();
    ui->ptextEdit->setFont(font);
    ui->ptextEdit->setPalette(pal);
}

void Widget::on_btnOk_clicked() {}

void Widget::on_btnQuit_clicked()
{
    QApplication::quit();
}
