#pragma once

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pbnClear_clicked();

    void on_pbnFrontBack_clicked();

    void on_pbnLeftRight_clicked();

    void on_pbnFirstLast_clicked();

    void on_pbnSection_clicked();

    void on_pbnIsNullEmpty_clicked();

    void on_pbnResize_clicked();

    void on_pbnSizeLength_clicked();

    void on_pbnFill_clicked();

    void on_pbnIndexLastOf_clicked();

    void on_pbnContains_clicked();

    void on_pbnEndStartWith_clicked();

    void on_pbnCount_clicked();

    void on_pbnTrimSimplfy_clicked();

    void on_pbnInsert_clicked();

    void on_pbnRemove_clicked();

    void on_pbnReplace_clicked();

private:
    Ui::Widget *ui;
};

