#include "frmbattery.h"
#include "ui_frmbattery.h"

frmBattery::frmBattery(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmBattery)
{
    ui->setupUi(this);
    this->initForm();
}

frmBattery::~frmBattery()
{
    delete ui;
}

void frmBattery::initForm() {
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->Battery, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(30);
}

