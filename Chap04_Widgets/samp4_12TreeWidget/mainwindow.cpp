#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TreeWidget的使用");

    settingUI();
    initSlots();
    buildTreeHeader();
    initTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_actFiles_triggered()
{
    QObject *obj = QObject::sender();

    if (obj == ui->actAddFolder) {
        QString dir = QFileDialog::getExistingDirectory();
        if (dir.isEmpty()) {
            return;
        }
        QTreeWidgetItem *currentItem = ui->treeFiles->currentItem();
        if (currentItem == nullptr) {
            return;
        }
        if (currentItem->type() != MainWindow::itImageItem) {
            addFolderItem(currentItem, dir);
        }
    }

    // 添加图片Action
    if (obj == ui->actAddFiles) {
        QFileDialog filesDlg;
        filesDlg.setFileMode(QFileDialog::ExistingFiles);
        filesDlg.setNameFilter("图片格式 (*.jpg *.png *.bmp)");

        QStringList files;
        if (filesDlg.exec()) {
            files = filesDlg.selectedFiles();
        }
        if (files.isEmpty())
            return;

        QTreeWidgetItem *parrentItem, *item;
        // item指向当前选择的项,如果为空则指向toplevel的第一项
        item = ui->treeFiles->currentItem();
        if (item == nullptr) {
            item = ui->treeFiles->topLevelItem(0);
        }
        // 如果当前的item是图片节点,这parrentItem指向其父节点,否则父节点和item是一样
        if (item->type() == MainWindow::itImageItem) {
            parrentItem = item->parent();
        } else {
            parrentItem = item;
        }

        foreach (const QString &file, files) {
            addImageItem(parrentItem, file);
        }
        // 展开父节点
        parrentItem->setExpanded(true);
    }
}

void MainWindow::do_treeNodeAct_triggered()
{
    QObject *obj = QObject::sender();

    // 删除节点信号
    if (obj == ui->actDelItem) {
        QTreeWidgetItem *item = ui->treeFiles->currentItem();
        if (item == nullptr) {
            return;
        }
        QTreeWidgetItem *parrentItem = item->parent();
        deleteItem(parrentItem, item);
    }

    // 遍历节点信号
    if (obj == ui->actScanItems) {
        QTreeWidgetItem *item = ui->treeFiles->currentItem();
        if (item == nullptr) {
            return;
        }
        changeItemCaption(item);
    }
}

void MainWindow::do_actZoom_triggered()
{
    QObject *obj = QObject::sender();

    // m_pixmap信息
    int realH = m_pixmap.height();
    int realW = m_pixmap.width();

    double ratio = 0.2; // 放大缩小比例
    QPixmap pix;

    // 适应高度
    if (obj == ui->actZoomFitH) {
        int H = ui->scrollArea->height();
        m_ratio = float(H) / realH; // 初始化比例
        pix = m_pixmap.scaledToHeight(H - 38);
    }

    // 适应宽度
    if (obj == ui->actZoomFitW) {
        int W = ui->scrollArea->width();
        pix = m_pixmap.scaledToWidth(W - 38);
    }

    // 放大
    if (obj == ui->actZoomIn) {
        m_ratio *= (1 + ratio);
        int h = m_ratio * realH;
        int w = m_ratio * realW;
        pix = m_pixmap.scaled(w, h);
    }

    // 缩小
    if (obj == ui->actZoomOut) {
        m_ratio *= (1 - ratio);
        int h = m_ratio * realH;
        int w = m_ratio * realW;
        pix = m_pixmap.scaled(w, h);
    }

    // 实际大小
    if (obj == ui->actZoomResize) {
        m_ratio = 1;
        pix = m_pixmap;
    }

    sbxRatio->setValue(100 * m_ratio);
    ui->lblImage->setPixmap(pix);
}

void MainWindow::settingUI()
{
    // 状态栏的lblNodeText
    lblNodeText = new QLabel("节点标题", this);
    lblNodeText->setMinimumWidth(200);
    ui->statusbar->addWidget(lblNodeText);

    // 状态栏的sbxRatio
    sbxRatio = new QSpinBox(this);
    sbxRatio->setRange(0, 2000);
    sbxRatio->setValue(100);
    sbxRatio->setSuffix(" %");
    sbxRatio->setButtonSymbols(QAbstractSpinBox::NoButtons);
    sbxRatio->setReadOnly(true);
    ui->statusbar->addPermanentWidget(sbxRatio);

    lblFileName = new QLabel("文件名", this);
    ui->statusbar->addPermanentWidget(lblFileName);

    this->setCentralWidget(ui->scrollArea);
}

void MainWindow::buildTreeHeader()
{
    ui->treeFiles->clear();
    QTreeWidgetItem *header = new QTreeWidgetItem();
    header->setText(MainWindow::colItem, "目录和文件");
    header->setText(MainWindow::colItemType, "节点类型");
    header->setText(MainWindow::colDate, "最后修改日期");
    header->setTextAlignment(colItem, Qt::AlignHCenter | Qt::AlignVCenter);
    header->setTextAlignment(colItemType, Qt::AlignHCenter | Qt::AlignVCenter);
    ui->treeFiles->setHeaderItem(header);
}

void MainWindow::initTree()
{
    QIcon icon(":/icons/15.ico");
    QTreeWidgetItem *top = new QTreeWidgetItem(MainWindow::itTopItem);
    top->setIcon(MainWindow::colItem, icon);
    top->setText(MainWindow::colItem, "图片");
    top->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsAutoTristate
                  | Qt::ItemIsEnabled);
    top->setCheckState(MainWindow::colItem, Qt::Checked);
    ui->treeFiles->addTopLevelItem(top);
}

void MainWindow::initSlots()
{
    // 绑定添加文件夹、添加文件
    connect(ui->actAddFolder, &QAction::triggered, this, &MainWindow::do_actFiles_triggered);
    connect(ui->actAddFiles, &QAction::triggered, this, &MainWindow::do_actFiles_triggered);

    // 绑定删除节点、遍历节点
    connect(ui->actDelItem, &QAction::triggered, this, &MainWindow::do_treeNodeAct_triggered);
    connect(ui->actScanItems, &QAction::triggered, this, &MainWindow::do_treeNodeAct_triggered);

    // 绑定图片放大缩小适应宽度和高度操作
    connect(ui->actZoomFitH, &QAction::triggered, this, &MainWindow::do_actZoom_triggered);
    connect(ui->actZoomFitW, &QAction::triggered, this, &MainWindow::do_actZoom_triggered);
    connect(ui->actZoomResize, &QAction::triggered, this, &MainWindow::do_actZoom_triggered);
    connect(ui->actZoomIn, &QAction::triggered, this, &MainWindow::do_actZoom_triggered);
    connect(ui->actZoomOut, &QAction::triggered, this, &MainWindow::do_actZoom_triggered);

    // 当窗口大小变化,自动触发适应高度的事件
    connect(this, &MainWindow::windowResized, ui->actZoomFitH, &QAction::trigger);
}

void MainWindow::addFolderItem(QTreeWidgetItem *parentItem, QString dir)
{
    QIcon icon(":/icons/open3.bmp");
    QString strNode = dir.section("/", -1, -1);

    QTreeWidgetItem *item = new QTreeWidgetItem(MainWindow::itGroupItem);
    item->setIcon(MainWindow::colItem, icon);
    item->setText(MainWindow::colItem, strNode);
    item->setText(MainWindow::colItemType, "Group Item");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsAutoTristate
                   | Qt::ItemIsEnabled);
    item->setCheckState(MainWindow::colItem, Qt::Checked);
    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dir));
    parentItem->addChild(item);
}

void MainWindow::addImageItem(QTreeWidgetItem *parentItem, QString fileName)
{
    QIcon icon(":/icons/31.ico");
    QFileInfo fileInfo(fileName);
    QString strNode = fileInfo.fileName();
    QDateTime birthDate = fileInfo.lastModified();

    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(MainWindow::itImageItem);
    item->setIcon(MainWindow::colItem, icon);
    item->setText(MainWindow::colItem, strNode);
    item->setText(MainWindow::colItemType, "Image Item");
    item->setText(MainWindow::colDate, birthDate.toString("yyyy/MM/dd"));
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsAutoTristate
                   | Qt::ItemIsEnabled);
    item->setCheckState(MainWindow::colItem, Qt::Checked);
    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(fileName));
    parentItem->addChild(item);
}

void MainWindow::displayImage(QTreeWidgetItem *item)
{
    QString fileName = item->data(MainWindow::colItem, Qt::UserRole).toString();
    lblFileName->setText(fileName);
    lblNodeText->setText(item->text(MainWindow::colItem));

    // 加载图片
    m_pixmap.load(fileName);
    ui->actZoomIn->setEnabled(true);
    ui->actZoomOut->setEnabled(true);
    ui->actZoomResize->setEnabled(true);
    ui->actZoomFitH->setEnabled(true);
    ui->actZoomFitW->setEnabled(true);

    ui->actZoomFitH->trigger();
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*" + item->text(MainWindow::colItem);
    item->setText(MainWindow::colItem, str);
    if (item->childCount() > 0) {
        for (int i = 0; i < item->childCount(); i++) {
            changeItemCaption(item->child(i));
        }
    }
}

void MainWindow::deleteItem(QTreeWidgetItem *parrentItem, QTreeWidgetItem *item)
{
    // 如果节点下有子节点,递归调用本函数删除
    if (item->childCount() > 0) {
        int count = item->childCount();
        QTreeWidgetItem *tempParItem = item;
        for (int i = count - 1; i >= 0; i--) {
            deleteItem(tempParItem, tempParItem->child(i));
        }
    }
    // 父节点移除子节点
    parrentItem->removeChild(item);
    // 删除节点指针
    delete item;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    emit windowResized(size);
}

void MainWindow::on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);

    if (current == nullptr)
        return;
    if (current == previous)
        return;

    int type = current->type();

    switch (type) {
    case MainWindow::itTopItem:
        ui->actAddFolder->setEnabled(true);
        ui->actAddFiles->setEnabled(true);
        ui->actDelItem->setEnabled(false); // 不允许删除顶节点

        break;
    case MainWindow::itGroupItem:
        ui->actAddFolder->setEnabled(true);
        ui->actAddFiles->setEnabled(true);
        ui->actDelItem->setEnabled(true);
        break;
    case MainWindow::itImageItem:
        ui->actAddFolder->setEnabled(false); // 图片节点不允许添加子节点
        ui->actAddFiles->setEnabled(true);
        ui->actDelItem->setEnabled(true);
        displayImage(current);
        break;
    default:
        break;
    }
}

void MainWindow::on_actDockFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}

void MainWindow::on_actDockVisible_triggered(bool checked)
{
    ui->dockWidget->setVisible(checked);
}
