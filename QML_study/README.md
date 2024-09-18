###  QML-Window介绍

在这一节主要是介绍了Window控件的一些调用，不会的话就去帮助文档搜索Window去试试。除此之外还有一次实例应用：`焦点在哪个控件上`，这里是给出了两个button控件来通过鼠标点击和键盘按钮来改变焦点位置，同时在改变的过程中用颜色高亮和控制台输出来证实程序的正确性，完整代码如下：

```cpp
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    //以屏幕左上角为(0,0),运行之后窗口就会显示在相对于源点(50, 50)的位置
    x: 600
    y: 300

    //限定窗口大小，不能被拉伸 方法就是都对应上width和height的数值一样
    minimumWidth: 640
    minimumHeight: 480
    maximumWidth: 640
    maximumHeight: 480

    //透明度范围0-1
    opacity: 0.8

    //内置信号与槽函数 这个例子是改变窗口宽度来输出当前宽度 要调用这个槽函数通常是on+空间名称然后会显示出来
//    onWidthChanged: {
//        console.log("width:", width)
//    }

    Button {
        id: btn1
        objectName: "btn1"  //控件起名字
        focus: true //默认以btn1聚焦
        width: 50
        height: 50
        background: Rectangle {
            border.color: btn1.focus ? "blue" : "black"
        }

        //鼠标点击事件
        onClicked: {
            console.log("btn1 clicked")
        }

        //点击键盘右键事件
        Keys.onRightPressed: {
            btn2.focus = true
        }
    }

    Button {
        id: btn2
        objectName: "btn2"
        x: 100
        width: 50
        height: 50
        background: Rectangle {
            border.color: btn2.focus ? "blue" : "black"
        }
        onClicked: {
            console.log("btn2 clicked")
        }
        Keys.onLeftPressed: {
            btn1.focus = true
        }
    }

    onActiveFocusItemChanged: {
        console.log("active focus item changed", activeFocusItem, "object name:", activeFocusItem.objectName)
    }
}
```

