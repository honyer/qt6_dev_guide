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
        pbn_clicked_StrUnicode();
    } else if (pbn == pbnClear) {
        pbn_clicked_Clear();
    } else if (pbn == pbnCharPropety) {
        pbn_clicked_CharPropety();
    } else if (pbn == pbnLatin1) {
        pbn_clicked_Latin1();
    } else if (pbn == pbnQChar) {
        pbn_clicked_QChar();
    } else if (pbn == pbnUtf16) {
        pbn_clicked_Utf16();
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
}

void Widget::pbn_clicked_StrUnicode()
{
    QString strContent = "";
    pteContent->clear();

    QString str = letInputStr->text();
    if (str.isEmpty()) {
        return;
    }

    for (qint16 i = 0; i < str.size(); i++) {
        QChar ch = str.at(i);
        // `char16_t` 是 C++11 引入的一种整数类型，用于表示 16 位的 Unicode 字符。
        // 它与 `ushort` 类型具有相同的大小（两者都是 16 位），
        // 因此可以直接将 `unicode()` 返回的值赋给 `char16_t` 类型的变量。
        char16_t uniCode = ch.unicode();
        strContent.append(QString(ch));
        // `%X`用于将整数值`uniCode`转换为十六进制表示
        strContent.append(QString::asprintf("\t,Unicode编码= 0x%X\n", uniCode));
    }

    pteContent->appendPlainText(strContent);
}

void Widget::pbn_clicked_CharPropety()
{
    QString str = letInputChar->text();
    if (str.isEmpty()) {
        return;
    }
    QChar ch = str.at(0);
    char16_t uniCode = ch.unicode();
    QString strContent = QString(ch);
    strContent.append(QString::asprintf("\t,Unicode编码= 0x%X\n", uniCode));

    // 判断该字符的特性填充到checkbox
    pteContent->appendPlainText(strContent);
    cbxIsDigit->setChecked(ch.isDigit());
    cbxIsLetter->setChecked(ch.isLetter());
    cbxIsLetterOrNum->setChecked(ch.isLetterOrNumber());
    cbxIsUpper->setChecked(ch.isUpper());
    cbxIsLower->setChecked(ch.isLower());
    cbxIsMark->setChecked(ch.isMark());
    cbxIsSpace->setChecked(ch.isSpace());
    cbxIsSymbol->setChecked(ch.isSymbol());
    cbxIsPunct->setChecked(ch.isPunct());
}

void Widget::pbn_clicked_Latin1()
{
    QString str = "Dimple";
    QString strContent = "原文：\"" + str + "\"\n";
    pteContent->clear();

    QChar chP = QChar::fromLatin1('P');
    str[0] = chP;
    strContent.append("\nQChar chP = QChar::fromLatin1('P');\nstr[0] = chP;\n\n");
    strContent.append("现文：" + str + "\"\n");

    pteContent->appendPlainText(strContent);
}

void Widget::pbn_clicked_Utf16()
{
    QString str = "Hello,北京";
    pteContent->clear();
    QString strContent = "原文：\"" + str + "\"\n";
    str[6] = QChar(0x9752);
    str[7] = QChar::fromUcs2(0x5C9B);
    strContent.append("\n");
    strContent.append("str[6] = QChar(0x9752);\n");
    strContent.append("str[7] = QChar::fromUcs2(0x5C9B);\n");
    strContent.append("\n");
    strContent.append("现文：\"" + str + "\"\n");

    pteContent->appendPlainText(strContent);
}

void Widget::pbn_clicked_QChar()
{
    QString strTarget = "河to湖";
    QString str = "他们来自于河南或河北";
    pteContent->clear();
    QString strContent = "目标：" + strTarget + "\n原文：\"" + str + "\"\n";
    QChar he = QChar::fromUcs2(strTarget[0].unicode());
    qDebug() << he;
    QChar hu = QChar(strTarget[3].unicode());
    qDebug() << hu;
    for (int i = 0; i < str.size(); i++) {
        if (str.at(i) == he)
            str[i] = hu;
    }
    strContent.append("\n");
    strContent.append("QChar he = QChar::fromUcs2(strTarget[0].unicode());\n");
    strContent.append("QChar hu = QChar(strTarget[3].unicode());\n");
    strContent.append("for (int i = 0; i < str.size(); i++) {\n");
    strContent.append("    if (str.at(i) == he)\n");
    strContent.append("        str[i] = hu;\n");
    strContent.append("}\n\n");
    strContent.append("现文：\"" + str + "\"\n");

    pteContent->appendPlainText(strContent);
}

void Widget::pbn_clicked_Clear()
{
    pteContent->clear();
}
