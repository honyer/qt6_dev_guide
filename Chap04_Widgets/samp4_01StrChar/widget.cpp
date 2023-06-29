#include "widget.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("QChar常用功能");
    setupUI();
    initSlots();
}

Widget::~Widget() {}

void Widget::do_pbnClicked()
{
    QPushButton *pbn = qobject_cast<QPushButton *>(sender());
    if (pbn == pbnStrUnicode) {
        qDebug() << "QPushButton Clicked：pbnStrUnicode";
    }
}

void Widget::do_cbxClicked(bool checked)
{
    QCheckBox *cbx = qobject_cast<QCheckBox *>(sender());
    if (cbx == cbxIsDigit) {
        qDebug() << "QCheckBox cbxIsDigit" << checked;
    }
}

void Widget::setupUI()
{
    // 主布局 vlayMain[gbxStrInput,gbxButtonTest,hlayResultCheck]
    QVBoxLayout *vlayMain = new QVBoxLayout(this);
    QGroupBox *gbxStrInput = new QGroupBox(this);
    QGroupBox *gbxButtonTest = new QGroupBox("其他测试和功能", this);
    // 一个widget只能添加一个layout，此处不能再设置父指针
    QHBoxLayout *hlayResultCheck = new QHBoxLayout();
    vlayMain->addWidget(gbxStrInput);
    vlayMain->addWidget(gbxButtonTest);
    vlayMain->addLayout(hlayResultCheck);

    // gbxStrInput[glayStr[2, 3]] QGridLayout2行3列
    QGridLayout *glayStr = new QGridLayout(gbxStrInput);
    QLabel *lblStr = new QLabel("输入字符串", gbxStrInput);
    QLabel *lblChar = new QLabel("输入单个字符", gbxStrInput);
    letInputStr = new QLineEdit("hello,世界", gbxStrInput);
    letInputChar = new QLineEdit("⭐", gbxStrInput);
    pbnStrUnicode = new QPushButton("每个字符的Unicode", gbxStrInput);
    pbnCharPropety = new QPushButton("单个字符特性判断", gbxStrInput);
    glayStr->addWidget(lblStr, 0, 0);
    glayStr->addWidget(letInputStr, 0, 1);
    glayStr->addWidget(pbnStrUnicode, 0, 2);
    glayStr->addWidget(lblChar, 1, 0);
    glayStr->addWidget(letInputChar, 1, 1);
    glayStr->addWidget(pbnCharPropety, 1, 2);

    // gbxButtonTest[glayTest[2,2]] QGridLayout2行3列
    QGridLayout *glayTest = new QGridLayout(gbxButtonTest);
    pbnLatin1 = new QPushButton("与Latin1的转换", gbxButtonTest);
    pbnUtf16 = new QPushButton("与UTF-16的转换", gbxButtonTest);
    pbnQChar = new QPushButton("QCHAR比较和替换", gbxButtonTest);
    pbnClear = new QPushButton("清空文本框", gbxButtonTest);
    glayTest->addWidget(pbnLatin1, 0, 0);
    glayTest->addWidget(pbnUtf16, 0, 1);
    glayTest->addWidget(pbnQChar, 1, 0);
    glayTest->addWidget(pbnClear, 1, 1);

    // hlayResultCheck[gbxResult,gbxCharCheck]
    // gbxResult[vlayContent[pteContent]]
    QGroupBox *gbxResult = new QGroupBox("结果显示", this);
    QVBoxLayout *vlayContent = new QVBoxLayout(gbxResult);
    pteContent = new QPlainTextEdit(gbxResult);
    vlayContent->addWidget(pteContent);
    // gbxCharCheck[vlayCheckBox[cbxIsDigit,...,cbxIsPunct]]
    QGroupBox *gbxCharCheck = new QGroupBox("QChar特性判断", this);
    QVBoxLayout *vlayCheckBox = new QVBoxLayout(gbxCharCheck);
    cbxIsDigit = new QCheckBox("isDigit", gbxCharCheck);
    cbxIsLetter = new QCheckBox("isLetter", gbxCharCheck);
    cbxIsLetterOrNum = new QCheckBox("isLetterOrNumber", gbxCharCheck);
    cbxIsUpper = new QCheckBox("isUpper", gbxCharCheck);
    cbxIsLower = new QCheckBox("isLower", gbxCharCheck);
    cbxIsMark = new QCheckBox("isMark", gbxCharCheck);
    cbxIsSpace = new QCheckBox("isSpace", gbxCharCheck);
    cbxIsSymbol = new QCheckBox("isSymbol", gbxCharCheck);
    cbxIsPunct = new QCheckBox("isPunct", gbxCharCheck);
    vlayCheckBox->addWidget(cbxIsDigit);
    vlayCheckBox->addWidget(cbxIsLetter);
    vlayCheckBox->addWidget(cbxIsLetterOrNum);
    vlayCheckBox->addWidget(cbxIsUpper);
    vlayCheckBox->addWidget(cbxIsLower);
    vlayCheckBox->addWidget(cbxIsMark);
    vlayCheckBox->addWidget(cbxIsSpace);
    vlayCheckBox->addWidget(cbxIsSymbol);
    vlayCheckBox->addWidget(cbxIsPunct);

    hlayResultCheck->addWidget(gbxResult);
    hlayResultCheck->addWidget(gbxCharCheck);
}

void Widget::initSlots()
{
    connect(pbnStrUnicode, &QPushButton::clicked, this, &Widget::do_pbnClicked);
    connect(pbnCharPropety, &QPushButton::clicked, this, &Widget::do_pbnClicked);
    connect(pbnLatin1, &QPushButton::clicked, this, &Widget::do_pbnClicked);
    connect(pbnUtf16, &QPushButton::clicked, this, &Widget::do_pbnClicked);
    connect(pbnQChar, &QPushButton::clicked, this, &Widget::do_pbnClicked);
    connect(pbnClear, &QPushButton::clicked, this, &Widget::do_pbnClicked);
    connect(cbxIsDigit, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
    connect(cbxIsLetter, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
    connect(cbxIsLetterOrNum, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
    connect(cbxIsUpper, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
    connect(cbxIsLower, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
    connect(cbxIsMark, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
    connect(cbxIsSpace, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
    connect(cbxIsSymbol, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
    connect(cbxIsPunct, &QCheckBox::clicked, this, &Widget::do_cbxClicked);
}
