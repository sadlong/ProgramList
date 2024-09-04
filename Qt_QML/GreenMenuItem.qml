import QtQuick 2.5
import QtQuick.Controls 2.5

//自定义MenuItem组件
MenuItem {
    id:menuItem //为组件设置唯一标识符。
    implicitWidth: 30   //组件默认宽度
    implicitHeight: 40  //组件默认高度

    //设置字体为“微软雅黑”，大小为10点，粗体。
    font: Qt.font({family:"微软雅黑", pointSize:10, weight:Font.Bold})

    //字体颜色
    contentItem: Text {
        text: menuItem.text
        font: menuItem.font
        opacity: enabled?1.0:0.3   //透明度
        color: "white"
        horizontalAlignment: Text.AlignHCenter  //文本在 contentItem 中的水平和垂直对齐方式
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitHeight: 40
        implicitWidth: 30
        opacity: enabled?1.0:0.3
        color: menuItem.highlighted?"yellowgreen":"transparent" // 属性设置背景颜色，如果高亮则为黄绿色，否则为透明。

        //用作背景上的分割线 因为高度设置的很小所以看不出来
        Rectangle {
            color: "white"
            height: 0.1
            width: parent.width
            anchors.top: parent.top
            opacity: 0.5
        }
    }


}
