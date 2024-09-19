###  自定义边框Rectangle

右键`/`文件选中add new...--->选中Qt(QML File)--->取名MyRectangle(取名随意)



**源码**

MyRectangle.qml

```cpp
import QtQuick 2.0

//实际上实现的是Rectangle内置的border.width,可以自定义长度边界
Rectangle {
    id: borderRect

    //将属性暴露出去 以便更好的灵活改变边距大小
    property int myTopMargin: 0
    property int myBottomMargin: 0
    property int myLeftMargin: 0
    property int myRightMargin: 0
    color: "red"    //边框颜色为红色
    Rectangle {
        id: innerRect
        color: "yellow" //实际内部的矩形为黄色
        anchors.fill: parent    //填充父控件borderRect可用的空间

        //设置边距
        anchors.topMargin: myTopMargin
        anchors.bottomMargin: myBottomMargin
        anchors.leftMargin: myLeftMargin
        anchors.rightMargin: myRightMargin
    }
}
```



main.qml

```cpp
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    //调用自定义矩形
    MyRectangle {
        //显示的起始位置
        x: 100
        y: 50

        //设置长宽
        width: 200
        height: 100

        //设置边缘宽度
        myTopMargin: 5
        myBottomMargin: 5
        myLeftMargin: 10
    }
}

```



**效果图**

![1726731606227](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1726731606227.png)

**小结**

这个demo主要是实现了上一节课讲的border.width，由于border.width修改的是整个边界，而不能仅仅修改某一边，通过这个实例很好的展现了将不同边设置不同边距，或者不设置的案例。除此之外这里还涉及到工程中的灵活性，就是将属性暴露出去，这样就能灵活的设置边距了。

