#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QModelIndex>

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
    delete m_model;
    delete ui;
}

void MainWindow::initSetting()
{
    // 初始化数据转载到model并显示在listView
    m_strList << "北京"
              << "上海"
              << "天津"
              << "重庆"
              << "河北"
              << "山东"
              << "四川"
              << "广东"
              << "湖南";
    m_model = new QStringListModel(this);
    m_model->setStringList(m_strList);
    ui->listView->setModel(m_model);

    // 设置界面UI
    this->setWindowTitle("QStringListModel和QListView");
    ui->cbxEditable->setCheckState(Qt::Checked);
    ui->pbnSort->setCheckable(true);
}

void MainWindow::initSlots()
{
    // 恢复列表,清除列表,允许编辑
    connect(ui->pbnRecovery,
            &QPushButton::clicked,
            this,
            &MainWindow::do_listView_pushButton_Clicked);
    connect(ui->pbnClearList,
            &QPushButton::clicked,
            this,
            &MainWindow::do_listView_pushButton_Clicked);
    connect(ui->cbxEditable, &QCheckBox::clicked, this, &MainWindow::do_listView_pushButton_Clicked);

    // 添加项,插入项,删除项
    connect(ui->pbnAddItem,
            &QPushButton::clicked,
            this,
            &MainWindow::do_listView_pushButton_Clicked);
    connect(ui->pbnInsertItem,
            &QPushButton::clicked,
            this,
            &MainWindow::do_listView_pushButton_Clicked);
    connect(ui->pbnDeleteItem,
            &QPushButton::clicked,
            this,
            &MainWindow::do_listView_pushButton_Clicked);

    // 上移,下移,排序
    connect(ui->pbnMoveUp, &QPushButton::clicked, this, &MainWindow::do_listView_pushButton_Clicked);
    connect(ui->pbnMoveDown,
            &QPushButton::clicked,
            this,
            &MainWindow::do_listView_pushButton_Clicked);
    connect(ui->pbnSort, &QPushButton::clicked, this, &MainWindow::do_listView_pushButton_Clicked);

    // 清空文本编辑框,显示listview到编辑框
    connect(ui->pbnClearText,
            &QPushButton::clicked,
            this,
            &MainWindow::do_plainText_pushButton_Clicked);
    connect(ui->pbnShowListStr,
            &QPushButton::clicked,
            this,
            &MainWindow::do_plainText_pushButton_Clicked);
}

void MainWindow::do_listView_pushButton_Clicked()
{
    QObject *obj = QObject::sender();
    if (obj == ui->pbnRecovery)
        m_model->setStringList(m_strList);
    if (obj == ui->pbnClearList)
        m_model->removeRows(0, m_model->rowCount());
    if (obj == ui->cbxEditable) {
        if (ui->cbxEditable->isChecked()) {
            ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked
                                          | QAbstractItemView::SelectedClicked);
        } else
            ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    // 增加,插入,删除
    if (obj == ui->pbnAddItem) {
        m_model->insertRow(m_model->rowCount());
        QModelIndex index = m_model->index(m_model->rowCount() - 1, 0);
        m_model->setData(index, "New Item", Qt::DisplayRole);
        ui->listView->setCurrentIndex(index);
    }
    if (obj == ui->pbnInsertItem) {
        QModelIndex index = ui->listView->currentIndex();
        m_model->insertRow(index.row());
        m_model->setData(index, "Inserted Item", Qt::DisplayRole);
        ui->listView->setCurrentIndex(index);
    }
    if (obj == ui->pbnDeleteItem) {
        QModelIndex index = ui->listView->currentIndex();
        m_model->removeRow(index.row());
    }

    // 上移,下移,排序
    if (obj == ui->pbnMoveUp) {
        int curRow = ui->listView->currentIndex().row(); //当前行号
        QModelIndex index = QModelIndex();
        m_model->moveRow(index, curRow, index, curRow - 1);
    }
    if (obj == ui->pbnMoveDown) {
        int curRow = ui->listView->currentIndex().row();
        QModelIndex index = QModelIndex();
        m_model->moveRow(index, curRow, index, curRow + 2);
    }
    if (obj == ui->pbnSort) {
        if (ui->pbnSort->isChecked()) {
            m_model->sort(0, Qt::AscendingOrder);
        } else
            m_model->sort(0, Qt::DescendingOrder);
    }
}

void MainWindow::do_plainText_pushButton_Clicked()
{
    QObject *obj = QObject::sender();

    if (obj == ui->pbnClearText)
        ui->plainTextEdit->clear();

    if (obj == ui->pbnShowListStr) {
        QString str;
        for (int i = 0; i < m_model->rowCount(); ++i) {
            QModelIndex index = m_model->index(i);
            str += m_model->data(index).toString() + "\n";
        }

        ui->plainTextEdit->setPlainText(str);
    }
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString str = QString::asprintf("模型索引:row=%d, column=%d; ", index.row(), index.column());
    QVariant var = m_model->data(index);
    ui->statusbar->showMessage(str + var.toString());
}
