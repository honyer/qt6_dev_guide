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
    void do_cbxClicked(bool checked);

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
};
