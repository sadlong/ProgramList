#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "sendfile.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "客户端主线程：" << QThread::currentThread();

    ui->ip->setText("127.0.0.1");
    ui->port->setText("8899");
    ui->progressBar->setRange(0, 100);  //范围在（0， 100）
    ui->progressBar->setValue(0);   //设置初始化进度条为0

    //创建线程对象
    QThread* t = new QThread; //这里不能设置父对象

    //创建工作对象
    SendFile* worker = new SendFile; //这里不能设置父对象

    worker->moveToThread(t);

    connect(this, &MainWindow::sendFile, worker, &SendFile::sendFile);

    //接收信号的对象在哪个线程上 那么对应的槽函数就在哪个线程上执行
    connect(this, &MainWindow::startConnect, worker, &SendFile::connectServer);

    //处理主线程发送的信号
    connect(worker, &SendFile::connectOk, this, [=](){
        QMessageBox::information(this, "连接服务器", "已经成功连接了服务器， 恭喜！");
    });
    connect(worker, &SendFile::gameover, this, [=](){
        t->quit();
        t->wait();
        worker->deleteLater();
        t->deleteLater();
    });

    connect(worker, &SendFile::curPercent, ui->progressBar, &QProgressBar::setValue);

    t->start();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectServer_clicked()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    emit startConnect(port, ip);
}

void MainWindow::on_selFile_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if(path.isEmpty()) {
        QMessageBox::warning(this, "打开文件", "选择的文件的路径不能为空！");
        return;
    }
    ui->filePath->setText(path);
}

void MainWindow::on_sendFile_clicked()
{
    emit sendFile(ui->filePath->text());
}
