###  MouseArea

```cpp
import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MouseArea {
        id: mouseArea
        width: 200
        height: 200
        acceptedButtons: Qt.LeftButton | Qt.RightButton //让鼠标左右键都能触发
        Rectangle {
            anchors.fill: parent
            color: "black"
        }

        //点击事件
        onClicked: {
            console.log("clicked")
        }
//        //按下事件
//        onPressed: {
//            //验证按下是哪个键只能在onPressed中判断而不是onClicked中判断
//            var ret1 = pressedButtons & Qt.LeftButton
//            var ret2 = pressedButtons & Qt.RightButton
//            console.log(ret1 ? "left" : ret2 ? "right" : "other")   //三目运算符嵌套
//            console.log("pressed")
//        }
//        //松开事件
//        onReleased: {
//            console.log("release")
//        }
    }
}
```

点击事件的各种操作，详见帮助文档MouseArea

