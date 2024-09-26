#pragma execution_character_set("utf-8")
#include "frmbattery.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setFamily("Microsoft Yahei");  //微软雅黑字体
    font.setPixelSize(13);
    a.setFont(font);

    QTextCodec* codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    frmBattery w;
    w.setWindowTitle("电池电量控件复现");
    w.show();
    return a.exec();
}
