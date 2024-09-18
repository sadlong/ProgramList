###  QML-Item与Rectangle

**解决哪个控件在上方的问题**

```cpp
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("My QML")
    color: "white"

    Rectangle {
        x: 100
        y: 100
        z: 1    //不加这一行默认蓝色矩形会覆盖黑色矩形，z坐标默认是0
        width: 100
        height: 50
        color: "black"
    }

    Rectangle {
        x: 120
        y: 120
        width: 100
        height: 50
        color: "blue"
    }

}
```

在这段代码中如果将`z:1`注释掉会让蓝色矩形覆盖掉黑色矩形，如果想要达到黑色矩形在上方的话就需要加上那一行



**鼠标选中聚焦后接收键盘信息**

```cpp
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("My QML")
    color: "white"

    Rectangle {
        x: 100
        y: 100
        width: 100
        height: 50
        color: "black"
        focus: true	//设置默认聚焦

        MouseArea {
            anchors.fill: parent	//填充在父控件当中
            onClicked: {
                console.log("on clicked")
            }
        }

        //鼠标点击矩形框之后按下enter键就会在控制台上输出
        Keys.onReturnPressed: {
            console.log("on return pressed")
        }
    }
}
```





**anchor用法**

```cpp
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("My QML")
    color: "white"

    Rectangle {
        id: rect1
        width: 50
        height: 50
        color: "black"
        anchors.centerIn: parent    //控件居中 但是不知道为什么加了这一句另外两个控件显示就不对了
    }

    Rectangle {
        id: rect2
        width: 100
        height: 50
        anchors.left: rect1.right	//将rect2的左边接在rect1的右边
        anchors.leftMargin: 20	//设置两个控件之间的距离
        color: "black"
    }

    Rectangle {
        id: rect3
        width: 100
        height: 50
        anchors.top: rect1.bottom	//将rect2的顶边接在rect1的下面
        anchors.topMargin: 20	//设置两个控件之间的距离
        color: "black"
    }
}
```

显示效果如下：
![1726657285613](C:\Users\123\AppData\Roaming\Typora\typora-user-images\1726657285613.png)



**scale和rotation**

- `scale: num`用来放缩控件，num是多少就放大多少倍
- `rotation: num`用来旋转控件，num是多少就顺时针旋转多少度

```cpp
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("My QML")
    color: "white"

    Rectangle {
        width: 100
        height: 50
        color: "black"
        border.width: 2 //边框粗细调节 越大越粗
        border.color: "green"  //边框颜色
        anchors.centerIn: parent    //将控件居中 以父控件为中心
        rotation: 30    //顺时针旋转30度
        scale: 2    //放缩控件，数字是多少就方法多少倍
        radius: 15  //调整圆角幅度 数值越大幅度越大
    }


    //渐变色gradient样例
    Rectangle {
        y: 100; width: 80; height: 80
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightsteelblue" }
            GradientStop { position: 1.0; color: "blue" }
        }
    }
}
```

