#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settingUi();
    initSlots();

    ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_fontFize_Changed(int size)
{
    // 获取当前选择的文本格式并设置字体大小
    QTextCharFormat fmtCurrent = ui->plainTextEdit->currentCharFormat();
    fmtCurrent.setFontPointSize(size);
    ui->plainTextEdit->mergeCurrentCharFormat(fmtCurrent);

    // 状态栏progressBar显示字体
    pbrFontSize->setValue(size);
}

void MainWindow::do_fontSelected(const QFont &font)
{
    lblInfo->setText(QString("字体名称：") + font.family());

    // 获取当前选择的文本格式并设置字体大小
    QTextCharFormat fmtCurrent = ui->plainTextEdit->currentCharFormat();
    fmtCurrent.setFont(font);
    ui->plainTextEdit->mergeCurrentCharFormat(fmtCurrent);
}

void MainWindow::do_font_checked(bool checked)
{
    QObject *obj = QObject::sender();
    QTextCharFormat fmt = ui->plainTextEdit->currentCharFormat();
    if (obj == ui->actFont_Bold) {
        if (checked)
            fmt.setFontWeight(QFont::Bold);
        else
            fmt.setFontWeight(QFont::Normal);
    } else if (obj == ui->actFont_Italic) {
        fmt.setFontItalic(checked);
    } else if (obj == ui->actFont_Underline) {
        fmt.setFontUnderline(checked);
    }
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::do_file_operation_triggled()
{
    QObject *obj = QObject::sender();
    if (obj == ui->actFile_New) {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->document()->setModified(false);
        lblFile->setText("新建了一个文件");
    } else if (obj == ui->actFile_Open) {
        lblFile->setText("打开了一个文件");
    } else if (obj == ui->actFile_Save) {
        ui->plainTextEdit->document()->setModified(false);
        lblFile->setText("文件已保存");
    }
}

void MainWindow::settingUi()
{
    this->setWindowTitle("QAction,QMainWindow,QPlainTextEdit");
    // 设置语言切换QActionGroup互斥
    agpCnEn = new QActionGroup(this);
    agpCnEn->addAction(ui->actLang_CN);
    agpCnEn->addAction(ui->actLang_EN);
    agpCnEn->setExclusive(true);
    ui->actLang_CN->setChecked(true);

    // 字体大小设置
    sbxFontSize = new QSpinBox(this);
    sbxFontSize->setValue(ui->plainTextEdit->font().pointSize());
    sbxFontSize->setMinimum(5);
    sbxFontSize->setMaximum(50);
    sbxFontSize->setPrefix("字体 ");
    ui->toolBar->addWidget(sbxFontSize);

    // 字体下拉设置
    fcbFontName = new QFontComboBox(this);
    fcbFontName->setFont(ui->plainTextEdit->font());
    fcbFontName->setMinimumWidth(150);
    ui->toolBar->addWidget(fcbFontName);

    // 添加分割线和关闭按钮
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actClose);

    // 创建状态栏组件
    lblFile = new QLabel("文件名：", this);
    lblFile->setMinimumWidth(150);
    lblInfo = new QLabel("字体名称：", this);
    pbrFontSize = new QProgressBar(this);
    pbrFontSize->setMaximumWidth(200);
    pbrFontSize->setMinimum(5);
    pbrFontSize->setMaximum(50);
    pbrFontSize->setValue(ui->plainTextEdit->font().pointSize());
    ui->statusbar->addWidget(lblFile);
    ui->statusbar->addWidget(pbrFontSize);
    ui->statusbar->addPermanentWidget(lblInfo);
}

void MainWindow::initSlots()
{
    connect(sbxFontSize, &QSpinBox::valueChanged, this, &MainWindow::do_fontFize_Changed);
    connect(fcbFontName, &QFontComboBox::currentFontChanged, this, &MainWindow::do_fontSelected);

    // 粗体、斜体、下划线信号槽绑定
    connect(ui->actFont_Bold, &QAction::triggered, this, &MainWindow::do_font_checked);
    connect(ui->actFont_Italic, &QAction::triggered, this, &MainWindow::do_font_checked);
    connect(ui->actFont_Underline, &QAction::triggered, this, &MainWindow::do_font_checked);

    // 文件新建、打开、保存信号槽
    connect(ui->actFile_New, &QAction::triggered, this, &MainWindow::do_file_operation_triggled);
    connect(ui->actFile_Open, &QAction::triggered, this, &MainWindow::do_file_operation_triggled);
    connect(ui->actFile_Save, &QAction::triggered, this, &MainWindow::do_file_operation_triggled);
}

void MainWindow::on_plainTextEdit_copyAvailable(bool b)
{
    // 编辑框是否能copy，更新剪切、复制、粘贴的按钮可用状态
    ui->actEdit_Copy->setEnabled(b);
    ui->actEdit_Cut->setEnabled(b);
    ui->actEdit_Paste->setEnabled(ui->plainTextEdit->canPaste());
}

void MainWindow::on_plainTextEdit_selectionChanged()
{
    // 编辑框内容选择变化，更新粗体、斜体、下划线的可用状态
    QTextCharFormat fmt = ui->plainTextEdit->currentCharFormat();
    ui->actFont_Bold->setChecked(fmt.font().bold());
    ui->actFont_Italic->setChecked(fmt.font().italic());
    ui->actFont_Underline->setChecked(fmt.font().underline());
    ui->actEdit_Cut->setChecked(true);
}

void MainWindow::on_actSys_ToggleText_triggered(bool checked)
{
    if (checked) {
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    } else {
        ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    }
}
