#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //设置成密码模式
    ui->pass_lineEdit->setEchoMode(QLineEdit::Password);
    ui->confirm_lineEdit->setEchoMode(QLineEdit::Password);


    ui->err_tip->setProperty("state", "normal");   //设置ui的属性
    repolish(ui->err_tip);  //修改颜色
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandles();

    //这样修改字体颜色也行 博主的写法是将修改颜色样式的操作集中在一个文件中
//    ui->err_tip->setStyleSheet("color:red");
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_get_code_clicked()
{
    //获取输入框中的文本
    auto email = ui->email_lineEdit->text();
    //规定正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    //匹配
    bool match = regex.match(email).hasMatch();
    if(match) {
        //发送http验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        qDebug() << "gate_url_prefix is " << gate_url_prefix;
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/get_verifycode"), json_obj, ReqId::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);
    } else {
        //这里输入中文有问题 在第一节课的时候提到过 可能是编译器处理的不同 用MINGW可能没问题
        showTip(tr("email input error"), false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS) {
        showTip(tr("network request error"), false);
        return;
    }

    //解析JSON字符串 res转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()) {
        showTip(tr("json failed"), false);
        return;
    }
    //json 解析错误
    if(!jsonDoc.isObject()) {
        showTip(tr("json failed"), false);
        return;
    }

    m_handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::initHttpHandles()
{
    //注册获取验证码回包的逻辑
    m_handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj) {
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS) {
            showTip(tr("canshu error"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip(tr("code sent to email, please check"), true);
        qDebug() << "email is " << email;
    });
}

void RegisterDialog::showTip(QString str, bool ok)
{
    if(ok) {
        ui->err_tip->setProperty("state", "normal");
    } else {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(str);

    repolish(ui->err_tip);
}
