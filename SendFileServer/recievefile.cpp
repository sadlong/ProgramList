#include "recievefile.h"
#include <QFile>
#include <QDebug>

RecieveFile::RecieveFile(QTcpSocket* tcp, QObject *parent) : QThread(parent)
{
    m_tcp = tcp;
}

void RecieveFile::run()
{
    QFile* file = new QFile("recieve.txt"); //不存在则创建一个
    file->open(QFile::WriteOnly);
    qDebug() << "服务器子线程：" << QThread::currentThread();

    //接收数据
    connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
        static int cnt = 0, total = 0;
        if(cnt == 0) {
            //超级超级巨大的失误！ 这里是&total而不是total 在sendfile.cpp中也是一样的错误！ 这样导致了没有接收到文件的数据
            m_tcp->read((char*)&total, 4);
        }

        //读出剩余的数据
        QByteArray all = m_tcp->readAll();
        cnt += all.size();
        file->write(all);

        //判断是否接收完毕
        if(cnt == total) {
            m_tcp->close();
            m_tcp->deleteLater();
            file->close();
            file->deleteLater();
            emit over();
        }
    });

    //进入事件循环
    exec();
}
