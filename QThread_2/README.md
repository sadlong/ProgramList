## 多线程第二种写法

### 大致步骤

- 创建子线程对象，形如`QThread* t1 = new QThread;`，有多少个子线程，就需要创建多少个QThread
- 自定义任务类对象，这个类是继承自QObject而不是QThread，所以里面并不需要重写run方法，只需要自定义一个任务函数即可，比如说working，working函数是可以传入参数的，而重写的run方法是不能有参数的，解决的方法可以通过定义成员变量和信号槽函数传入参数给成员变量
- 将任务对象移动到某个子线程中，形如`gen->moveToThread(t1);`，这行代码的意思是将任务对象移动到t1线程上
- 启动子线程`t1->start()`这里和第一种方法有点区别，虽然启动了子线程，但不会开始工作，需要通过信号槽函数来调用working函数才能让子线程开始工作，任务对象的任务函数可以有多个，亦或者是功能不相同的函数，`这也是继承QObject的子线程方法与继承QThread的子线程方法的最大的不同`，继承自QObject方法可以灵活处理子线程的多种功能，而直接继承run方法相对来说比较单一
- 释放线程对象以及任务对象





### 问题解决

> QObject::moveToThread: Current thread (0x9bd1fb0) is not the object's thread (0xb6e5bf0).
>
> QObject::moveToThread: Cannot move objects with a parent

这个问题分别出现在创建子线程对象和任务对象的时候指定了父对象导致的，它们在实例化对象的时候是一定不要指定父对象的