#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login = new LoginDialog();
    setCentralWidget(_login);    //将自定义的ui布局设置成中心控件
    _login->show();

    connect(_login, &LoginDialog::swichRegister, this, &MainWindow::SlotSwichReg);
    //_register = new RegisterDialog();
}

MainWindow::~MainWindow()
{
    delete ui;

//    if(_login) {
//        delete _login;
//        _login = nullptr;
//    }
//    if(_register) {
//        delete _register;
//        _register = nullptr;
//    }
}

void MainWindow::SlotSwichReg()
{
    _register = new RegisterDialog();
    connect(_register, &RegisterDialog::sigSwichLogin, this, &MainWindow::SlotSwichLogin);
    setCentralWidget(_register);
    _login->hide();
    _register->show();
}

void MainWindow::SlotSwichLogin()
{
    _login = new LoginDialog();
    setCentralWidget(_login);    //将自定义的ui布局设置成中心控件
    _login->show();
}

