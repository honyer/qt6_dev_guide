#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QListWidget的使用");
    this->setCentralWidget(ui->splitter);

    initSlots();
    setActionsForButton();
    createSelectionMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActionsForButton()
{
    // 左侧ToolBox的ToolButton添加Action
    ui->tbnListInit->setDefaultAction(ui->actListInit);
    ui->tbnListClear->setDefaultAction(ui->actListClear);
    ui->tbnListInsert->setDefaultAction(ui->actListInsert);
    ui->tbnListAppend->setDefaultAction(ui->actListAppend);
    ui->tbnListDelete->setDefaultAction(ui->actListDel);

    // ListWidget上方的ToolButton添加Action
    ui->tbnSelAll->setDefaultAction(ui->actSelAll);
    ui->tbnSelNone->setDefaultAction(ui->actSelNone);
    ui->tbnSelInvs->setDefaultAction(ui->actSelInvs);
}

void MainWindow::createSelectionMenu()
{
    // 创建下拉菜单
    QMenu *menuSelection = new QMenu(this);
    menuSelection->addAction(ui->actSelAll);
    menuSelection->addAction(ui->actSelNone);
    menuSelection->addAction(ui->actSelInvs);

    // ListWidget上方的项选择菜单
    ui->tbnSelection->setPopupMode(QToolButton::MenuButtonPopup); // 菜单弹出模式
    ui->tbnSelection->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tbnSelection->setDefaultAction(ui->actSelPopMenu);
    ui->tbnSelection->setMenu(menuSelection);

    // 工具栏上的"项选择"按钮
    QToolButton *tbnSelectionW = new QToolButton(this); // 和list上方的一样
    tbnSelectionW->setPopupMode(QToolButton::InstantPopup);
    tbnSelectionW->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tbnSelectionW->setDefaultAction(ui->actSelPopMenu);
    tbnSelectionW->setMenu(menuSelection);
    ui->toolBar->addWidget(tbnSelectionW);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actQuit);
}

void MainWindow::do_listAction_trigled()
{
    QObject *obj = QObject::sender();

    // 预设内容
    QListWidgetItem *aItem;
    QIcon icon = QIcon(":/icons/check2.ico");
    Qt::ItemFlags flags;
    if (ui->cbxEditable->isChecked()) {
        flags = Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable
                | Qt::ItemIsEnabled;
    } else {
        flags = Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    }
    QString str;

    // 初始化
    if (obj == ui->actListInit) {
        ui->listWidget->clear();
        for (int i = 0; i < 10; ++i) {
            str = QString("Item %1").arg(i);
            aItem = new QListWidgetItem();
            aItem->setText(str);
            aItem->setIcon(icon);
            aItem->setCheckState(Qt::Checked);
            aItem->setFlags(flags);
            ui->listWidget->addItem(aItem);
        }
    }

    // 清空
    if (obj == ui->actListClear) {
        ui->listWidget->clear();
    }

    // 插入项
    if (obj == ui->actListInsert) {
        str = "Inserted Item";
        aItem = new QListWidgetItem();
        aItem->setText(str);
        aItem->setIcon(icon);
        aItem->setCheckState(Qt::Checked);
        aItem->setFlags(flags);
        ui->listWidget->insertItem(ui->listWidget->currentRow(), aItem);
    }

    // 添加项
    if (obj == ui->actListAppend) {
        str = "Append Item";
        aItem = new QListWidgetItem();
        aItem->setText(str);
        aItem->setIcon(icon);
        aItem->setCheckState(Qt::Checked);
        aItem->setFlags(flags);
        ui->listWidget->addItem(aItem);
    }

    // 删除项
    if (obj == ui->actListDel) {
        int row = ui->listWidget->currentRow();
        aItem = ui->listWidget->takeItem(row);
        delete aItem;
    }
}

void MainWindow::do_listItem_Selection()
{
    QObject *obj = QObject::sender();

    QList<QListWidgetItem *> itemList;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        itemList.append(ui->listWidget->item(i));
    }

    //全选
    if (obj == ui->actSelAll) {
        foreach (QListWidgetItem *item, itemList) {
            item->setCheckState(Qt::Checked);
        }
    }

    // 全不选
    if (obj == ui->actSelNone) {
        foreach (QListWidgetItem *item, itemList) {
            item->setCheckState(Qt::Unchecked);
        }
    }

    // 反选
    if (obj == ui->actSelInvs) {
        foreach (QListWidgetItem *item, itemList) {
            if (item->checkState() == Qt::Unchecked) {
                item->setCheckState(Qt::Checked);
            } else {
                item->setCheckState(Qt::Unchecked);
            }
        }
    }
}

void MainWindow::do_tbnSort_clicked(bool checked)
{
    QObject *obj = QObject::sender();

    // 是否允许排序
    if (obj == ui->cbxSorting) {
        ui->listWidget->setSortingEnabled(checked);
    }

    // 正序排序
    if (obj == ui->tbnSortAsc) {
        ui->listWidget->sortItems(Qt::AscendingOrder);
    }

    // 反序排序
    if (obj == ui->tbnSortDes) {
        ui->listWidget->sortItems(Qt::DescendingOrder);
    }
}

void MainWindow::initSlots()
{
    // 绑定listWidget的初始化、清除、插入、添加、删除操作到槽函数
    connect(ui->actListInit, &QAction::triggered, this, &MainWindow::do_listAction_trigled);
    connect(ui->actListClear, &QAction::triggered, this, &MainWindow::do_listAction_trigled);
    connect(ui->actListInsert, &QAction::triggered, this, &MainWindow::do_listAction_trigled);
    connect(ui->actListAppend, &QAction::triggered, this, &MainWindow::do_listAction_trigled);
    connect(ui->actListDel, &QAction::triggered, this, &MainWindow::do_listAction_trigled);

    // 绑定选择：全选、反选、不选操作到槽函数
    connect(ui->actSelAll, &QAction::triggered, this, &MainWindow::do_listItem_Selection);
    connect(ui->actSelNone, &QAction::triggered, this, &MainWindow::do_listItem_Selection);
    connect(ui->actSelInvs, &QAction::triggered, this, &MainWindow::do_listItem_Selection);

    // 排序槽函数
    connect(ui->cbxSorting, &QCheckBox::clicked, this, &MainWindow::do_tbnSort_clicked);
    connect(ui->tbnSortAsc, &QToolButton::clicked, this, &MainWindow::do_tbnSort_clicked);
    connect(ui->tbnSortDes, &QToolButton::clicked, this, &MainWindow::do_tbnSort_clicked);
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current,
                                                  QListWidgetItem *previous)
{
    QString str;
    if (current != nullptr) {
        if (previous == nullptr) {
            str = "当前：" + current->text();
        } else {
            str = "前一项：" + previous->text() + "; 当前项：" + current->text();
        }
        ui->lineEdit->setText(str);
    }
    ui->plainTextEdit->appendPlainText("信号：currentItemChanged() 被发射");
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->plainTextEdit->appendPlainText(
        QString("信号：currentRowChanged() 被发射，currentRow=%1").arg(currentRow));
}

void MainWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->plainTextEdit->appendPlainText("信号：currentTextChanged() 被发射,currentText=%1"
                                       + currentText);
}

void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("信号：itemChanged() 被发射,当前item=" + item->text());
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    ui->plainTextEdit->appendPlainText("信号：itemSelectionChanged() 被发射");
}

void MainWindow::on_tbnTextClear_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_tbnTextAddLine_clicked()
{
    ui->plainTextEdit->appendPlainText("");
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);

    QMenu *menuList = new QMenu(this);

    menuList->addAction(ui->actListInit);
    menuList->addAction(ui->actListClear);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListDel);
    menuList->addSeparator();
    menuList->addAction(ui->actSelAll);
    menuList->addAction(ui->actSelNone);
    menuList->addAction(ui->actSelInvs);

    menuList->exec(QCursor::pos());
    delete menuList;
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Qt::ItemFlags flags = item->flags();
    if (ui->cbxEditable->isChecked()) {
        flags = flags | Qt::ItemIsEditable;
        item->setFlags(flags); // 将可编辑的flag设置回去，否则无法编辑
        ui->listWidget->editItem(item);
    } else {
        flags = flags = flags & ~Qt::ItemIsEditable;
    }
}
