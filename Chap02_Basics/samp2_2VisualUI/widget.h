#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_cbxUnderLine_clicked(bool checked);

    void on_cbxItalic_clicked(bool checked);

    void on_cbxBold_clicked(bool checked);

    void do_setFontColor();

    void on_btnClear_clicked();

    void on_btnOk_clicked();

    void on_btnQuit_clicked();

private:
    Ui::Widget *ui;
    QFont font;
};
