#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QAction>
#include <QPixmap>

ChatDialog::ChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog),_mode(ChatUIMode::ChatMode), _state(ChatUIMode::ChatMode), _b_loading(false)
{
    ui->setupUi(this);
    ui->add_btn->SetState("normal","hover","press");
    ui->add_btn->setProperty("state","normal");
    ui->search_edit->SetMaxLength(15);
    QAction *searchAction = new QAction(ui->search_edit);
    searchAction->setIcon(QIcon(":/res/search.png"));
    ui->search_edit->addAction(searchAction,QLineEdit::LeadingPosition);
    ui->search_edit->setPlaceholderText(QStringLiteral("search"));


    // 创建一个清除动作并设置图标
    QAction *clearAction = new QAction(ui->search_edit);
    clearAction->setIcon(QIcon(":/res/close_transparent.png"));
    // 初始时不显示清除图标
    // 将清除动作添加到LineEdit的末尾位置
    ui->search_edit->addAction(clearAction, QLineEdit::TrailingPosition);

    // 当需要显示清除图标时，更改为实际的清除图标
    connect(ui->search_edit, &QLineEdit::textChanged, [clearAction](const QString &text) {
        if (!text.isEmpty()) {
            clearAction->setIcon(QIcon(":/res/close_search.png"));
        } else {
            clearAction->setIcon(QIcon(":/res/close_transparent.png")); // 文本为空时，切换回透明图标
        }

    });

    // 连接清除动作的触发信号到槽函数，用于清除文本
    connect(clearAction, &QAction::triggered, [this, clearAction]() {
        ui->search_edit->clear();
        clearAction->setIcon(QIcon(":/res/close_transparent.png")); // 清除文本后，切换回透明图标
        ui->search_edit->clearFocus();
        //清除按钮被按下则不显示搜索框
        ShowSearch(false);
    });

    ShowSearch(false);
    connect(ui->chat_user_list, &ChatUserList::sig_loading_chat_user, this, &ChatDialog::slot_loading_chat_user);
    addChatUserList();

    QPixmap pixmap(":/res/head_1.jpg");
    ui->side_head_lb->setPixmap(pixmap);
    QPixmap scaledPixmap = pixmap.scaled(ui->side_head_lb->size(), Qt::KeepAspectRatio);
    ui->side_head_lb->setPixmap(scaledPixmap);
    ui->side_head_lb->setScaledContents(true);
    //ui->side_chat_lb->setProperty("state", "normal");
    ui->side_chat_lb->SetState("normal", "hover", "pressed", "selected_normal", "selected_hover", "selected_pressed");
    ui->side_contact_lb->SetState("normal", "hover", "pressed", "selected_normal", "selected_hover", "selected_pressed");
    connect(ui->side_chat_lb, &StateWidget::clicked, this, &ChatDialog::slot_side_chat);
    connect(ui->side_contact_lb, &StateWidget::clicked, this, &ChatDialog::slot_side_contact);

    //链接搜索框输入变化
    connect(ui->search_edit, &QLineEdit::textChanged, this, &ChatDialog::slot_text_changed);
    //检测鼠标点击位置判断是否要清空搜索框
    this->installEventFilter(this);
    //设置label聊天选中状态
    ui->side_chat_lb->SetSelected(true);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::ShowSearch(bool bsearch)
{
    if(bsearch){
        ui->chat_user_list->hide();
        ui->con_user_list->hide();
        ui->search_list->show();
        _mode = ChatUIMode::SearchMode;
    }else if(_state == ChatUIMode::ChatMode){
        ui->chat_user_list->show();
        ui->con_user_list->hide();
        ui->search_list->hide();
        _mode = ChatUIMode::ChatMode;
        ui->search_list->CloseFindDlg();
        ui->search_edit->clear();
        ui->search_edit->clearFocus();
    }else if(_state == ChatUIMode::ContactMode){
        ui->chat_user_list->hide();
        ui->search_list->hide();
        ui->con_user_list->show();
        _mode = ChatUIMode::ContactMode;
        ui->search_list->CloseFindDlg();
        ui->search_edit->clear();
        ui->search_edit->clearFocus();
    }
}


void ChatDialog::addChatUserList() {
    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();
        auto *chat_user_wid = new ChatUserWid();
        chat_user_wid->SetInfo(names[name_i], heads[head_i], strs[str_i]);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->chat_user_list->addItem(item);
        ui->chat_user_list->setItemWidget(item, chat_user_wid);
    }
}

void ChatDialog::ClearLabelState(StateWidget *lb)
{
    for(auto & ele: _lb_list){
        if(ele == lb){
            continue;
        }

        ele->ClearState();
    }
}

void ChatDialog::slot_loading_chat_user()
{
    if(_b_loading){
        return;
    }

    _b_loading = true;
    LoadingDlg *loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    qDebug() << "add new data to list.....";
//    loadMoreChatUser();
    addChatUserList();
    // 加载完成后关闭对话框
    loadingDialog->deleteLater();

    _b_loading = false;
}

//void ChatDialog::loadMoreChatUser() {
//    auto friend_list = UserMgr::GetInstance()->GetChatListPerPage();
//    if (friend_list.empty() == false) {
//        for(auto & friend_ele : friend_list){
//            auto find_iter = _chat_items_added.find(friend_ele->_uid);
//            if(find_iter != _chat_items_added.end()){
//                continue;
//            }
//            auto *chat_user_wid = new ChatUserWid();
//            auto user_info = std::make_shared<UserInfo>(friend_ele);
//            chat_user_wid->SetInfo(user_info);
//            QListWidgetItem *item = new QListWidgetItem;
//            //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
//            item->setSizeHint(chat_user_wid->sizeHint());
//            ui->chat_user_list->addItem(item);
//            ui->chat_user_list->setItemWidget(item, chat_user_wid);
//            _chat_items_added.insert(friend_ele->_uid, item);
//        }

//        //更新已加载条目
//        UserMgr::GetInstance()->UpdateChatLoadedCount();
//    }
//}

void ChatDialog::AddLBGroup(StateWidget* lb)
{
    _lb_list.push_back(lb);
}

void ChatDialog::slot_side_chat() {
    qDebug()<< "receive side chat clicked";
    ClearLabelState(ui->side_chat_lb);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    _state = ChatUIMode::ChatMode;
    ShowSearch(false);
}

void ChatDialog::slot_side_contact(){
    qDebug()<< "receive side contact clicked";
    ClearLabelState(ui->side_contact_lb);
    //设置
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
//    if(_last_widget == nullptr){
//        ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
//        _last_widget = ui->friend_apply_page;
//    }else{
//        ui->stackedWidget->setCurrentWidget(_last_widget);
//    }

    _state = ChatUIMode::ContactMode;
    ShowSearch(false);
}

void ChatDialog::slot_text_changed(const QString &str)
{
    //qDebug()<< "receive slot text changed str is " << str;
    if (!str.isEmpty()) {
        ShowSearch(true);
    }
}

bool ChatDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
       QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
       handleGlobalMousePress(mouseEvent);
    }
    return QDialog::eventFilter(watched, event);
}

void ChatDialog::handleGlobalMousePress(QMouseEvent *event)
{
    // 实现点击位置的判断和处理逻辑
    // 先判断是否处于搜索模式，如果不处于搜索模式则直接返回
    if( _mode != ChatUIMode::SearchMode){
        return;
    }

    // 将鼠标点击位置转换为搜索列表坐标系中的位置
    QPoint posInSearchList = ui->search_list->mapFromGlobal(event->globalPos());
    // 判断点击位置是否在聊天列表的范围内
    if (!ui->search_list->rect().contains(posInSearchList)) {
        // 如果不在聊天列表内，清空输入框
        ui->search_edit->clear();
        ShowSearch(false);
    }
}
