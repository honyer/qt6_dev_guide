#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settingUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::settingUi()
{
    lblCellIndex = new QLabel("当前单元格坐标:", this);
    lblCellIndex->setMinimumWidth(200);

    lblCellIndex = new QLabel("当前单元格类型:", this);
    lblCellType->setMinimumWidth(200);

    lblStuId = new QLabel("学生ID:", this);
    lblStuId->setMinimumWidth(200);

    ui->statusbar->addWidget(lblCellIndex);
    ui->statusbar->addWidget(lblCellType);
    ui->statusbar->addWidget(lblStuId);
}

void MainWindow::createItemsARow(
    int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score)
{}

void MainWindow::on_pbnSetHeader_clicked()
{
    QStringList headerText;
    headerText << "姓名"
               << "性别"
               << "出生日期"
               << "民族"
               << "分数"
               << "是否党员";
    qDebug() << headerText;
}

void MainWindow::on_pbnSetRows_clicked() {}

void MainWindow::on_pbnInitData_clicked() {}

void MainWindow::on_pbnInsertRow_clicked() {}

void MainWindow::on_pbnDelCurRow_clicked() {}

void MainWindow::on_pbnAutoHeight_clicked() {}

void MainWindow::on_pbnAutoWidth_clicked() {}

void MainWindow::on_pbnLoadTableToText_clicked() {}
