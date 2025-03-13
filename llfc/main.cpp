#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QDebug>
#include "global.h"

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

    QString filename = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + filename);
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    qDebug() << "gate_host is " << gate_host;
    qDebug() << "gate_port is " << gate_port;
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

    MainWindow w;
    w.show();
    return a.exec();
}
