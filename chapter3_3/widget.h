#pragma once

#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>
#include "tperson.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void do_pbnClicked_pbnBoyAge();   // QPushButton pbnBoyAge clicked
    void do_pbnClicked_pbnGirlAge();  // QPushButton pbnGirlAge clicked
    void do_pbnClicked_pbnMetaInfo(); // QPushButton pbnMetaInfo clicked
    void do_pbnClicked_pbnClear();    // QPushButton pbnClear clicked

    void do_ageChanged(int val); // TPerson age changed
    void do_sbxChanged(int val); // QSpinBox value changed

private:
    TPerson *boy;
    TPerson *girl;

    QSpinBox *sbxBoyAge;
    QSpinBox *sbxGirlAge;
    QPushButton *pbnBoyAge;
    QPushButton *pbnGirlAge;
    QPushButton *pbnMetaInfo;
    QPushButton *pbnClear;

    QPlainTextEdit *pteContent;

    void setupUI();
    void initSlots();
};
