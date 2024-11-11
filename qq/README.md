##  仿QQ多人聊天室

###  login.cpp

**窗口设置**

```cpp
this->setWindowIcon(QIcon(":/images/qq.png"));
this->setWindowTitle("QQ");
```

这里的路径与以前写的不同，原因是在 Qt 中，以 `:/` 开头的路径表示的是资源文件系统中的路径，而 `./` 则表示普通的文件系统相对路径 



**初始化用户列表**

```cpp
QVector<QToolButton*> vector;   //存放按钮的容器
//用户名列表
QStringList list;
list<<"张三"<<"李四"<<"王五"<<"xrg"<<"cdq"<<"dyt"<<"mgj"<<"lxc"<<"csm";
//图片资源列表
QStringList listIcon;
listIcon<<"spqy"<<"ymrl"<<"qq"<<"xrg"<<"cdq"<<"dyt"<<"mgj"<<"lxc"<<"spqy";

//循环创建按钮对象及其对应姓名
for(int i=0;i<9;i++){
    QToolButton *btn=new QToolButton(this);	//父对象为this 保证了资源释放
    //设置按钮图标
    btn->setIcon(QPixmap(QString(":/images/%1.png").arg(listIcon[i])));
    //设置图标大小为对应图片的大小
    btn->setIconSize(QPixmap(QString(":/images/%1.png").arg(listIcon[i])).size());
    //设置按钮为透明效果（自动凸起）
    btn->setAutoRaise(true);
    //设置网名
    btn->setText(QString("%1").arg(list[i]));
    //设置按钮的显示格式，使文本显示在图标旁边 貌似只有这一种显示方式。。。
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //将按钮添加到垂直布局管理器ui->vlayout中
    ui->vlayout->addWidget(btn);
    vector.push_back(btn);   //每创建一个btn就加入到vector中
    isShow.push_back(false);
}
```

- `QVector<QToolButton*>`用来管理`QToolButton*`，以便后续展示用户名列表
- `QStringList`在Qt用来存储字符串列表的，用途相当于`vector<string>`
- `btn->setIcon(QPixmap(QString(":/images/%1.png").arg(listIcon[i])));`首先调用QString中的arg函数，将listIcon[i]替换%1，例如listIcon[i]"QQ"，那么资源路径就替换成了":/images/QQ.png"，然后通过QPixmap类来加载这个路径下对应的资源，这一行大致可以用作模板
- `btn->setAutoRaise(true);`设置按钮为透明效果（自动凸起）
- `btn->setText(QString("%1").arg(list[i]));`和设置按钮图标大致类似，只不过就是不需要通过`QPixmap`来加载图片资源，直接通过得到的字符串传给`setText`函数即可
- `btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);`让字体显示在图片旁边



**展示用户列表**

```cpp
for(int i=0;i<9;i++){
    connect(vector[i],&QToolButton::clicked,[=](){
        if(true==isShow[i]){
            QMessageBox::warning(this,"警告","该聊天框已被打开");
            return;
        }
        isShow[i]=true;
        //打开对应用户的聊天窗口
        Widget *widget=new Widget(0,vector[i]->text());
        widget->setWindowIcon(vector[i]->icon());
        widget->setWindowTitle(vector[i]->text());
        widget->show();
        //关闭聊天框时将对于的isShow跟改为false
        connect(widget,&Widget::closeWidget,[=](){
            isShow[i]=false;
        });
    });
}
```

主要是信号与槽的应用，监控了按钮的点击事件和聊天框的关闭事件，点开的时候isShow[i]变为true，关闭的时候变为false，这里用循环的目的是动态管理多个聊天框