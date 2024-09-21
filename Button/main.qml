import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id: btn
        width: 50
        height: 50
        autoRepeat: true    //按住的时候不断调用
        autoRepeatDelay: 3000   //延迟3秒repeat
        autoRepeatInterval: 1000    //触发repeat之后间隔1秒
        onClicked: {
            console.log("clicked")
        }
        onPressed: {
            console.log("pressed")
        }
        onReleased: {
            console.log("release")
        }
    }

//        //多个按钮 确保只有一个按钮是被选中的 在每个button中加上autoExclusive: true
//        Button {
//            id: btn1
//            width: 50
//            height: 50
//            autoExclusive: true
//            checkable: true
//        }

//        Button {
//            id: btn2
//            width: 50
//            height: 50
//            x: 60
//            autoExclusive: true
//            checkable: true
//        }

//        Button {
//            id: btn3
//            width: 50
//            height: 50
//            x: 120
//            autoExclusive: true
//            checkable: true
//        }

//        //实现单击变黑
//        checkable: true

//        //实现双击变黑
//        checkable: false
//        onCheckableChanged: {
//            console.log("changed", checkable)
//        }
//        onClicked: {
//            btn.checkable = !btn.checkable
//        }


//        onClicked: {
//            console.log("onclicked")
//        }
//        onPressed: {
//            console.log("onPressed")
//        }
//        onReleased: {
//            console.log("onReleased")
//        }
//        //长按事件
//        onPressAndHold: {
//            console.log("onPressAndHold")
//        }
}
