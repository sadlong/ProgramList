#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private slots:
    void on_send_btn_clicked();

private:
    Ui::ChatPage *ui;
};

#endif // CHATPAGE_H
