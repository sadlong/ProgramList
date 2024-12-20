#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>   //需要在.pro文件下添加network
#include <QThread>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    //连接服务器
    void connectServer(unsigned short port, QString ip);

    //发送文件
    void sendFile(QString path);

signals:
    void connectOk();
    void gameover();
    void curPercent(int num);

private:
    QTcpSocket* m_tcp;

public slots:
};

#endif // SENDFILE_H
