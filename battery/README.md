###  电池控件

**层次分析**

首先说frmbattery.cpp，这个是基于QWidget的一个继承类，也就是最开始创建项目的时候起的名字，然后创建完工程之后batter.cpp是之后创建的，在frmbattery的ui中放着两个对象：横向拖拉条(horizontalSlider)和电池图像

####  反锯齿函数

```cpp
QPainter painter(this);
painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
```

在这个电池控件中，由于这个图像是弯曲的，所以要用到反锯齿函数来美化图形，调用了反锯齿函数之后那些有弧线的地方会变得圆滑



####  固定矩形位置

```cpp
QPointF batteryRect;	//先声明对象
int borderWidth = 5;
QPointF topLeft(borderWidth, borderWidth);  //确定左上角
QPointF bottomRight(batteryWidth, height() - borderWidth);  //确定右上角
batteryRect = QRectF(topLeft, bottomRight);
```

这是一段关于`QPointF`api的使用方法，这一段的作用是将矩形固定在一个位置





####  渐变色调用方法

```cpp
QLinearGradient batteryGradient(QPointF(0, 0), QPointF(0, height()));   //纵向的渐变色
if (currentValue <= alarmValue) {
    batteryGradient.setColorAt(0.0, alarmColorStart);   //第一个参数是position，范围是[0,1]
    batteryGradient.setColorAt(1.0, alarmColorEnd);
} else {
    batteryGradient.setColorAt(0.0, normalColorStart);
    batteryGradient.setColorAt(1.0, normalColorEnd);
}
painter->setBrush(batteryGradient); //用渐变色填充
```

对于这个电池组件，他会有一个电量低的警戒状态（也就是红色），所以才会有中间的if和else部分，要是仅仅只有一类颜色的渐变的话就只需要其中的两行即可，第一个参数是`double`类型，第二个参数是`QColor`类型





####  QPainter的基本使用步骤

```cpp
painter->save();

//固定位置
QPointF headRectTopLeft(batteryRect.topRight().x(), height() / 3);
QPointF headRectBottomRight(width(), height() - height() / 3);
QRectF headRect(headRectTopLeft, headRectBottomRight);

//设置渐变色 可有可无
QLinearGradient headRectGradient(headRect.topLeft(), headRect.bottomLeft());
headRectGradient.setColorAt(0.0, borderColorStart);
headRectGradient.setColorAt(1.0, borderColorEnd);

painter->setPen(Qt::NoPen);	//笔用来画边界
painter->setBrush(headRectGradient);	//刷子用来填充颜色
painter->drawRoundedRect(headRect, headRadius, headRadius);

painter->restore();
```





####  复现过程中遇到的问题

**构造函数前加explicit关键字**

```cpp
explicit frmBattery(QWidget *parent = nullptr);
```

在初始qt构建项目的时候是不会有explicit关键字的，explicit关键字的作用就是防止隐式转换，只有明确的构造函数才能调用



**painter相关**

```cpp
//setpen()里面参数是QPen类型的，QPen类型中需要两个参数，分别是QColor和画笔粗细
painter->setPen(QPen(borderColorStart, borderWidth));

//画刷 填充颜色
painter->setBrush(Qt::NoBrush);

//用来定形 绘制带圆角的函数 参数1：QRectF类型用来确定位置，后两个参数分别是x和y的圆角幅度
painter->drawRoundedRect(batteryRect, borderRadius, borderRadius);
```



**自定义控件封装**

这个很重要很重要！！！也是找了好久猜搞明白这个操作怎么弄的。就拿这个battery类为例，当我写完画边框的函数之后，想要跑一下看看能不能有个画边框的样子，结果什么都没有显示！？拿自己代码和它对比了一下发现自己的.ui文件中没有battery类？？？这玩意咋出来的呢？

首先这个battery是一个QWidget类，然后打开.ui文件，在Containers中选中Widget拖出来，然后右键这个框框选中提升为，这时候会弹出一个对话框，然后将你的自定义控件的类名复制过来添加即可，最保险的操作就是将类名直接复制过来，可能有时候因为大小写不同而出错！
![1727269504178](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1727269504178.png)



**Q_EMIT+函数**

代表Qt信号发射函数，以`Q_EMIT valuechanged(value);`为例，当value发生变化 连接到`valuechanged(value)`信号的槽函数都会被调用，前提是这个`valuechanged(value)`是一个槽函数哦！



**画完了电池电量为什么不显示？**

破案了，原来是frmbattery.cpp中的initForm函数没写。。。



**如何通过滑动轴控件来实现电池电量变化的？**

这个要看到frmbattery.cpp中的initForm函数，复现的时候就是没有写这个函数导致没有出现电量。。。也就是这一步实现了轴移动电量也跟着移动的效果



**小结 **

大佬写出来的代码就是不一样，其实看到现在感觉是懂了绝大部分了，主要是想独立复现出来还是有点困难，还是难在电量的显示上。第一遍看源码的时候还是没有理解透，现在再看一遍这个代码又懂了很多东西。首先需要弄懂的是他在Q_OBJECT中写的一大堆宏定义，这其实是Qt的一种特色吧，`可以通过 Qt 的元对象系统（如信号与槽机制）方便地访问和修改这些属性`。通过这一个小demo其实学到的东西还挺多！首先是代码的规范吧，有一说一确实舒服，虽然从这里调用到那里，函数名一样但参数不一样，但是我认为这样写反而十分严谨，映像比较清楚的是这里面的几个value，他为了从int统一到double写了很多对同名函数