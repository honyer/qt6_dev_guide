# QT6 C++开发指南

该项目使用cmake构建
根据案例界面自行编写，有以下几个要点：

- cmake添加程序图标
在Windows环境下，将图标文件放到根目录，并新建appIcon.rc;在该资源文件中添加
`IDI_ICON1 ICON DISCARDABLE "appicon.ico"`
并在CMakeLists.txt `set(PROJECT_SOURCES )`中添加该文件

- radioButton 在同一个容器中只能选择一个
并且选择之后至少有一个被选择，不能取消，在clear函数准备清空所有的radioButton选择，实践最后一个选项无法清空。

- 文本编辑框
不能用Text Edit，案例需要使用Plain Text Edit，因为Text Edit是html格式渲染，使用该组件导致字体颜色无法被渲染。

### 信号与槽
可以自定义槽函数，通过connect函数将其它组件的信号与自定义的槽函数绑定起来，就能响应对应的处理机制了。自定义函数要声名在 private slots:下面

```c++
// 三个radioButton点击事件绑定到do_setFontColor()
    connect(ui->rbtnBlack, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(ui->rbtnRed, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
    connect(ui->rbtnBlue, SIGNAL(clicked()), this, SLOT(do_setFontColor()));
```

