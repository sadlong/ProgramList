#ifndef FRMLIGHTBUTTON_H
#define FRMLIGHTBUTTON_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class frmLightButton; }
QT_END_NAMESPACE

class frmLightButton : public QWidget
{
    Q_OBJECT

public:
    explicit frmLightButton(QWidget *parent = nullptr);
    ~frmLightButton();

private:
    Ui::frmLightButton *ui;
    int type;   //三个按钮的状态类型 一共有三种

private slots:
    void initForm();
    void updateValue();
};
#endif // FRMLIGHTBUTTON_H
