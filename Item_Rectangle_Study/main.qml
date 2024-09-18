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
