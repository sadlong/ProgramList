###  Component与Loader

**动态创建并销毁组件、加载动图**

```cpp
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")



//    Component {
//        id:com
//        Rectangle {
//            id: rect
//            width: 200
//            height: 100
//            color: "black"
//            //调用component属性的内置槽函数   调用component后自动调用
//            Component.onCompleted: {
//                console.log("onCompleted", width, height, color)
//            }

//            //关闭component后自动调用
//            Component.onDestruction: {
//                console.log("onDestruction", width, height, color)
//            }
//        }
//    }

    Component {
        id: com
        //加载动图 AnimatedImage继承自Image
        AnimatedImage {
            id: img
            source: "qrc:/test.gif"
            width: 200
            height: 200
            speed: 10    //改变动图倍速
        }

    }

    Loader {
        id: loader
        //source: "MyRectangle.qml" //实现不了 不知道为啥
        asynchronous: true  //设置为异步
        sourceComponent: com
        onStateChanged: {
            console.log("status: ", status)
        }
    }

    Button {
        width: 50
        height: 50
        x: 200
        onClicked: {
            //loader.sourceComponent = null   //点击消除component

            //点击后暂停，再次点击继续动
            loader.item.paused = !loader.item.paused

            //点击后更改控件大小 只能这么改
//            loader.item.width = 100
//            loader.item.height = 100
//            loader.item.color = "red"

            //错误示范
            //com.width = 50
        }
    }
}

```

不知道为啥Loader里面不会输出status，其它效果不错~