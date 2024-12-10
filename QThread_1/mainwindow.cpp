#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建子线程对象
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    connect(this, &MainWindow::starting, gen, &Generate::recvNum);
    //启动子线程
    connect(ui->start, &QPushButton::clicked, this, [=](){
        emit starting(10000);  //执行10次
        gen->start();
    });

    connect(gen, &Generate::sendArray, bubble, &BubbleSort::recvArray);
    connect(gen, &Generate::sendArray, quick, &QuickSort::recvArray);
    //接收子线程发送的数据
    connect(gen, &Generate::sendArray, this, [=](QVector<int> list) {
        bubble->start();
        quick->start();
        for(int i = 0; i < list.size(); i++) {
            ui->randList->addItem(QString::number(list[i]));
        }
    });
    connect(bubble, &BubbleSort::finish, this, [=](QVector<int> list) {
        for(int i = 0; i < list.size(); i++) {
            ui->bubulList->addItem(QString::number(list[i]));
        }
    });
    connect(quick, &QuickSort::finish, this, [=](QVector<int> list) {
        for(int i = 0; i < list.size(); i++) {
            ui->quickList->addItem(QString::number(list[i]));
        }
    });

    connect(this, &MainWindow::destroyed, this, [=]() {
        gen->quit();
        gen->wait();
        gen->deleteLater();

        bubble->quit();
        bubble->wait();
        bubble->deleteLater();

        quick->quit();
        quick->wait();
        quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//这样写转到槽不合适，因为gen对象是死在Mainwindow的构造函数中实例化的 是一个局部变量，在这里使用不了gen对象
//void MainWindow::on_start_clicked()
//{
//    emit starting(10000);  //执行10次
//    gen->start();
//}
