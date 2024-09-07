#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

#include "udpservercomm.h"
#include <QDebug>

static int iCountMsg;

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

private:
    Ui::MainDialog *ui;

public:
    UDPServerComm* udpservercomm;

    void InitUDPSocketFunc();
public slots:
    void ReadDatagramFunc();

};
#endif // MAINDIALOG_H
