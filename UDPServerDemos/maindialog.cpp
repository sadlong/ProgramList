#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    setFixedSize(width(), height());    //固定窗口大小

    udpservercomm = new UDPServerComm(this);

    InitUDPSocketFunc();

    iCountMsg = 0;
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::InitUDPSocketFunc() {
    udpservercomm->p_udpSocketobject = new QUdpSocket;
    udpservercomm->p_HostAddress.setAddress("127.0.0.1");   //设置主机地址为本地地址（127.0.0.1）
    udpservercomm->p_udpSocketobject->bind(8899);   // 将 UDP 套接字绑定到端口 8899，以便接收数据

    //关联信号与槽函数
    // 连接 QUdpSocket 的 readyRead 信号到 MainDialog 类的槽函数 ReadDatagramFunc。当 UDP 套接字有数据可读时，ReadDatagramFunc 将被调用。
    connect(udpservercomm->p_udpSocketobject, &QUdpSocket::readyRead, this, [=]{ReadDatagramFunc();});
}

void MainDialog::ReadDatagramFunc() {
    QByteArray ReadData;

    //调整 ReadData 的大小，以适应接收到的待处理数据的大小。
    ReadData.resize(udpservercomm->p_udpSocketobject->pendingDatagramSize());

    QHostAddress* hostAddress = new QHostAddress("127.0.0.1");
    quint16 int_port = 8899;

    //循环检查是否有待处理的数据报。
    while(udpservercomm->p_udpSocketobject->hasPendingDatagrams()) {
        //从 UDP 套接字中读取数据报，将其存储到 ReadData 中，并设置数据源的主机地址和端口。
        udpservercomm->p_udpSocketobject->readDatagram(ReadData.data(), ReadData.size(), hostAddress, &int_port);

        //将接收到的消息追加到 UI 组件 plainTextEdit_ListMsg 中，并更新消息计数器 iCountMsg
        //qDebug() << ("Receive client messages(%1):" + QString::fromLatin1(ReadData)).arg(iCountMsg++) << endl;
        ui->plainTextEdit_ListMsg->appendPlainText(("Receive client messages(%1):" + QString::fromLatin1(ReadData)).arg(iCountMsg++));
    }
}

