## Chapter2_3 使用代码的方式布局UI界面

- 该项目使用cmake构建

- cmake添加程序图标
在Windows环境下，将图标文件放到根目录，并新建appIcon.rc;在该资源文件中添加
`IDI_ICON1 ICON DISCARDABLE "appicon.ico"`
并在CMakeLists.txt `set(PROJECT_SOURCES )`中添加该文件

- radioButton 在同一个容器中只能选择一个
并且选择之后至少有一个被选择，不能取消，在clear函数准备清空所有的radioButton选择，实践最后一个选项无法清空。

- 文本编辑框
不能用Text Edit，案例需要使用Plain Text Edit，因为Text Edit是html格式渲染，使用该组件导致字体颜色无法被渲染。

### 与Chapter2_2的区别
- 对界面布局要有层次感
- Widget与Widget之间应该要有一个Layout布局来圈套
比如QGroupBox放三个复选框按钮，它们都是继承自QWidget，如果直接把QCheckBox放到QGroupBox中，将会堆叠到一起无法正常显示，解决方法是将三个QCheckBox放到一个水平布局QHBoxLayout中，再将这个layout放到QGroupBox上，`QGroupBox[QHBoxLayout[cbxUnderLine,cbxItalic,cbxBold]]`
- 自定义槽函数来绑定各种事件



![运行示例](https://github.com/honyer/qt6_dev_guide/blob/main/Chap02_Basics/samp2_3CodeUI/chapter2_3_preview.png)
