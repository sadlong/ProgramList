# Qt中Socket网络编程常用

这里就拿b站上**爱编程的小丙**的demo来做总结吧，首先要感谢成功带我入门的人：爱编程的小丙和程序员长风，这两个人是讲Socket编程我听懂的课555，接下来就总结一下Qt中的socket编程



项目源码： [ProgramList/QtClient at main · sadlong/ProgramList](https://github.com/sadlong/ProgramList/tree/main/QtClient) 和
 [ProgramList/QtServer at main · sadlong/ProgramList](https://github.com/sadlong/ProgramList/tree/main/QtServer) 



跟用普通的C/C++的通信demo一样，都是服务器端的代码要难写一点



## 服务器端

首先包含头文件并定义以下成员属性：

```cpp
#include <QTcpServer>
#include <QTcpSocket>

QTcpServer* m_s;	//用于监听
QTcpSocket* m_tcp;
```



创建监听的服务器对象：

```cpp
m_s = new QTcpServer(this);
```



核心实现步骤：

```cpp
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
```

与C++实现的socket编程不同，这里没有用到while循环，这里使用的是一个槽函数来代替的循环，当接收到客户端的连接后(`&QTcpServer::newConnection`)就执行里面的匿名函数，在这里面也有一个很讲究的点就是一定要先连接上了客户端再实例化成员属性`m_tcp`，然后才能基于`m_tcp`来实现其它的槽函数(例如读写操作)。

**常用的函数**

- `&QTcpServer::newConnection`连接信号

- `m_s->nextPendingConnection()`实例化`m_tcp`
- `m_status->setPixmap(QPixmap(":/t.jpg").scaled(20, 20))`m_status是`QLable`类型`setPixmap`设置图片，`scaled()`放缩图片长宽
- `&QTcpSocket::readyRead`读信号
- `&QTcpSocket::disconnected`断开连接信号



点击*开始监听*事件

```cpp
void MainWindow::on_setListen_clicked()
{
    unsigned short port = ui->port->text().toUShort();  //转换类型unsigned short
    m_s->listen(QHostAddress::Any, port);   //绑定本机ip地址any为任意ip
    ui->setListen->setDisabled(true);   //点击完之后设置成不可用
}
```

port的类型通常都是unsigned short类型的

- `ui->port->text().toUShort()`类型转换，讲QString类型的text转化为unsigned short类型
- `listen(QHostAddress::Any, port)`监听函数，参数一：主机ip地址 参数二：端口号
- `QHostAddress::Any`表示任意ip地址
- `setDisabled(true)`这个函数主要针对的是pushButton控件，当点击完开始监听后设置按钮变成不可选中，这一点很实用





## 客户端

大致还是和服务器端相似，但是没有了监听的步骤。



头文件和成员属性：

```cpp
#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QHostAddress>

QTcpSocket* m_tcp;
QLabel* m_status;	//用于设置状态的，提示是否连接的
```





核心实现代码：

```cpp
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
```

在这里主要是对客户端连接和未连接的按钮能否选中进行了判断，总之就是**连接服务器**按钮和**断开连接**按钮是对立的，仅仅只能有一个可以选中，然后就是状态栏控件QLable的介绍，这好像是默认显示在左下角的一个控件，通用是通过信号槽的是否连接动态来显示图片。

- `addWidget(new QLabel("连接状态："))`添加控件，应该默认的是水平布局