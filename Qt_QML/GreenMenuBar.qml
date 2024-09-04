import QtQuick 2.5
import QtQuick.Controls 2.5

MenuBarItem {
    id:menuBarItem
    height: 40
    width: 120

    //字体设置
    font: Qt.font({family: "微软雅黑", pointSize:10, weight:Font.Bold})

    //字体颜色
    contentItem: Text {
        text: menuBarItem.text
        font: menuBarItem.font
        opacity: enabled?1.0:0.3
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitHeight: 40
        implicitWidth: 30
        opacity: enabled?1.0:0.3
        color: menuBarItem.highlighted?"yellowgreen":"transparent"
    }
}
