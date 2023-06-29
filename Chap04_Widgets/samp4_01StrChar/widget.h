#pragma once

#include <QCheckBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void do_pbnClicked();

private:
    QLineEdit *letInputStr;
    QLineEdit *letInputChar;

    QPushButton *pbnStrUnicode;
    QPushButton *pbnCharPropety;
    QPushButton *pbnLatin1;
    QPushButton *pbnUtf16;
    QPushButton *pbnQChar;
    QPushButton *pbnClear;

    QPlainTextEdit *pteContent;

    QCheckBox *cbxIsDigit;
    QCheckBox *cbxIsLetter;
    QCheckBox *cbxIsLetterOrNum;
    QCheckBox *cbxIsUpper;
    QCheckBox *cbxIsLower;
    QCheckBox *cbxIsMark;
    QCheckBox *cbxIsSpace;
    QCheckBox *cbxIsSymbol;
    QCheckBox *cbxIsPunct;

    void setupUI();
    void initSlots();

    void pbn_clicked_StrUnicode();
    void pbn_clicked_CharPropety();
    void pbn_clicked_Latin1();
    void pbn_clicked_Utf16();
    void pbn_clicked_QChar();
    void pbn_clicked_Clear();
};
