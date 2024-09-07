#ifndef UDPSERVERCOMM_H
#define UDPSERVERCOMM_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class UDPServerComm : public QObject
{
    Q_OBJECT
public:
    explicit UDPServerComm(QObject *parent = nullptr);

public:
    QUdpSocket* p_udpSocketobject;
    QHostAddress p_HostAddress;

public slots:
};

#endif // UDPSERVERCOMM_H
