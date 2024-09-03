##  可视化数据技术

- QChart类（用来管理数据）
- QChartView类（用来显示图表类）



项目准备：

- 在.pro工程文件中的`QT       += core gui`下一行加上`QT += charts`
- 在.h文件中加上头文件`#include <QtCharts>`和`#include <QtCharts/QChartView>`
- 在MainDialog类中添加成员指针变量

![1725281533123](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1725281533123.png)



**出现的问题**

为什么不能将pChart放在maindialog.h中的的成员变量中声明？

解答：将 `pChart` 作为 `MainDialog` 类中的成员变量可能会导致问题，主要是因为 `pChart` 是在 `MainDialog` 构造函数中动态创建的。如果你将 `pChart` 作为成员变量，需要确保在类的析构函数中正确释放它，以避免内存泄漏。此外，确保在图表被销毁之前它的所有引用都有效也是个挑战。如果处理不当，可能会引发程序崩溃或不稳定的行为。使用动态创建的对象需要额外的内存管理和生命周期管理工作。 

![1725326146229](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1725326146229.png)

这里和视频做的稍微不一样的点就是把销售数量的标签给遮掉了，如果显示在柱状图上显得很丑