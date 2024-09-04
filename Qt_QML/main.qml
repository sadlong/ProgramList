import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true   //可见
    width: 900  //宽度
    height: 550 //高度
    title: qsTr("Qt开发工程师课程--QML高级编程（下拉菜单）")

    menuBar:MenuBar {
        //在菜单栏中创建一个菜单
        Menu {
            title: qsTr("零声教育高端课程")
            Action {
                text: qsTr("Linux内核源码分析")
                onTriggered: console.log("各位同学们，你现在已经点击【Linux内核源码分析课程】")    //点击后在控制台中输出
            }
            Action {
                text: qsTr("Qt开发工程师课程")
                onTriggered: console.log("各位同学们，你现在已经点击【Qt开发工程师课程】")    //点击后在控制台中输出
            }
            Action{text:qsTr("音视频高级课程")}
            Action{text:qsTr("Linux C++高级架构师课程")}
            Action{text:qsTr("BAT大厂技术面试课程")}

            delegate: GreenMenuItem{}   //设置自定义的菜单项委托，用于定义菜单项的样式和行为
            background: GreenMenuBarBg{}    //设置菜单的背景样式
        }


        Menu {
            title: qsTr("Qt开发工程师课程技术栈")
            Action{text:qsTr("C/C++基础专栏")}
            Action{text:qsTr("数据结构与算法设计")}
            Action{text:qsTr("Qt框架开发（入门到精通）")}
            Action{text:qsTr("MySQL数据库编程")}
            Action{text:qsTr("SQLite数据库编程")}
            Action{text:qsTr("C++设计模式")}
            Action{text:qsTr("OpenGL高级编程")}

            delegate: GreenMenuItem{}   //设置自定义的菜单项委托，用于定义菜单项的样式和行为
            background: GreenMenuBarBg{}    //设置菜单的背景样式
        }

        Menu {
            title: qsTr("零声讲师团队")
            Action{text:qsTr("King老师")}
            Action{text:qsTr("Nico老师")}
            Action{text:qsTr("xuge老师")}
            Action{text:qsTr("dajiang老师")}
            Action{text:qsTr("baby老师")}
            Action{text:qsTr("桃子老师")}

            delegate: GreenMenuItem{}   //设置自定义的菜单项委托，用于定义菜单项的样式和行为
            background: GreenMenuBarBg{}    //设置菜单的背景样式
        }
    }
}
