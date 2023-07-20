#pragma once

#include <QDate>
#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString str;
private slots:
    void on_pbnSetHeader_clicked();

    void on_pbnSetRows_clicked();

    void on_pbnInitData_clicked();

    void on_pbnInsertRow_clicked();

    void on_pbnDelCurRow_clicked();

    void on_pbnAutoHeight_clicked();

    void on_pbnAutoWidth_clicked();

    void on_pbnLoadTableToText_clicked();

    void on_tblContent_currentCellChanged(int currentRow,
                                          int currentColumn,
                                          int previousRow,
                                          int previousColumn);

    void on_pbnApendRow_clicked();

    void on_cbxTableEditable_clicked(bool checked);

    void on_cbxHeaderH_clicked(bool checked);

    void on_cbxRowColor_clicked(bool checked);

    void on_cbxHeaderV_clicked(bool checked);

    void on_rbxSelectRow_clicked();

    void on_rbnSelectColumn_clicked();

private:
    Ui::MainWindow *ui;
    enum CellType { ctName = 1000, ctSex, ctBirth, ctNation, ctScore, ctPartyM };
    enum FieldColNum { colName = 0, colSex, colBirth, colNation, colScore, colPartyM };

    QLabel *lblCellIndex; // 状态栏显示单元格的行号和列号
    QLabel *lblCellType;  // 状态栏显示单元格的Type
    QLabel *lblStuId;     // 状态栏显示单元格学生的数据信息

    void settingUi();
    void createItemsARow(
        int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score);
};
