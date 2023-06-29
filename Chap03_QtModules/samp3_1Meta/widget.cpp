#include "widget.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMetaProperty>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("元对象系统特性");
    setupUI();

    // 初始化boy
    boy = new TPerson("王小明", this);
    boy->setProperty("score", 75);
    boy->setProperty("age", 10);
    boy->setProperty("gender", "boy"); // 动态属性gender，TPerson并没有定义这个属性

    // 初始化girl
    girl = new TPerson("刘晓莉", this);
    girl->setProperty("score", 88);
    girl->setProperty("age", 10);
    girl->setProperty("gender", "girl");

    sbxBoyAge->setProperty("isBoy", true);
    sbxGirlAge->setProperty("isGirl", true);

    initSlots();
}

Widget::~Widget()
{
}

void Widget::do_pbnClicked_pbnBoyAge()
{
    boy->incAge();
}

void Widget::do_pbnClicked_pbnGirlAge()
{
    girl->incAge();
}

void Widget::do_pbnClicked_pbnMetaInfo()
{
    QObject *obj = boy;
    const QMetaObject *meta = obj->metaObject();

    pteContent->clear();
    QString str = QString("类名称：%1\n").arg(meta->className());
    str.append("property\n");
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++) {
        const char *propName = meta->property(i).name(); // 需引入头文件QMetaProperty
        QString propValue = obj->property(propName).toString();
        str.append(QString("属性名称=%1，属性值=%2\n").arg(propName).arg(propValue));
    }

    str.append("classInfo\n");
    for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); ++i) {
        QMetaClassInfo mci = meta->classInfo(i);
        str.append(QString("Name=%1;Value=%2\n").arg(mci.name()).arg(mci.value()));
    }

    pteContent->insertPlainText(str);
}

void Widget::do_pbnClicked_pbnClear()
{
    pteContent->clear();
}

void Widget::do_ageChanged(int val)
{
    Q_UNUSED(val);
    TPerson *person = qobject_cast<TPerson *>(sender());
    QString hisName = person->property("name").toString();
    QString hisGender = person->property("gender").toString();
    int hisAge = person->age();
    QString str = QString("%1,%2,年龄=%3").arg(hisName).arg(hisGender).arg(hisAge);
    pteContent->appendPlainText(str); //与insertPlainText的区别，append是换行追加，insert是末尾追加
}

void Widget::do_sbxChanged(int val)
{
    // 将信号发送者对象转为sbx，判断其属性
    QSpinBox *sbx = qobject_cast<QSpinBox *>(sender());
    if (sbx->property("isBoy").toBool()) {
        boy->setAge(val);
    } else {
        girl->setAge(val);
    }
}

void Widget::setupUI()
{
    // this[mainLayout[gbxOperate,pteContent]]
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 操作框 gbxOperate[vlayGBox[hlayBoy, hlayGirl]]
    QGroupBox *gbxOperate = new QGroupBox(this);
    QVBoxLayout *vlayGBox = new QVBoxLayout(gbxOperate);
    // 男生年龄水平布局 hlayBoy[lable1,sbxBoyAge,pbnBoyAge,pbnMetaInfo]
    QHBoxLayout *hlayBoy = new QHBoxLayout();
    QLabel *lable1 = new QLabel("设置男生年龄", gbxOperate);
    sbxBoyAge = new QSpinBox(gbxOperate);
    pbnBoyAge = new QPushButton("boy长大一岁", gbxOperate);
    pbnMetaInfo = new QPushButton("元对象信息", gbxOperate);
    hlayBoy->addWidget(lable1);
    hlayBoy->addWidget(sbxBoyAge);
    hlayBoy->addWidget(pbnBoyAge);
    hlayBoy->addWidget(pbnMetaInfo);
    // 女生年龄水平布局 hlayGirl[lable2,sbxGirlAge,pbnGirlAge,pbnClear]
    QHBoxLayout *hlayGirl = new QHBoxLayout();
    QLabel *lable2 = new QLabel("设置女生年龄", gbxOperate);
    sbxGirlAge = new QSpinBox(gbxOperate);
    pbnGirlAge = new QPushButton("girl长大一岁", gbxOperate);
    pbnClear = new QPushButton("清空文本框", gbxOperate);
    hlayGirl->addWidget(lable2);
    hlayGirl->addWidget(sbxGirlAge);
    hlayGirl->addWidget(pbnGirlAge);
    hlayGirl->addWidget(pbnClear);
    vlayGBox->addLayout(hlayBoy);
    vlayGBox->addLayout(hlayGirl);

    // 文本框
    pteContent = new QPlainTextEdit(this);
    mainLayout->addWidget(gbxOperate);
    mainLayout->addWidget(pteContent);

    // 初始化组件信息
    sbxBoyAge->setValue(10);
    sbxGirlAge->setValue(20);
}

void Widget::initSlots()
{
    // 在Qt 6中，`SIGNAL()`和`SLOT()`宏已经被弃用，而使用新的连接语法来连接信号与槽
    // 弃用 connect(sbxBoyAge, SIGNAL(valueChanged()), this, SLOT(do_sbxChanged()));
    // 启用 connect(sbxBoyAge, &QSpinBox::valueChanged, this, &YourClassName::do_sbxChanged);

    // connect TPerson boy and girl age changed
    connect(boy, &TPerson::ageChanged, this, &Widget::do_ageChanged);
    connect(girl, &TPerson::ageChanged, this, &Widget::do_ageChanged);

    // connect QSpinBox Value change，do_sbxChanged(int val),信号自动传参SpinBox的value作为入参
    connect(sbxBoyAge, &QSpinBox::valueChanged, this, &Widget::do_sbxChanged);
    connect(sbxGirlAge, &QSpinBox::valueChanged, this, &Widget::do_sbxChanged);

    // connect QPushButton clicked
    connect(pbnBoyAge, &QPushButton::clicked, this, &Widget::do_pbnClicked_pbnBoyAge);
    connect(pbnGirlAge, &QPushButton::clicked, this, &Widget::do_pbnClicked_pbnGirlAge);
    connect(pbnMetaInfo, &QPushButton::clicked, this, &Widget::do_pbnClicked_pbnMetaInfo);
    connect(pbnClear, &QPushButton::clicked, this, &Widget::do_pbnClicked_pbnClear);
}
