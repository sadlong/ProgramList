##  Qt多线程文件传输

经过刚刚的Qt网络编程，会发现代码不是很好用，感觉这个程序是一次性的，举个例子，当我们打开客户端和服务器连接完之后并进行通讯，这一个流程是不会出现任何错误的，但是呢当断开客户端连接想要再次点击连接客户端就会出现卡退的情况，也可以说成是死机了。解释一下这个原因：在网络编程的代码中，整个通信是基于主线程的一个程序，当一次通信点击“断开连接”后这个进程就结束了，如果再要点击连接就会出现错误的，只能全部重新运行客户端和服务端程序。还有一种解决办法就是利用多线程来处理这件事，将通信的这一部分放在当前主进程的一个子线程下，这样当点击断开连接之后再次点击连接就不会出现上述的卡死情况了，以上就是我目前对多线程的理解~



项目地址：

- 客户端： [ProgramList/SendFileClient at main · sadlong/ProgramList](https://github.com/sadlong/ProgramList/tree/main/SendFileClient) 
- 服务器端： [ProgramList/SendFileServer at main · sadlong/ProgramList](https://github.com/sadlong/ProgramList/tree/main/SendFileServer) 



## 客户端

**创建线程**

首先在mainwindow.cpp中包含头文件`QThread	`，然后封装一个`SendFile`的类，这个类是继承自`QObject`的类，在这个类中包含两个成员函数：`connectServer`和`sendFile`，具体的使用流程以及注意事项如下：

```cpp
//创建线程对象
QThread* t = new QThread; //这里不能设置父对象

//创建工作对象
SendFile* worker = new SendFile; //这里不能设置父对象

//将工作对象移到子线程中
worker->moveToThread(t);

//接收信号的对象在哪个线程上 那么对应的槽函数就在哪个线程上执行
connect(this, &MainWindow::startConnect, worker, &SendFile::connectServer);

//启动子线程
t->start();

//子线程的退出 通常写在某个退出函数中或者connect中
t->quit();
t->wait();
```

以上的几行代码介绍了线程的创建及其注意事项，并且如何在一个子线程中启动这个客户端。`startConnect`是一个自定义的信号函数，它触发的时机在点击按钮后执行了一行`emit startConnect(port, ip);`，随后就调用了上面的信号槽函数，成功实现了在子线程中执行这个客户端的连接程序。



**connect函数知识补充**

在上面的信号槽函数中，两个函数`startConnect`和`connectServer`都是自定义的两个函数，这两个函数都是有讲究的，信号函数的参数是逐个传递给槽函数的，所以这里的两个参数分别是port端口号和ip地址，参数也是最好要一致吧。

在这个项目demo中信号槽函数起到了主线程和子线程之间的通信，子线程有许多自定义信号，在主线程中处理这些信号，这样就使得了主线程和子线程之间的通信了



**连接成功代码逻辑**

```cpp
connect(worker, &SendFile::connectOk, this, [=](){
    QMessageBox::information(this, "连接服务器", "已经成功连接了服务器， 恭喜！");
});
```

当收到worker产生的connectOk信号就调用`QMessageBox`类的`information`函数，那么connectOk是怎么产生信号的呢？这下我们看到sendfile.cpp中`m_tcp`和服务器连接成功后会发出connected信号，槽函数就对应的是connectOk，这有种信号槽函数的互连



**QProgressBar相关操作**

```cpp
ui->progressBar->setRange(0, 100);  //范围在（0， 100）
ui->progressBar->setValue(0);   //设置初始化进度条为0
connect(worker, &SendFile::curPercent, ui->progressBar, &QProgressBar::setValue);
```

第三行是处理进度条变化的通过传输文件的百分比来不断改变进度条的百分比



**选择文件事件处理**

```cpp
void MainWindow::on_selFile_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if(path.isEmpty()) {
        QMessageBox::warning(this, "打开文件", "选择的文件的路径不能为空！");
        return;
    }
    ui->filePath->setText(path);
}
```

首先需要包括头文件`QFileDialog`头文件，调用了`getOpenFileName`函数后会弹出选择文件的对话框，然后将获取的路径赋值给ui控件上