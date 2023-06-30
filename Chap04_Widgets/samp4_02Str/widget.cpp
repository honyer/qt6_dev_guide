#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("QString常用功能");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pbnClear_clicked()
{
    ui->pteContent->clear();
}

void Widget::on_pbnFrontBack_clicked()
{
    QString str = "字符串截取:\n";
    str.append("front(),back()函数测试\n");
    QString str1 = ui->cbxStr1->currentText();
    str.append("str1=" + str1 + "\n");
    str.append("front()=" + QString(str1.front()) + "\n");
    str.append("back()=" + QString(str1.back()) + "\n");
    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnLeftRight_clicked()
{
    QString str = "字符串截取:\n";
    str.append("left(),right()函数测试\n");
    QString str1 = ui->cbxStr1->currentText();
    str.append("str1=" + str1 + "\n");
    str.append("left(2)=" + QString(str1.left(2)) + "\n");
    str.append("right(6)=" + QString(str1.right(6)) + "\n");

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnFirstLast_clicked()
{
    QString str = "字符串截取:\n";
    str.append("first(),last()函数测试\n");
    QString str1 = ui->cbxStr1->currentText();
    str.append("str1=" + str1 + "\n");
    str.append("first(11)=" + QString(str1.first(11)) + "\n");
    str.append("last(9)=" + QString(str1.last(9)) + "\n");

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnSection_clicked()
{
    QString str = "字符串截取:\n";
    str.append("section()函数测试\n");
    QString str1 = ui->cbxStr1->currentText();
    QString str2 = ui->cbxStr2->currentText();
    str.append("str1=" + str1 + "\n");
    str.append("str2=" + str2 + "\n");
    str.append("str1.section(str2, 0, 0)=" + str1.section(str2, 0, 0) + "\n");
    str.append("str1.section(str2, -1, -1)=" + str1.section(str2, -1, -1) + "\n");

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnIsNullEmpty_clicked()
{
    QString str = "存储相关:\n";
    str.append("isNull(),isEmpty()函数测试\n");
    QString str1 = ui->cbxStr1->currentText();

    str.append("str1=" + str1 + "\n");
    str.append("str1.isNull()=" + [str1]() {
        return str1.isNull() ? QString("true") : QString("false");
    }() + "\n");
    str.append("str1.isEmpty()=" + [str1]() {
        return str1.isEmpty() ? QString("true") : QString("false");
    }() + "\n");

    str.append("\nstr1=;\n");
    str1 = "";
    str.append("str1.isNull()=" + [str1]() {
        return str1.isNull() ? QString("true") : QString("false");
    }() + "\n");
    str.append("str1.isEmpty()=" + [str1]() {
        return str1.isEmpty() ? QString("true") : QString("false");
    }() + "\n");

    str.append("\nstr1.clear()\n");
    str1.clear();
    str.append("str1.isNull()=" + [str1]() {
        return str1.isNull() ? QString("true") : QString("false");
    }() + "\n");
    str.append("str1.isEmpty()=" + [str1]() {
        return str1.isEmpty() ? QString("true") : QString("false");
    }() + "\n");

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnResize_clicked()
{
    QString str = "存储相关:\n";
    str.append("resize()函数测试\n");
    QString str1;
    str.append("QString str1;\n");
    str1.resize(5, '0');
    str.append("str1.resize(5, '0')=" + str1 + "\n");
    str1.resize(10, QChar(0x54C8));
    str.append("str1.resize(10,QChar(0x54C8))=" + str1 + "\n");
    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnSizeLength_clicked()
{
    QString str = "存储相关:\n";
    str.append("size(),length()函数测试\n");
    QString str1 = ui->cbxStr1->currentText();
    str.append("str1=" + str1 + "\n");
    str.append("str1.size()=" + QString::asprintf("%d\n", str1.size()));
    //    str.append("str1.count()=" + QString::asprintf("%d\n", str1.count()));
    str.append("str1.length()=" + QString::asprintf("%d\n", str1.length()));

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnFill_clicked()
{
    QString str = "存储相关:\n";
    str.append("fill()函数测试\n");
    QString str1 = ui->cbxStr1->currentText();
    str.append("str1=" + str1 + "\n");
    str1.fill('A');
    str.append("str1.fill('A')=" + str1 + "\n");
    str1.fill('X', 3);
    str.append("str1.fill('X',3)=" + str1 + "\n");
    str1.fill(QChar(0x54C8), 3);
    str.append("str1.fill(QChar(0x54C8), 3)=" + str1 + "\n");

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnIndexLastOf_clicked()
{
    QString str = "搜索和判断:\n";
    str.append("indexOf(),lastIndexOf()函数测试\n");
    // TODO

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnContains_clicked()
{
    QString str = "搜索和判断:\n";
    str.append("contains()函数测试\n");
    // TODO

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnEndStartWith_clicked()
{
    QString str = "搜索和判断:\n";
    str.append("endsWith(),startsWith()函数测试\n");
    // TODO

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnCount_clicked()
{
    QString str = "搜索和判断:\n";
    str.append("count()函数测试\n");
    // TODO

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnTrimSimplfy_clicked()
{
    QString str = "转换或修改:\n";
    str.append("trimmed(),simplified()函数测试\n");
    // TODO

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnInsert_clicked()
{
    QString str = "转换或修改:\n";
    str.append("insert()函数测试\n");
    // TODO

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnRemove_clicked()
{
    QString str = "转换或修改:\n";
    str.append("remove()函数测试\n");
    // TODO

    ui->pteContent->appendPlainText(str);
}

void Widget::on_pbnReplace_clicked()
{
    QString str = "转换或修改:\n";
    str.append("replace()函数测试\n");
    // TODO

    ui->pteContent->appendPlainText(str);
}
