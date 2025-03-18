#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "global.h"
#include <QRandomGenerator>
#include "chatuserwid.h"
#include "loadingdlg.h"
#include "statewidget.h"

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
    void ClearLabelState(StateWidget *lb);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    void handleGlobalMousePress(QMouseEvent *event);

private:
    Ui::ChatDialog *ui;
    void ShowSearch(bool bsearch = false);
    void AddLBGroup(StateWidget* lb);
    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;
    void loadMoreChatUser();
    QList<StateWidget*> _lb_list;
    QWidget* _last_widget;

private slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
    void slot_text_changed(const QString &str);
};

#endif // CHATDIALOG_H
