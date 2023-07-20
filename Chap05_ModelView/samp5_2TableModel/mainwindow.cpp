#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QActionGroup>
#include <QFileDialog>
#include <QRegularExpression>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSetting();
    initSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSetting()
{
    // 设置窗口标题
    this->setWindowTitle("QStandardItemModel和QTableView");

    // 初始化指针
    m_model = new QStandardItemModel(1, FixedColumnCount, this);
    m_selection = new QItemSelectionModel(m_model, this);

    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionModel(m_selection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setCentralWidget(ui->splitter);

    // 初始化状态栏标签
    lblCurFile = new QLabel("当前文件:", this);
    lblCurFile->setMinimumWidth(200);

    lblCellPos = new QLabel("当前单元格:", this);
    lblCellPos->setMinimumWidth(180);
    lblCellPos->setAlignment(Qt::AlignHCenter);

    lblCellText = new QLabel("单元格的内容:", this);
    lblCellText->setMinimumWidth(150);

    ui->statusbar->addWidget(lblCurFile);
    ui->statusbar->addWidget(lblCellPos);
    ui->statusbar->addWidget(lblCellText);

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

    // 加载默认文件的数据
    QStringList strContent;
    loadFileData(defaultFile, strContent);
    if (strContent.size() > 0)
        initData(strContent);
}

void MainWindow::loadFileData(QString &aFileName, QStringList &strContent)
{
    // 文件不存在返回
    QFile aFile = QFile(aFileName);
    if (!aFile.exists()) {
        return;
    }
    // 读取文件数据,跳过空行
    aFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str;
    while (!aFile.atEnd()) {
        str = aFile.readLine();
        if (str.trimmed().isEmpty())
            continue;
        strContent.append(str);
    }
    aFile.close();
    lblCurFile->setText("当前文件: " + aFileName);
}
void MainWindow::initData(const QStringList &strContent)
{
    // 转载到tableView
    int rowCount = strContent.size();
    m_model->setRowCount(rowCount - 1); // 总行数减表头

    // 取数据文本文件的第一行作为表头
    QString header = strContent.at(0);
    QStringList headerList = header.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    m_model->setHorizontalHeaderLabels(headerList);

    int j;
    QStandardItem *aItem;
    // 从第二行开始读取数据
    for (int i = 1; i < rowCount; ++i) {
        QString aLineText = strContent.at(i);
        QStringList tmpStrList = aLineText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        // 分割一行数据填充到表格
        for (j = 0; j < FixedColumnCount - 1; ++j) {
            aItem = new QStandardItem(tmpStrList.at(j));
            m_model->setItem(i - 1, j, aItem);
        }

        // 最后一列是与否用checked来显示
        aItem = new QStandardItem(headerList.at(j));
        aItem->setCheckable(true);
        aItem->setBackground(QBrush(Qt::yellow));
        if (tmpStrList.at(j) == "0")
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
        m_model->setItem(i - 1, j, aItem);
    }

    // 设置工具栏按钮可用
    ui->actAppendRow->setEnabled(true);
    ui->actInsertRow->setEnabled(true);
    ui->actDelRow->setEnabled(true);
    ui->actSave->setEnabled(true);
}

void MainWindow::initSlots()
{
    // tableView选择变动
    connect(m_selection, &QItemSelectionModel::currentChanged, this, &MainWindow::do_currentChanged);

    // 样式Action
    connect(ui->actAlignLeft, &QAction::triggered, this, &MainWindow::do_actionAlign_triggerd);
    connect(ui->actAlignCenter, &QAction::triggered, this, &MainWindow::do_actionAlign_triggerd);
    connect(ui->actAlignRight, &QAction::triggered, this, &MainWindow::do_actionAlign_triggerd);

    // 字体Action
    connect(ui->actFontBold, &QAction::triggered, this, &MainWindow::do_actionFont_tridderd);
}

void MainWindow::do_actionAlign_triggerd()
{
    if (!m_selection->hasSelection())
        return; // 没有选择索引直接返回

    QObject *obj = QObject::sender();

    QModelIndexList indexList = m_selection->selectedIndexes();
    for (int i = 0; i < indexList.count(); ++i) {
        QModelIndex aIndex = indexList.at(i);
        QStandardItem *aItem = m_model->itemFromIndex(aIndex);
        if (obj == ui->actAlignLeft) {
            aItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }
        if (obj == ui->actAlignCenter) {
            aItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        }
        if (obj == ui->actAlignRight) {
            aItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        }
    }
}

void MainWindow::do_actionFont_tridderd(bool checked)
{
    if (!m_selection->hasSelection())
        return; // 没有选择索引直接返回

    QObject *obj = QObject::sender();
    QModelIndexList indexList = m_selection->selectedIndexes();
    for (int i = 0; i < indexList.count(); ++i) {
        QModelIndex aIndex = indexList.at(i);
        QStandardItem *aItem = m_model->itemFromIndex(aIndex);
        QFont font = aItem->font();
        font.setBold(checked);
        if (obj == ui->actFontBold) {
            aItem->setFont(font);
        }
    }
}

void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.isValid()) {
        lblCellPos->setText(
            QString::asprintf("当前单元格: %d 行, %d 列", current.row(), current.column()));
        QStandardItem *aItem = m_model->itemFromIndex(current);
        lblCellText->setText("单元格内容: " + aItem->text());
        ui->actFontBold->setChecked(aItem->font().bold());
    }
}

void MainWindow::on_actAppendRow_triggered()
{
    QList<QStandardItem *> aItemList;
    QStandardItem *aItem;
    // 添加一行的item
    for (int i = 0; i < FixedColumnCount - 1; ++i) {
        aItem = new QStandardItem("0");
        aItemList.append(aItem);
    }
    // 添加行的最后一个item,是与否的显示
    QString str = m_model->headerData(m_model->columnCount() - 1, Qt::Horizontal).toString();
    aItem = new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList.append(aItem);

    // 在最后一行插入insertRow,或者直接appendRow
    //        m_model->insertRow(m_model->rowCount(), aItemList);
    m_model->appendRow(aItemList);

    // 索引指向
    QModelIndex curIndex = m_model->index(m_model->rowCount() - 1, 0);
    m_selection->clearSelection();
    m_selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

void MainWindow::on_actInsertRow_triggered()
{
    QModelIndex curIndex = m_selection->currentIndex();
    QList<QStandardItem *> aItemList;
    QStandardItem *aItem;
    // 添加一行的item
    for (int i = 0; i < FixedColumnCount - 1; ++i) {
        aItem = new QStandardItem("0");
        aItemList.append(aItem);
    }
    // 添加行的最后一个item,是与否的显示
    QString str = m_model->headerData(m_model->columnCount() - 1, Qt::Horizontal).toString();
    aItem = new QStandardItem(str);
    aItem->setCheckable(true);
    aItem->setCheckState(Qt::Checked);
    aItemList.append(aItem);

    // 插入行,在当前行前面插入
    m_model->insertRow(curIndex.row(), aItemList);
    m_selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

void MainWindow::on_actDelRow_triggered()
{
    QModelIndex curIndex = m_selection->currentIndex();
    if (curIndex.row() == m_model->rowCount() - 1) {
        m_model->removeRow(curIndex.row());
    } else {
        m_model->removeRow(curIndex.row());
        m_selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
    }
}

void MainWindow::on_actOpen_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this,
                                                     "打开文件",
                                                     curPath,
                                                     "数据文件(*.txt);;所有文件(*.*)");
    if (aFileName.isEmpty()) {
        return;
    }

    QStringList strContent;
    loadFileData(aFileName, strContent); // 加载文件数据
    if (strContent.size() > 0)
        initData(strContent); // 加载到表格
    // 加载到text文本框
    ui->plainTextEdit->clear();
    foreach (const QString &str, strContent) {
        ui->plainTextEdit->appendPlainText(str);
    }
}

void MainWindow::on_actExit_triggered()
{
    this->close();
}

void MainWindow::on_actPreview_triggered()
{
    ui->plainTextEdit->clear();

    QStandardItem *aItem;
    QString str;
    // 获取表头
    for (int i = 0; i < FixedColumnCount; ++i) {
        aItem = m_model->horizontalHeaderItem(i);
        if (aItem == nullptr)
            return; // 表头为空退出
        str += aItem->text() + "\t";
    }
    ui->plainTextEdit->appendPlainText(str.trimmed()); // 去掉最后一个\t

    for (int i = 0; i < m_model->rowCount(); ++i) {
        str = "";
        int j;
        for (j = 0; j < FixedColumnCount - 1; ++j) {
            aItem = m_model->item(i, j);
            if (aItem == nullptr)
                return;
            str += aItem->text() + "\t";
        }
        // 最后一个
        aItem = m_model->item(i, j);
        if (aItem->checkState() == Qt::Checked) {
            str += "1";
        } else {
            str += "0";
        }
        ui->plainTextEdit->appendPlainText(str);
    }
}
