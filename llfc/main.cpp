#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)) {
        qDebug("open success");
        //readAll返回的是QByteArra类型，要用QLatin1String转化
        QString style = QLatin1String(qss.readAll());
        //设置样式
        a.setStyleSheet(style);
        //关闭文件
        qss.close();
    } else {
        qDebug("Open failed");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
