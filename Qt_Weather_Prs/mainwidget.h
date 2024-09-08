#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include <QTimer>
#include <QTime>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

private:
    QNetworkAccessManager* qNwkHttp;
    QTimer qTimer;  //定时器
public slots:
    void OnTimerOutFunc();

public:
    //获取当天的天气预报数据
    void Get_CurrentWeather(QNetworkReply* qReply);

    //获取三天内天气预报数据
    void Get_ThreeWeather(QNetworkReply* qReply);
private slots:
    void on_pushButton_GetData_clicked();
};
#endif // MAINWIDGET_H
