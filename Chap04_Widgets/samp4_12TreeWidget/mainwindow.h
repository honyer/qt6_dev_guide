#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QResizeEvent>
#include <QSpinBox>
#include <QTreeWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void windowResized(const QSize &size); // 窗口大小变化了的信号

private slots:
    void do_actFiles_triggered();    // 与文件操作相关的信号槽函数
    void do_treeNodeAct_triggered(); // 删除节点,遍历节点action信号槽函数
    void do_actZoom_triggered();     // 图片操作相关

    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actDockFloat_triggered(bool checked);

    void on_actDockVisible_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    enum TreeItemType { itTopItem = 1001, itGroupItem, itImageItem };
    enum TreeColNum { colItem = 0, colItemType, colDate };
    QLabel *lblFileName;
    QLabel *lblNodeText;
    QSpinBox *sbxRatio; // 状态栏显示图片的缩放比例
    QPixmap m_pixmap;   // 当前的图片
    float m_ratio;      // 当前图片的缩放比例

    void settingUI(); // 初始化一些不在Designer设计的控件，以及一些其他ui设置
    void buildTreeHeader(); // 构建目录树表头
    void initTree();        // 初始化目录树
    void initSlots();       // 绑定信号槽
    void addFolderItem(QTreeWidgetItem *parentItem, QString dir);     // 添加目录节点
    void addImageItem(QTreeWidgetItem *parentItem, QString fileName); // 添加图片节点
    void displayImage(QTreeWidgetItem *item);                         // 显示图片
    void changeItemCaption(QTreeWidgetItem *item);                    // 改变tree项
    void deleteItem(QTreeWidgetItem *parrentItem, QTreeWidgetItem *item); // 删除树的项

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event); // 重写窗口大小变化事件,发射信号
};
