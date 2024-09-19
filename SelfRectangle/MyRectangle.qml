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
