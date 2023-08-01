#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QActionGroup>
#include <QFile>
#include <QFileDialog>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSetting();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSetting()
{
    this->setWindowTitle("使用自定义代理");

    // 初始化状态栏标签
    lblFileName = new QLabel("当前文件:", this);
    lblFileName->setMinimumWidth(200);
    lblIndex = new QLabel("当前项:", this);
    lblIndex->setMinimumWidth(180);
    lblItemText = new QLabel("当前项内容:", this);
    lblItemText->setMinimumWidth(150);
    ui->statusbar->addWidget(lblFileName);
    ui->statusbar->addWidget(lblIndex);
    ui->statusbar->addWidget(lblItemText);

    m_model = new QStandardItemModel(2, FixedColumnCount, this);
    m_selection = new QItemSelectionModel(m_model, this);

    connect(m_selection, &QItemSelectionModel::currentChanged, this, &MainWindow::do_currentChanged);
    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionModel(m_selection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    intSpinDelegate = new TSpinBoxDelegate(this);
    ui->tableView->setItemDelegateForColumn(0, intSpinDelegate); // 第一列设置SpinBox代理
    floatSpinDelegate = new TFloatSpinDelegate(this);
    ui->tableView->setItemDelegateForColumn(1, floatSpinDelegate); // 第二列设置FloatSpinBox
    ui->tableView->setItemDelegateForColumn(2, floatSpinDelegate); // 第三列设置FloatSpinBox
    ui->tableView->setItemDelegateForColumn(3, floatSpinDelegate); // 第四列设置FloatSpinBox

    comboDelegate = new TComboBoxDelegate(this);
    qualityType << "优"
                << "良"
                << "一般"
                << "不合格";
    comboDelegate->setItems(qualityType, false);
    ui->tableView->setItemDelegateForColumn(4, comboDelegate); // 第五列设置ComboBox代理

    // 设置居左居中居右排他单选
    QActionGroup *alignGroup = new QActionGroup(ui->toolBar);
    alignGroup->addAction(ui->actAlignLeft);
    alignGroup->addAction(ui->actAlignCenter);
    alignGroup->addAction(ui->actAlignRight);
    alignGroup->setExclusive(true);
    ui->actAlignLeft->setCheckable(true);
    ui->actAlignCenter->setCheckable(true);
    ui->actAlignRight->setCheckable(true);

    // 设置粗体action可以点击
    ui->actFontBold->setCheckable(true);

    // 加载默认文件数据
    fileName = "JingXie.txt";
    QStringList strContent;
    loadFileData(fileName, strContent);
    if (strContent.count() > 1)
        loadDataForTable(strContent);
    qDebug() << strContent.count();
}

void MainWindow::loadFileData(const QString &fileName, QStringList &strContent)
{
    QFile aFile = QFile(fileName);
    if (!aFile.exists())
        return;
    aFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str;
    while (!aFile.atEnd()) {
        str = aFile.readLine();
        if (str.trimmed().isEmpty())
            continue;
        strContent.append(str);
    }

    aFile.close();
    lblFileName->setText("当前文件: " + fileName);
}

void MainWindow::loadDataForTable(const QStringList &strContent)
{
    m_model->clear();
    m_model->setRowCount(strContent.count());

    QStandardItem *item;
    // 设置表头字段
    QStringList headerList
        = strContent.at(0).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).toList();
    m_model->setHorizontalHeaderLabels(headerList);

    for (int i = 1; i < strContent.count(); ++i) {
        QStringList rowList
            = strContent.at(i).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).toList();
        for (int j = 0; j < FixedColumnCount - 1; ++j) {
            item = new QStandardItem(rowList.at(j));
            m_model->setItem(i, j, item);
        }

        item = new QStandardItem(headerList.at(FixedColumnCount - 1));
        item->setCheckable(true);
        item->setBackground(QBrush(Qt::yellow));
        if (rowList.last() == "1")
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        m_model->setItem(i, FixedColumnCount - 1, item);
    }
}

void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.isValid()) {
        lblIndex->setText(
            QString::asprintf("当前单元格: %d 行, %d 列", current.row(), current.column()));
        QStandardItem *aItem = m_model->itemFromIndex(current);
        lblItemText->setText("单元格内容: " + aItem->text());
        ui->actFontBold->setChecked(aItem->font().bold());
    }
}

void MainWindow::on_actOpen_triggered()
{
    QString appDir = QApplication::applicationDirPath();

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "打开数据文件",
                                                    appDir,
                                                    "数据文件(*.txt);;所有文件(*.*)");
    if (fileName.isEmpty())
        return;
    QStringList strContent;
    loadFileData(fileName, strContent);
    loadDataForTable(strContent);
    ui->plainTextEdit->clear();
    foreach (const QString &str, strContent) {
        ui->plainTextEdit->appendPlainText(str);
    }
}

void MainWindow::on_actPreview_triggered()
{
    QString str;
    QStandardItem *item;
    for (int i = 0; i < FixedColumnCount; ++i) {
        item = m_model->horizontalHeaderItem(i);
        if (item == nullptr)
            return;
        str += item->text() + "\t";
    }
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(str.trimmed());

    for (int i = 1; i < m_model->rowCount(); ++i) {
        str = "";
        for (int j = 0; j < m_model->columnCount() - 1; ++j) {
            item = m_model->item(i, j);
            if (item == nullptr)
                return;
            str += item->text() + "\t";
        }

        item = m_model->item(i, m_model->columnCount() - 1);
        if (item->checkState() == Qt::Checked)
            str += "1";
        else
            str += "0";
        ui->plainTextEdit->appendPlainText(str.trimmed());
    }
}

void MainWindow::on_acAlignLeft_triggered()
{
    if (!m_selection->hasSelection())
        return; // 没有选择索引直接返回

    QModelIndexList indexList = m_selection->selectedIndexes();
    for (int i = 0; i < indexList.count(); ++i) {
        QModelIndex aIndex = indexList.at(i);
        QStandardItem *aItem = m_model->itemFromIndex(aIndex);

        aItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
}

void MainWindow::on_acAlignCenter_triggered()
{
    if (!m_selection->hasSelection())
        return; // 没有选择索引直接返回

    QModelIndexList indexList = m_selection->selectedIndexes();
    for (int i = 0; i < indexList.count(); ++i) {
        QModelIndex aIndex = indexList.at(i);
        QStandardItem *aItem = m_model->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    }
}

void MainWindow::on_acAlignRight_triggered()
{
    if (!m_selection->hasSelection())
        return; // 没有选择索引直接返回

    QModelIndexList indexList = m_selection->selectedIndexes();
    for (int i = 0; i < indexList.count(); ++i) {
        QModelIndex aIndex = indexList.at(i);
        QStandardItem *aItem = m_model->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}

void MainWindow::on_actFontBold_triggered()
{
    if (!m_selection->hasSelection())
        return; // 没有选择索引直接返回

    QModelIndexList indexList = m_selection->selectedIndexes();
    for (int i = 0; i < indexList.count(); ++i) {
        QModelIndex aIndex = indexList.at(i);
        QStandardItem *aItem = m_model->itemFromIndex(aIndex);
        QFont font = aItem->font();
        font.setBold(ui->actFontBold->isChecked());
        aItem->setFont(font);
    }
}

void MainWindow::on_actExit_triggered()
{
    this->close();
}

void MainWindow::on_actAppend_triggered()
{
    QList<QStandardItem *> itemList;
    itemList << new QStandardItem("0") << new QStandardItem("0.00") << new QStandardItem("0.0")
             << new QStandardItem("0.00") << new QStandardItem(qualityType.at(1));
    QString str = m_model->horizontalHeaderItem(FixedColumnCount - 1)->text(); // 最后一列字段checked
    QStandardItem *item = new QStandardItem(str);
    item->setCheckable(true);
    item->setCheckState(Qt::Checked);
    itemList.append(item);

    m_model->appendRow(itemList);

    QModelIndex curIndex = m_model->index(m_model->rowCount(), 0);
    m_selection->clearSelection();
    m_selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

void MainWindow::on_actInsert_triggered()
{
    QModelIndex curIndex = m_selection->currentIndex();

    QList<QStandardItem *> itemList;
    itemList << new QStandardItem("0") << new QStandardItem("0.00") << new QStandardItem("0.0")
             << new QStandardItem("0.00") << new QStandardItem(qualityType.at(0));
    QString str = m_model->horizontalHeaderItem(FixedColumnCount - 1)->text(); // 最后一列字段checked
    QStandardItem *item = new QStandardItem(str);
    item->setCheckable(true);
    item->setCheckState(Qt::Unchecked);
    itemList.append(item);

    m_model->insertRow(curIndex.row(), itemList);
    m_selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

void MainWindow::on_actDel_triggered()
{
    QModelIndex curIndex = m_selection->currentIndex();
    if (curIndex.row() == m_model->rowCount() - 1) {
        m_model->removeRow(curIndex.row());

    } else {
        m_model->removeRow(curIndex.row());
        m_selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
    }
}
