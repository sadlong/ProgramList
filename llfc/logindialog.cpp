#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->signUp_pushButton, &QPushButton::clicked, this, &LoginDialog::swichRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
