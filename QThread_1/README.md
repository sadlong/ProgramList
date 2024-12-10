## 多线程编程

### Qt多线程实现步骤

- 自定义线程类，首先add new，这个类要继承自QThread，但是在Qt5中没有QThread这个选项，所以我们通常继承自QObject类，创建完成之后手动修改，需要包含头文件`#include <QThread>`
- 创建子线程对象，在这个项目中以Generate类为例，这是一个生成随机数的子线程类，通过`Generate* gen = new Generate`来实例化对象
- 重写子线程类里面的run方法，run方法通常是protected类型的，在.h文件声明之前最好带上protected，因为最后是通过start方法来调用的，run方法的接口是不对外开放的
- 调用start方法启动子线程
- 线程与线程之间的通信只能通过信号槽函数来建立连接，不能直接通过子线程的数据放到主线程的窗口中显示，期间一定需要信号槽的参与

###  计算执行用时

声明头文件`#include <QElapsedTimer>`，这个类的目的主要是计算在程序运行的过程中某个阶段的执行用时，下面是给出的应用例子，代码示例中的省略号就代表的是循环体或者是函数体

```cpp
QElapsedTimer time;
time.start();
...
int deltaTime = time.elapsed();
qDebug() << "生成" << m_num << "个随机数总共用时：" << deltaTime << "毫秒";
```





























### 遇到的问题

> QObject::connect: Cannot queue arguments of type 'QVector<int>'
>
> (Make sure 'QVector<int>' is registered using qRegisterMetaType().)

解决方法：在main.cpp中写上`qRegisterMetaType<...>("...");`这里面的省略号就是对应的`QVector<int>`