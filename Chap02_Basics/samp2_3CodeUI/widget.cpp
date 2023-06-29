#include "widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
//#include <QSpacerItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    beautifyUI();
    initSignalSlots();
    this->setWindowTitle("纯代码实现UI界面");
}

Widget::~Widget()
{
}

void Widget::do_cbxUnderLine(bool checked)
{
    font = cbxUnderLine->font();
    font.setUnderline(checked);
    ptextEdit->setFont(font);
}

void Widget::do_cbxItalic(bool checked)
{
    font = cbxItalic->font();
    font.setItalic(checked);
    ptextEdit->setFont(font);
}

void Widget::do_cbxBold(bool checked)
{
    font = cbxBold->font();
    font.setBold(checked);
    ptextEdit->setFont(font);
}

void Widget::do_setFontColor()
{
    // 复选框设置字体
    QFont font = ptextEdit->font();
    font.setBold(cbxBold->isChecked());
    font.setUnderline(cbxUnderLine->isChecked());
    font.setItalic(cbxItalic->isChecked());

    // 单选框设置颜色
    QPalette pal = ptextEdit->palette();
    if (rbtnRed->isChecked()) {
        pal.setColor(QPalette::Text, Qt::red);
    } else if (rbtnBlue->isChecked()) {
        pal.setColor(QPalette::Text, Qt::blue);
    } else if (rbtnBlack->isChecked()) {
        pal.setColor(QPalette::Text, Qt::black);
    } else {
        pal.setColor(QPalette::Text, Qt::black);
    }

    // 更新到PlainTextEdit
    ptextEdit->setFont(font);
    ptextEdit->setPalette(pal);
}

void Widget::do_clearButtonClicked()
{
    QFont font;
    QPalette pal;
    // 清空字体复选框
    cbxBold->setChecked(false);
    cbxItalic->setChecked(false);
    cbxUnderLine->setChecked(false);

    // 颜色设置默认黑色
    rbtnBlack->setChecked(true);
    rbtnBlue->setChecked(false);
    rbtnRed->setChecked(false);

    // 文本框内容清空
    ptextEdit->setFont(font);
    ptextEdit->setPalette(pal);
    ptextEdit->clear();
}

void Widget::do_quitButtonClicked()
{
    this->close();
}

void Widget::setupUI()
{
    // 定义主布局,垂直布局QVBoxLayout[gbxFont,gbxColor,ptextEdit,hblayButton]
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 三个字体复选框 gbxFont[hlayFont[cbxUnderLine,cbxItalic,cbxBold]]
    QGroupBox *gbxFont = new QGroupBox("字体", this);
    QHBoxLayout *hlayFont = new QHBoxLayout(gbxFont);
    cbxUnderLine = new QCheckBox("UnderLine", gbxFont);
    cbxItalic = new QCheckBox("Italic", gbxFont);
    cbxBold = new QCheckBox("Bold", gbxFont);
    hlayFont->addWidget(cbxUnderLine);
    hlayFont->addWidget(cbxItalic);
    hlayFont->addWidget(cbxBold);
    mainLayout->addWidget(gbxFont);

    // 三个颜色单选框 gbxColor[hblayColor[cbxUnderLine,cbxItalic,cbxBold]]
    QGroupBox *gbxColor = new QGroupBox("颜色", this);
    QHBoxLayout *hblayColor = new QHBoxLayout(gbxColor);
    rbtnBlack = new QRadioButton("Black", gbxColor);
    rbtnRed = new QRadioButton("Red", gbxColor);
    rbtnBlue = new QRadioButton("Blue", gbxColor);
    hblayColor->addWidget(rbtnBlack);
    hblayColor->addWidget(rbtnRed);
    hblayColor->addWidget(rbtnBlue);
    mainLayout->addWidget(gbxColor);

    // 文本编辑框
    ptextEdit = new QPlainTextEdit(this);
    ptextEdit->insertPlainText("通过纯代码创建的GUI布局");
    mainLayout->addWidget(ptextEdit);

    // 三个按钮水平布局 hblayButton[spItem1,btnClear,spItem2,btnOk,btnQuit]
    QHBoxLayout *hblayButton = new QHBoxLayout();
    QSpacerItem *spItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnClear = new QPushButton("清除", this);
    QSpacerItem *spItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnOk = new QPushButton("确定", this);
    btnQuit = new QPushButton("退出", this);
    hblayButton->addItem(spItem1);
    hblayButton->addWidget(btnClear);
    hblayButton->addItem(spItem2);
    hblayButton->addWidget(btnOk);
    hblayButton->addWidget(btnQuit);
    mainLayout->addLayout(hblayButton);

    // 以下这一句可以注释不用，因为在初始化的时候就绑定了Parrent Widget
    //    this->setLayout(mainLayout);
}

void Widget::beautifyUI()
{
    btnClear->setIcon(QIcon(":/images/212.bmp"));
    btnOk->setIcon(QIcon(":/images/322.bmp"));
    btnQuit->setIcon(QIcon(":/images/324.bmp"));
}

void Widget::initSignalSlots()
{
    connect(cbxUnderLine, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(cbxItalic, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(cbxBold, SIGNAL(clicked()), this, SLOT(do_setFontColor()));

    connect(rbtnBlack, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(rbtnRed, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(rbtnBlue, SIGNAL(clicked()), this, SLOT(do_setFontColor()));

    connect(btnClear, SIGNAL(clicked()), this, SLOT(do_clearButtonClicked()));
    //    connect(btnOk, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(btnQuit, SIGNAL(clicked()), this, SLOT(do_quitButtonClicked()));
}
