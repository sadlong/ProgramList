#ifndef RECIEVEFILE_H
#define RECIEVEFILE_H

#include <QThread>
#include <QTcpSocket>

class RecieveFile : public QThread
{
    Q_OBJECT
public:
    explicit RecieveFile(QTcpSocket* tcp, QObject *parent = nullptr);

protected:
    void run() override;

private:
    QTcpSocket* m_tcp;

signals:
    void over();

public slots:
};

#endif // RECIEVEFILE_H
