#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog), _countdown(5)
{
    ui->setupUi(this);
    //设置成密码模式
    ui->pass_lineEdit->setEchoMode(QLineEdit::Password);
    ui->confirm_lineEdit->setEchoMode(QLineEdit::Password);


    ui->err_tip->setProperty("state", "normal");   //设置ui的属性
    repolish(ui->err_tip);  //修改颜色
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandles();
    ui->err_tip->clear();

    connect(ui->user_lineEdit, &QLineEdit::editingFinished, this, [this]() {
        checkUserValid();
    });

    connect(ui->email_lineEdit, &QLineEdit::editingFinished, this, [this]() {
        checkEmailValid();
    });

    connect(ui->pass_lineEdit, &QLineEdit::editingFinished, this, [this]() {
        checkPassValid();
    });

    connect(ui->confirm_lineEdit, &QLineEdit::editingFinished, this, [this]() {
        checkConfirmValid();
    });

    connect(ui->varify_lineEdit, &QLineEdit::editingFinished, this, [this]() {
        checkVarifyValid();
    });

    ui->pass_visible->setCursor(Qt::PointingHandCursor);
    ui->confirm_visible->setCursor(Qt::PointingHandCursor);

    ui->pass_visible->SetState("unvisible","unvisible_hover","","visible",
                                "visible_hover","");
    ui->confirm_visible->SetState("unvisible","unvisible_hover","","visible",
                                    "visible_hover","");

    connect(ui->pass_visible, &ClickedLabel::clicked, this, [this]() {
        if(ui->pass_visible->GetCurState() == ClickLbState::Normal) {
            ui->pass_lineEdit->setEchoMode(QLineEdit::Password);
        } else {
            ui->pass_lineEdit->setEchoMode(QLineEdit::Normal);
        }
        qDebug() << "label was clicked!";
    });

    connect(ui->confirm_visible, &ClickedLabel::clicked, this, [this]() {
        if(ui->confirm_visible->GetCurState() == ClickLbState::Normal) {
            ui->confirm_lineEdit->setEchoMode(QLineEdit::Password);
        } else {
            ui->confirm_lineEdit->setEchoMode(QLineEdit::Normal);
        }
        qDebug() << "Label was clicked!";
    });

    //创建定时器
    _countdown_timer = new QTimer(this);

    //连接信号和槽
    connect(_countdown_timer, &QTimer::timeout, this, [this]() {
        if(_countdown == 0) {
            _countdown_timer->stop();
            emit sigSwichLogin();   //切换到第一个界面
            return;
        }
        _countdown--;
        auto str = QString("login successfully, return after %1 second").arg(_countdown);
        ui->tip_lb->setText(str);
    });


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

    //注册注册用户回包逻辑
    m_handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("canshu error"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("sign up sucessfully"), true);
        qDebug() << "user uuid is " << jsonObj["uid"].toString();
        qDebug()<< "email is " << email ;
        ChangeTipPage();
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

void RegisterDialog::AddTipErr(TipErr te, QString tips) {
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void RegisterDialog::DelTipErr(TipErr te) {
    _tip_errs.remove(te);
    if(_tip_errs.empty()) {
        ui->err_tip->clear();
        return;
    }
    showTip(_tip_errs.first(), false);
}

bool RegisterDialog::checkUserValid()
{
    if(ui->user_lineEdit->text() == "") {
        AddTipErr(TipErr::TIP_USER_ERR, tr("user name is empty"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegisterDialog::checkEmailValid()
{
    auto email = ui->email_lineEdit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(!match) {
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("email is not correct"));
        return false;
    }

    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool RegisterDialog::checkPassValid()
{
    auto pass = ui->pass_lineEdit->text();
    auto confirm = ui->confirm_lineEdit->text();
    if(pass.size() < 6 || pass.size() > 15) {
        //长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("length of password should be 6-15"));
        return false;
    }

    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("can not include invalid character"));
        return false;;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

bool RegisterDialog::checkConfirmValid()
{
    auto pass = ui->pass_lineEdit->text();
    auto confirm = ui->confirm_lineEdit->text();
//    if(pass.size() < 6 || pass.size() > 15) {
//        //长度不准确
//        AddTipErr(TipErr::TIP_PWD_CONFIRM, tr("length of password should be 6-15"));
//        return false;
//    }

//    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
//    bool match = regExp.match(pass).hasMatch();
//    if(!match){
//        //提示字符非法
//        AddTipErr(TipErr::TIP_PWD_CONFIRM, tr("can not include invalid character"));
//        return false;;
//    }

    if(pass != confirm) {
        AddTipErr(TipErr::TIP_PWD_CONFIRM, tr("confirm password is not equal to password"));
        return false;
    }

    DelTipErr(TipErr::TIP_PWD_CONFIRM);
    return true;
}

bool RegisterDialog::checkVarifyValid()
{
    if(ui->varify_lineEdit->text() == "") {
        AddTipErr(TipErr::TIP_VARIFY_ERR, tr("verify code should not be empty"));
        return false;
    }

    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}

void RegisterDialog::on_sure_btn_clicked()
{
    if(ui->user_lineEdit->text() == ""){
        showTip(tr("name empty"), false);
        return;
    }
    if(ui->email_lineEdit->text() == ""){
        showTip(tr("email empty"), false);
        return;
    }
    if(ui->pass_lineEdit->text() == ""){
        showTip(tr("password empty"), false);
        return;
    }
    if(ui->confirm_lineEdit->text() == ""){
        showTip(tr("confirm password empty"), false);
        return;
    }
    if(ui->pass_lineEdit->text() != ui->confirm_lineEdit->text()){
        showTip(tr("password and confirm is not same"), false);
        return;
    }
    if(ui->varify_lineEdit->text() == ""){
        showTip(tr("code is empty"), false);
        return;
    }
    //day11 发送http请求注册用户
    QJsonObject json_obj;
    json_obj["user"] = ui->user_lineEdit->text();
    json_obj["email"] = ui->email_lineEdit->text();
    json_obj["passwd"] = xorString(ui->pass_lineEdit->text());
    json_obj["confirm"] = xorString(ui->confirm_lineEdit->text());
    json_obj["varifycode"] = ui->varify_lineEdit->text();
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                 json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);
}

void RegisterDialog::ChangeTipPage() {
    _countdown_timer->stop();
    ui->stackedWidget->setCurrentWidget(ui->page_2);

    //启动定时器
    _countdown_timer->start(1000);
}

void RegisterDialog::on_return_btn_clicked()
{
    _countdown_timer->stop();
    emit sigSwichLogin();
}

void RegisterDialog::on_cancel_pushButton_clicked()
{
    qDebug() << "return to login";
    emit sigSwichLogin();
}
