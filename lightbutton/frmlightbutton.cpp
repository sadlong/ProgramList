#include "frmlightbutton.h"
#include "ui_frmlightbutton.h"
#include "qtimer.h"
#include "qdebug.h"

frmLightButton::frmLightButton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmLightButton)
{
    ui->setupUi(this);
    this->initForm();   //这个没写。。。结果又是什么都没有显示。。。
}

frmLightButton::~frmLightButton()
{
    delete ui;
}

void frmLightButton::initForm() {
    type = 0;
    QTimer * timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
    //qDebug() << 111;
}

void frmLightButton::updateValue() {
    if(type == 0) {
        ui->lightButton1->setLightGreen();
        ui->lightButton2->setLightRed();
        ui->lightButton3->setLightBlue();
        type = 1;
    } else if(type == 1) {
        ui->lightButton1->setLightBlue();
        ui->lightButton2->setLightGreen();
        ui->lightButton3->setLightRed();
        type = 2;
    } else if(type == 2) {
        ui->lightButton1->setLightRed();
        ui->lightButton2->setLightBlue();
        ui->lightButton3->setLightGreen();
        type = 0;
    }
    //qDebug() << 111;
}

