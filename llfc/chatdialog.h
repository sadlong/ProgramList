#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "global.h"
#include <QRandomGenerator>
#include "chatuserwid.h"
#include "loadingdlg.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();
    void addChatUserList();

private:
    Ui::ChatDialog *ui;
    void ShowSearch(bool bsearch = false);
    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;
    void loadMoreChatUser();

private slots:
    void slot_loading_chat_user();
};

#endif // CHATDIALOG_H
