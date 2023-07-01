#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("QComboBox的使用");

    connect(ui->cbxList, &QComboBox::currentIndexChanged, this, &Widget::do_cbxitem_indexChanged);
    connect(ui->cbxCity, &QComboBox::currentIndexChanged, this, &Widget::do_cbxitem_indexChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pbnClearContent_clicked()
{
    ui->pteContent->clear();
}

void Widget::on_pbnInitList_clicked()
{
    QIcon icon;
    icon.addFile(":/icons/aim.ico");
    ui->cbxList->clear();

    QStringList list;
    for (int i = 0; i < 20; ++i) {
        list.append(QString("Item%1").arg(i));
    }
    ui->cbxList->addItems(list);

    for (int i = 0; i < 20; ++i) {
        if (i % 2 == 0) {
            ui->cbxList->setItemIcon(i, icon);
        }
    }
}

void Widget::on_pbnClearList_clicked()
{
    ui->cbxList->clear();
}

void Widget::on_pbnInitCityCode_clicked()
{
    QMap<QString, int> city_zone;
    city_zone.insert("北京", 10);
    city_zone.insert("上海", 21);
    city_zone.insert("天津", 22);
    city_zone.insert("广州", 20);
    city_zone.insert("成都", 28);
    city_zone.insert("深圳", 755);
    city_zone.insert("武汉", 27);
    city_zone.insert("大连", 411);
    city_zone.insert("福州", 591);
    city_zone.insert("青岛", 532);

    foreach (const QString &str, city_zone.keys()) {
        ui->cbxCity->addItem(str, city_zone.value(str));
    }
}

void Widget::on_cbxEditable_clicked(bool checked)
{
    ui->cbxList->setEditable(checked);
}

void Widget::do_cbxitem_indexChanged()
{
    QObject *obj = QObject::sender();
    QString str;
    if (obj == ui->cbxList) {
        str = ui->cbxList->currentText();
    } else if (obj == ui->cbxCity) {
        str = QString(ui->cbxCity->currentText())
              + "：区号 = " + ui->cbxCity->currentData().toString();
    }
    ui->pteContent->appendPlainText(str);
}
