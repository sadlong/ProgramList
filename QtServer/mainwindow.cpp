#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置一个默认端口便于测试
    ui->port->setText("8899");
    setWindowTitle("服务器");

    //创建监听的服务器对象
    m_s = new QTcpServer(this);

    connect(m_s, &QTcpServer::newConnection, this, [=](){
        m_tcp = m_s->nextPendingConnection();   //一定要先实例化m_tcp 才能调用connect
        //重新设置图片状态
        m_status->setPixmap(QPixmap(":/t.jpg").scaled(20, 20)); //setPixmap设置图片 scaled让图片缩放
        connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
            QByteArray data = m_tcp->readAll(); //全部读
            ui->recode->append("客户端说：" + data);   //追加信息
        });

        //是否断开连接
        connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
            //套接字关闭 释放 切换图片
            m_tcp->close();
            m_tcp->deleteLater();
            m_status->setPixmap(QPixmap(":/f.jpg").scaled(20, 20)); //setPixmap设置图片 scaled让图片缩放
        });
    });

    //状态栏
    m_status = new QLabel;
    m_status->setPixmap(QPixmap(":/f.jpg").scaled(20, 20)); //setPixmap设置图片 scaled让图片缩放
    ui->statusbar->addWidget(new QLabel("连接状态："));
    ui->statusbar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_setListen_clicked()
{
    unsigned short port = ui->port->text().toUShort();  //转换类型unsigned short
    m_s->listen(QHostAddress::Any, port);   //绑定本机ip地址any为任意ip
    ui->setListen->setDisabled(true);   //点击完之后设置成不可用
}

void MainWindow::on_sendMsg_clicked()
{
    QString msg = ui->msg->toPlainText();   //将纯文本的形式取出来 还有一种是html格式的 但是好像不能用QString接收
    m_tcp->write(msg.toUtf8());
    ui->recode->append("服务器说：" + msg);
}
