#include "sendfile.h"

#include <QHostAddress>
#include <qfile.h>
#include <QFileInfo>

SendFile::SendFile(QObject *parent) : QObject(parent)
{

}

void SendFile::connectServer(unsigned short port, QString ip)
{
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(ip), port);

    //当tcp产生connected信号 触发connectOk信号
    connect(m_tcp, &QTcpSocket::connected, this, &SendFile::connectOk);
    connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
        m_tcp->close();
        m_tcp->deleteLater();
        emit gameover();
    });
}

void SendFile::sendFile(QString path)
{
    qDebug() << "客户端子线程：" << QThread::currentThread();
    QFile file(path);
    QFileInfo info(path);
    int fileSize = info.size(); //文件大小 字节为单位
    file.open(QFile::ReadOnly);
//    qDebug() << 111;

    while(!file.atEnd()) {

        static int num = 0;
        if(num == 0) {
            m_tcp->write((char*)&fileSize, 4);  //需和接收端的read的第二个参数一致 都应该是4
        }

        QByteArray line = file.readLine();
        num += line.size();
        int percent = (num*100/fileSize);
        emit curPercent(percent);
        m_tcp->write(line);
    }
}
