#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置一个默认端口便于测试
    ui->port->setText("8899");
    ui->ip->setText("127.0.0.1");
    setWindowTitle("客户端");

    ui->disconbine->setDisabled(true);

    //创建监听的服务器对象
    m_tcp = new QTcpSocket;

    connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
        QByteArray data = m_tcp->readAll(); //全部读
        ui->recode->append("服务器说：" + data);   //追加信息
    });

    connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
        //套接字关闭 释放 切换图片
        m_tcp->close();
        m_tcp->deleteLater();
        m_status->setPixmap(QPixmap(":/f.jpg").scaled(20, 20)); //setPixmap设置图片 scaled让图片缩放
        ui->recode->append("服务器已经和客户端断开了连接...");
        ui->disconbine->setDisabled(true);
        ui->conbine->setEnabled(true);
    });

    connect(m_tcp, &QTcpSocket::connected, this, [=](){
        m_status->setPixmap(QPixmap(":/t.jpg").scaled(20, 20)); //setPixmap设置图片 scaled让图片缩放
        ui->recode->append("已经成功连接到服务器...");
        ui->disconbine->setEnabled(true);
        ui->conbine->setDisabled(true);
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


void MainWindow::on_sendMsg_clicked()
{
    QString msg = ui->msg->toPlainText();   //将纯文本的形式取出来 还有一种是html格式的 但是好像不能用QString接收
    m_tcp->write(msg.toUtf8());
    ui->recode->append("客户端说：" + msg);
}

void MainWindow::on_conbine_clicked()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    m_tcp->connectToHost(QHostAddress(ip), port);   //参数ip 和 端口
}

void MainWindow::on_disconbine_clicked()
{
    m_tcp->close();
    ui->conbine->setEnabled(true);
    ui->disconbine->setDisabled(true);
}
