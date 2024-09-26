#ifndef FRMBATTERY_H
#define FRMBATTERY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class frmBattery; }
QT_END_NAMESPACE

class frmBattery : public QWidget
{
    Q_OBJECT

public:
    explicit frmBattery(QWidget *parent = nullptr); //提高可读性和安全性 防止隐式转换，只有明确的构造函数才能调用
    ~frmBattery();

private:
    Ui::frmBattery *ui;

private slots:
    void initForm();
};
#endif // FRMBATTERY_H
