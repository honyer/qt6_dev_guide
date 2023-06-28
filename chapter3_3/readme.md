## Chapter3_3 QT的元对象系统

- 该示例使用cmake构建
- GUI界面使用代码实现
- QT6的信号与槽connect
在Qt 6中，`SIGNAL()`和`SLOT()`宏已经被弃用，而使用新的连接语法来连接信号与槽；

`connect(sbxBoyAge, SIGNAL(valueChanged()), this, SLOT(do_sbxChanged()));`
应该改写为:
`connect(sbxBoyAge, &QSpinBox::valueChanged, this, &YourClassName::do_sbxChanged);`
如果do_sbxChanged需要传参类型
`connect(sbxBoyAge, qOverload<int>(&QSpinBox::valueChanged), this, &YourClassName::do_sbxChanged);`


#### 元对象
自定义的元对象要继承自QObject，使用`Q_CLASSINFO`宏来定义类信息，`Q_PROPERTY`宏来定义属性

```c++
    Q_OBJECT
    Q_CLASSINFO("author", "wang") // 定义类的附加信息
    Q_CLASSINFO("company", "GNU")
    Q_CLASSINFO("version", "1.0.0.0")
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged) // 定义属性age
    Q_PROPERTY(QString name MEMBER m_name)                      // 定义属性name
    Q_PROPERTY(int score MEMBER m_score)                        // 定义属性score
```



#### bool QObject::setProperty(const char *name, const QVariant &value)

如果property是Q_PROPERTY定义的，那返回的就是true否则就是false；没有用Q_PROPERTY定义的在初始化时设置的称为动态属性；但是不能从property(int index)中读取到动态属性，只能通过property('name')来获取到值；循环遍历CLASSINFO和PROPERTY，只能获取到对象预设的类和属性。



#### QObject *QObject::sender()

sender()是信号发送者，返回的是一个QObject指针，通过qobject_cast将其转为实际的发送对象，就能读取响应的属性。

```c++
// 将信号发送者对象转为sbx，判断其属性
    QSpinBox *sbx = qobject_cast<QSpinBox *>(sender());
```

![运行示例](https://github.com/honyer/qt6_dev_guide/blob/main/chapter3_3/chapter3_3_preview.png)
