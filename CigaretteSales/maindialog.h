#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

#include <QtCharts>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

    //QChart* pChart; //管理数据指针
    QChartView* pChartView; //显示图表指针
    QDialog* pContainer;    //对话框指针

private:
    Ui::MainDialog *ui;
};
#endif // MAINDIALOG_H
