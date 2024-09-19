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
