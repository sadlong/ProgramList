#include "login.h"
#include "ui_login.h"
#include<QToolButton>
#include<QPixmap>
#include "widget.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    QVector<QToolButton*> vector;
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/qq.png"));
    this->setWindowTitle("QQ");
    //用户名列表
    QStringList list;
    list<<"张三"<<"李四"<<"王五"<<"旭日干"<<"陈德强"<<"丁一同"<<"孟广杰"<<"黎萱晨"<<"陈淑明";
    //图片资源列表
    QStringList listIcon;
    listIcon<<"spqy"<<"ymrl"<<"qq"<<"xrg"<<"cdq"<<"dyt"<<"mgj"<<"lxc"<<"spqy";

    for(int i=0;i<9;i++){
       QToolButton *btn=new QToolButton(this);
       btn->setIcon(QPixmap(QString(":/images/%1.png").arg(listIcon[i])));
       btn->setIconSize(QPixmap(QString(":/images/%1.png").arg(listIcon[i])).size());
      //透明
       btn->setAutoRaise(true);
        //设置网名
       btn->setText(QString("%1").arg(list[i]));
       //设置显示格式
       btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
       ui->vlayout->addWidget(btn);
       vector.push_back(btn);
       isShow.push_back(false);
    }
    for(int i=0;i<9;i++){
        connect(vector[i],&QToolButton::clicked,[=](){
            if(true==isShow[i]){
                QMessageBox::warning(this,"警告","该聊天框已被打开");
                return;
            }
            isShow[i]=true;
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
}

Login::~Login()
{
    delete ui;
}
