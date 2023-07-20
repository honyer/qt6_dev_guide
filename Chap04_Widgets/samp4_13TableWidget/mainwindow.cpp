#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QRandomGenerator>

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

    lblCellType = new QLabel("当前单元格类型:", this);
    lblCellType->setMinimumWidth(200);

    lblStuId = new QLabel("学生ID:", this);
    lblStuId->setMinimumWidth(200);

    ui->statusbar->addWidget(lblCellIndex);
    ui->statusbar->addWidget(lblCellType);
    ui->statusbar->addWidget(lblStuId);
}

void MainWindow::createItemsARow(
    int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score)
{
    // 学号
    uint studId=202105000;
    QTableWidgetItem *item=new QTableWidgetItem(name,MainWindow::ctName);
    studId += rowNo;
    item->setData(Qt::UserRole, QVariant(studId));
    ui->tblContent->setItem(rowNo, MainWindow::colName, item);

    // 性别
    QIcon icon;
    if (sex == "男") {
        icon.addFile(":/icons/boy.ico");
    } else {
        icon.addFile(":/icons/girl.ico");
    }
    item = new QTableWidgetItem(sex, MainWindow::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    item->setFlags(flags);
    ui->tblContent->setItem(rowNo, MainWindow::colSex, item);

    // 出生日期
    QString str = birth.toString("yyyy-MM-dd");
    item = new QTableWidgetItem(str, MainWindow::ctBirth);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tblContent->setItem(rowNo, MainWindow::colBirth, item);

    // 民族
    item = new QTableWidgetItem(nation, MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tblContent->setItem(rowNo, MainWindow::colNation, item);

    // 是否党员
    item = new QTableWidgetItem("党员", MainWindow::ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    flags = Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    item->setFlags(flags);
    if (isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    item->setBackground(QBrush(Qt::yellow));
    ui->tblContent->setItem(rowNo, MainWindow::colPartyM, item);

    // 分数
    str.setNum(score);
    item = new QTableWidgetItem(str, MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tblContent->setItem(rowNo, MainWindow::colScore, item);
}

void MainWindow::on_pbnSetHeader_clicked()
{
    QStringList headerText;
    headerText << "姓名"
               << "性别"
               << "出生日期"
               << "民族"
               << "分数"
               << "是否党员";
    ui->tblContent->setColumnCount(headerText.size());
    ui->tblContent->setHorizontalHeaderLabels(headerText); // 一次性设置表头文本

    // 个性化设置表头
//    for (int i = 0; i < ui->tblContent->columnCount(); ++i) {
//        QTableWidgetItem *headerItem=new QTableWidgetItem(headerText.at(i));// 创建表头
//        QFont font =headerItem->font();// 获取初始字体
//        font.setBold(true);// 设置粗体
//        font.setPointSize(11);
//        headerItem->setForeground(QBrush(Qt::red));
//        headerItem->setFont(font);
//        ui->tblContent->setHorizontalHeaderItem(i,headerItem);

//    }
}

void MainWindow::on_pbnSetRows_clicked()
{
    // 设置表的行数
    ui->tblContent->setRowCount(ui->sbxRowCount->value());
    ui->tblContent->setAlternatingRowColors(ui->cbxRowColor->isChecked());
}

void MainWindow::on_pbnInitData_clicked() {
    QDate birth(2001,4,6);
    ui->tblContent->clearContents();// 只清除表格内容
    for (int i = 0; i < ui->tblContent->rowCount(); ++i) {
        QString strName=QString("学生%1").arg(i);
        QString strSex=((i%2)==0)?"男":"女";
        bool isParty=((i%2)==0)?true:false;
        int score=QRandomGenerator::global()->bounded(60,100);
        createItemsARow(i, strName, strSex, birth, "汉族", isParty, score);
        qDebug() << i;
    }
}

void MainWindow::on_pbnInsertRow_clicked()
{
    // 获取当前行号,并调用插入函数createItemsARow
    int curRow = ui->tblContent->currentRow();
    ui->tblContent->insertRow(curRow);
    createItemsARow(curRow, "新学生", "男", QDate(2022, 7, 1), "苗族", true, 80);
}

void MainWindow::on_pbnApendRow_clicked()
{
    int curRow = ui->tblContent->rowCount();
    ui->tblContent->insertRow(curRow);

    createItemsARow(curRow, "新生", "女", QDate(2022, 7, 2), "布依族", false, 78);
}

void MainWindow::on_pbnDelCurRow_clicked()
{
    int curRow = ui->tblContent->currentRow();
    ui->tblContent->removeRow(curRow);
}

void MainWindow::on_pbnAutoHeight_clicked()
{
    ui->tblContent->resizeRowsToContents();
}

void MainWindow::on_pbnAutoWidth_clicked()
{
    ui->tblContent->resizeColumnsToContents();
}

void MainWindow::on_pbnLoadTableToText_clicked()
{
    QTableWidgetItem *item;
    ui->pteContent->clear();
    for (int i = 0; i < ui->tblContent->rowCount(); ++i) {
        QString str = QString::asprintf("第 %d 行:", i + 1);
        for (int j = 0; j < ui->tblContent->columnCount(); ++j) {
            // 如果当前列是是否党员,跳过
            if (j == MainWindow::colPartyM)
                continue;
            item = ui->tblContent->item(i, j);
            str += item->text() + " ";
        }

        // 党员当前列单独显示
        item = ui->tblContent->item(i, MainWindow::colPartyM);
        if (item->checkState() == Qt::Checked)
            str += "党员";
        else
            str += "群众";
        ui->pteContent->appendPlainText(str);
    }
}

void MainWindow::on_tblContent_currentCellChanged(int currentRow,
                                                  int currentColumn,
                                                  int previousRow,
                                                  int previousColumn)
{
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);

    QTableWidgetItem *item = ui->tblContent->item(currentRow, currentColumn);
    if (item == nullptr)
        return;
    lblCellIndex->setText(
        QString::asprintf("当前单元格坐标: %d 行, %d 列", currentRow, currentColumn));
    int cellType = item->type();
    lblCellType->setText(QString::asprintf("当前单元格类型: %d", cellType));

    item = ui->tblContent->item(currentRow, MainWindow::colName);
    uint ID = item->data(Qt::UserRole).toUInt();
    lblStuId->setText(QString::asprintf("学生ID: %d", ID));
}

void MainWindow::on_cbxTableEditable_clicked(bool checked)
{
    if (checked)
        ui->tblContent->setEditTriggers(QAbstractItemView::DoubleClicked
                                        | QAbstractItemView::SelectedClicked);
    else
        ui->tblContent->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void MainWindow::on_cbxRowColor_clicked(bool checked)
{
    ui->tblContent->setAlternatingRowColors(checked);
}

void MainWindow::on_cbxHeaderH_clicked(bool checked)
{
    ui->tblContent->horizontalHeader()->setVisible(checked);
}

void MainWindow::on_cbxHeaderV_clicked(bool checked)
{
    ui->tblContent->verticalHeader()->setVisible(checked);
}

void MainWindow::on_rbxSelectRow_clicked()
{
    ui->tblContent->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void MainWindow::on_rbnSelectColumn_clicked()
{
    ui->tblContent->setSelectionBehavior(QAbstractItemView::SelectColumns);
}
