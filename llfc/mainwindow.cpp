#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "tcpmgr.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login = new LoginDialog(this);
    _login->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_login);    //将自定义的ui布局设置成中心控件
//    _login->show();

    connect(_login, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    connect(_login, &LoginDialog::switchReset, this, &MainWindow::SlotSwitchReset);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_swich_chatdlg, this, &MainWindow::SlotsSwitchChat);
    emit TcpMgr::GetInstance()->sig_swich_chatdlg();
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

void MainWindow::SlotSwitchReg()
{
    _register = new RegisterDialog(this);
    _register->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    connect(_register, &RegisterDialog::sigSwichLogin, this, &MainWindow::SlotSwitchLogin);
    setCentralWidget(_register);
    _login->hide();
    _register->show();
}

void MainWindow::SlotSwitchLogin()
{
    _login = new LoginDialog(this);
    _login->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_login);    //将自定义的ui布局设置成中心控件
    _register->hide();
    _login->show();
    //连接登录界面忘记密码信号
    connect(_login, &LoginDialog::switchReset, this, &MainWindow::SlotSwitchReset);
    //连接登录界面注册信号
    connect(_login, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
}

void MainWindow::SlotSwitchReset() {
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    _reset_dlg = new ResetDialog(this);
    _reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    //注册返回登录信号和槽函数
    connect(_reset_dlg, &ResetDialog::switchLogin, this, &MainWindow::SlotSwitchLogin2);
    setCentralWidget(_reset_dlg);
    _login->hide();
    _reset_dlg->show();

}

void MainWindow::SlotSwitchLogin2() {
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    _login = new LoginDialog(this);
    _login->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login);
    _reset_dlg->hide();
    _login->show();
    //连接登录界面忘记密码信号
    connect(_login, &LoginDialog::switchReset, this, &MainWindow::SlotSwitchReset);
    //连接登录界面注册信号
    connect(_login, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
}

void MainWindow::SlotsSwitchChat()
{
    _chat_dlg = new ChatDialog(this);
    _chat_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_chat_dlg);
    _chat_dlg->show();
    _login->hide();
    //不能拉伸
    this->setMinimumSize(QSize(1200, 700));
    this->setMaximumSize(QSize(1200, 700));
}
