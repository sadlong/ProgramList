#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //初始化天气预报所在城市
    ui->comboBox_city->clear();
    QStringList qStrList;
    qStrList << "Beijing" << "Shanghai" << "Shenzhen" << "Guangzhou" << "Changsha" << "Chongqing";
    ui->comboBox_city->addItems(qStrList);  //将城市列表添加到下拉框中

    // 处理QLCDNumber控件
    ui->lcdNumber_Time->setDigitCount(10);  //设置 LCD 显示器的数字位数为 10
    ui->lcdNumber_Time->setMode(QLCDNumber::Dec);   //设置 LCD 显示器的模式为十进制
    ui->lcdNumber_Time->setSegmentStyle(QLCDNumber::Flat);  //设置 LCD 显示器的段样式为平面（无 3D 效果）

    QTimer* qtimer = new QTimer();
    qtimer->setInterval(1000);  //设置计时器的间隔为 1000 毫秒（即 1 秒）
    qtimer->start();    //启动计时器

    //信号和槽连接 将计时器的超时信号连接到槽函数 OnTimerOutFunc()，每当计时器超时（即每秒）时，会调用该槽函数
    connect(qtimer, SIGNAL(timeout()), this, SLOT(OnTimerOutFunc()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

//获取当前时间
void MainWidget::OnTimerOutFunc() {
    //获取系统当前时间
    QTime qtime = QTime::currentTime();

    //设置晶体管空间QLCDNumber显示时间  将当前时间格式化为 "HH:mm:ss" 并显示在 QLCDNumber 控件上
    ui->lcdNumber_Time->display(qtime.toString("HH:mm:ss"));
}

//获取当天的天气预报数据
void MainWidget::Get_CurrentWeather(QNetworkReply* qReply) {

}

//获取三天内天气预报数据
void MainWidget::Get_ThreeWeather(QNetworkReply* qReply) {

}


void MainWidget::on_pushButton_GetData_clicked()
{

}
