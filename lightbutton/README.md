###  高亮按钮---lightButton

####  main.cpp大致模板(4.10版本)

```cpp
#include "frmlightbutton.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(13);
    a.setFont(font);

    QTextCodec* codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    frmLightButton w;
    w.setWindowTitle("lightButtonDemo");
    w.show();
    return a.exec();
}
```



####  求min函数

```cpp
int side = qMin(width, height);
```



####  在控件中央显示文本

```cpp
QFont font;
font.setPixelSize(side - 200);
painter.setFont(font);	//将刚刚创建并设置好的字体应用到绘图对象 (painter) 上
painter.setPen(textColor);	//设置笔刷的颜色 这决定了文本的颜色
//this->rect()是widget内置的表示当前绘图区域 Qt::AlignCenter表示文本居中对齐
painter.drawText(this->rect(), Qt::AlignCenter, text);
```



####  不显示控件的原因

1、可能是frmxxx.cpp中的构造函数中没有调用`this->initForm();`

2、evenFliter没有写。。。这个问题出现在写lightButton项目的时候出现的

通过这两次的demo学习我发现了第二点的根本原因，就是一定要注意类中的signals所绑定的信号函数，当这个被调用之后才会触发这个控件的绘制，例如lightButton中的clicked()和battery中的valueChanged()



####  自定义事件过滤器

第一次遇见，记下来吧~注释都在代码上了，其实也不是很懂。。。

```cpp
//这个函数必须写 不写不显示控件 实现一个可拖动的按钮 watched 是被监视的对象，event 是接收到的事件
bool LightButton::eventFilter(QObject *watched, QEvent *event) {
    int type = event->type();   //获取事件的类型，并将其存储在 type 变量中
    QMouseEvent* mouseEvent = (QMouseEvent*) event;
    //检查事件类型是否为鼠标按下（MouseButtonPress）
    if(type == QEvent::MouseButtonPress) {
        //检查鼠标点击的位置是否在按钮的矩形区域内 判断鼠标是否是左键点击
        if(this->rect().contains(mouseEvent->pos()) && (mouseEvent->button() == Qt::LeftButton)) {
            lastPoint = mouseEvent->pos();
            pressed = true;
        }
    } else if(type == QEvent::MouseMove && pressed) { //检查事件类型是否为鼠标移动（MouseMove），并且按钮当前是被按下状态（pressed）
        //如果允许移动（canMove 为 true），计算鼠标当前位置与上一次记录位置的偏移量 dx 和 dy
        if(canMove) {
            int dx = mouseEvent->pos().x()-lastPoint.x();
            int dy = mouseEvent->pos().y()-lastPoint.y();
            //使用 this->move() 方法，将按钮移动到新的位置，实现拖动效果
            this->move(this->x()+dx, this->y()+dy);
        }
    } else if(type == QEvent::MouseButtonRelease && pressed) {//检查事件类型是否为鼠标释放（MouseButtonRelease），并且按钮当前是被按下状态
        pressed = false;
        //触发 clicked() 信号，表示按钮被点击完成，可以连接到其他槽函数进行处理
        Q_EMIT clicked();
    }

    //调用基类的 eventFilter 方法以确保其他事件仍然得到处理，返回该值以指示事件是否被处理
    return QWidget::eventFilter(watched, event);
}
```





####  画圆形案例

```cpp
void LightButton::drawBorderOut(QPainter *painter) {
    int radius = 100;   //设置半径
    painter->save();
    painter->setPen(Qt::NoPen);
    //创建一个线性渐变对象 borderGradient，其起始点为 (0, -radius)，终止点为 (0, radius)。这意味着渐变将沿着 Y 轴垂直方向进行
    QLinearGradient borderGradient(0, -radius, 0, radius);
    //在渐变的起始位置（Y=−radius）设置开始颜色
    borderGradient.setColorAt(0, borderOutColorStart);
    //在渐变的结束位置（Y=radius）设置结束颜色
    borderGradient.setColorAt(1, borderOutColorEnd);
    painter->setBrush(borderGradient);
    //使用 drawEllipse 方法绘制一个圆形。圆心在 (0, 0)，宽和高均为 radius * 2（即直径为 200），因此绘制的圆形的边界从 (-radius, -radius) 开始，覆盖到 (radius, radius)
    painter->drawEllipse(-radius, -radius, radius*2, radius*2); //画圆形
    painter->restore();
}
```

我就说为什么分为了外圆和内圆，原来画完之后的效果图是这样啊！

![1727523410422](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1727523410422.png)

内圆比外圆半径小，然后渐变方式相反，就达到了这样的视觉效果，真厉害