#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    // QChart为图表库，专门用于创建和显示各种类型的图表（线图、柱状图、饼图等）
    //pChart = new QChart();
    QChart* pChart = new QChart(); //管理数据指针

    //创建5个柱状图线条数据
    QBarSet* pSet1 = new QBarSet("芙蓉王硬蓝");
    QBarSet* pSet2 = new QBarSet("和天下");
    QBarSet* pSet3 = new QBarSet("万宝路");
    QBarSet* pSet4 = new QBarSet("中南海");
    QBarSet* pSet5 = new QBarSet("中华");

    //为柱状图赋值
    *pSet1 << 2300 << 1000 << 1333 << 1555 << 3000; //向香烟柱状添加每个月的销售数据
    *pSet2 << 2100 << 500 << 1333 << 555 << 2500; //向香烟柱状添加每个月的销售数据
    *pSet3 << 1800 << 1700 << 2333 << 2555 << 3500; //向香烟柱状添加每个月的销售数据
    *pSet4 << 2700 << 1900 << 1333 << 555 << 1500; //向香烟柱状添加每个月的销售数据
    *pSet5 << 2200 << 700 << 1333 << 555 << 3100; //向香烟柱状添加每个月的销售数据

//    pSet1->setLabelColor(QColor(0,0,0));    //黑色
//    pSet2->setLabelColor(QColor(0,0,0));    //黑色
//    pSet3->setLabelColor(QColor(0,0,0));    //黑色
//    pSet4->setLabelColor(QColor(0,0,0));    //黑色
//    pSet5->setLabelColor(QColor(0,0,0));    //黑色

    QBarSeries* pSeries = new QBarSeries();
    pSeries->append(pSet1);
    pSeries->append(pSet2);
    pSeries->append(pSet3);
    pSeries->append(pSet4);
    pSeries->append(pSet5);
    pSeries->setLabelsVisible(false);    //设置柱状图上的标签 数据值为不可见

    pChart->addSeries(pSeries); //将柱状图添加道QChart
    QBrush brush(Qt::red);
    pChart->setTitleBrush(brush);
    pChart->setTitle("香烟销售统计表（王中王分店）");
    pChart->setTitleFont(QFont("黑体"));

    //创建水平分类轴
    QBarCategoryAxis* pAxisX = new QBarCategoryAxis();
    pAxisX->append("January(Jan)");
    pAxisX->append("Febrary(Feb)");
    pAxisX->append("March(Mar)");
    pAxisX->append("April(Apr)");
    pAxisX->append("May(May)");
    pAxisX->setLabelsColor(Qt::black);


    QValueAxis* pAxisY = new QValueAxis();
    pAxisY->setRange(0, 4000);  //最小和最大值
    pAxisY->setTitleText("Price");
    pAxisY->setLabelFormat("%d");

    //将轴添加到图表中
    pChart->setAxisX(pAxisX, pSeries);
    pChart->setAxisY(pAxisY, pSeries);

    //pChartView用于在界面上显示pChart
    pChartView = new QChartView(pChart);
    pContainer->setLayout(new QHBoxLayout());   //设置窗口控件布局管理器
    pContainer->layout()->addWidget(pChartView);    //将图表视图添加到窗口控件布局管理器
}

MainDialog::~MainDialog()
{
    delete ui;
}

