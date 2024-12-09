## 多线程编程





























### 遇到的问题

> QObject::connect: Cannot queue arguments of type 'QVector<int>'
>
> (Make sure 'QVector<int>' is registered using qRegisterMetaType().)

解决方法：在main.cpp中写上`qRegisterMetaType<...>("...");`这里面的省略号就是对应的`QVector<int>`