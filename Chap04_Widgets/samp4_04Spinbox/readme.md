## samp4_04Spinbox

- 该示例使用cmake构建
- 常用属性

| 属性名称 | 功能 |
| -------- | ---- |
| prefix         |  数字显示的前缀，例如“$”    |
| suffix         |  数字显示的后缀，例如“kg”    |
| buttonSymbols         |  编辑框右侧调节按钮的符号，可以设置不显示调节按钮    |
| text         |  只读属性，SpinBox 里显示的全部文字，包括前缀和后缀    |
| cleanText         |  只读属性，不带前缀和后缀且去除了前后空格的文字    |
| minimum         |  数值范围的最小值    |
| maximum         |  数值范围的最大值    |
| singleStep         |  点击编辑框右侧上下调节按钮时的单步改变值，例如 1 或 0.1    |
| stepType         |  步长类型，单一步长或自适应步长    |
| value         |  当前显示的值    |
| **displayIntegerBase**     |  QSpinBox 特有属性，显示整数使用的进制，例如 10 表示十进制    |
| decimals         |  QDoubleSpinBox 特有属性，显示数值的小数位数，例如 2 表示显示两位小数    |
- 常用接口函数
| 接口函数 | 功能 |
| -------- | ---- |
|  int QSpinBox::value()        |  读取数值    |
|  void QSpinBox::setValue(int val)        |  设置数值    |
|  void QSpinBox::setRange(int minimum, int maximum)   | 设置数值范围     |
- 常用信号
| 属性名称                                        | 功能                                                         |
| ----------------------------------------------- | ------------------------------------------------------------ |
| void QSpinBox::valueChanged(int i)              | 数值变化                                                     |
| void QSpinBox::textChanged(const QString &text) | 数值变化导致文字变化，prefix 或suffix 属性变化导致文字变化。 |



####
- 布局
控件布局sizePolicy策略有最大最小以及最小扩展，可以根据布局需要调整设置
![运行示例](https://github.com/honyer/qt6_dev_guide/blob/main/Chap04_Widgets/samp4_04Spinbox/samp4_04_preview.png)
