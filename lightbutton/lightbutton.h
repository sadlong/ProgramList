#ifndef LIGHTBUTTON_H
#define LIGHTBUTTON_H

#include <QWidget>

class LightButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor alarmColor READ getAlarmColor WRITE setAlarmColor)
    Q_PROPERTY(QColor normalColor READ getNormalColor WRITE setNormalColor)

    Q_PROPERTY(QColor borderOutColorStart READ getBorderOutColorStart WRITE setBorderOutColorStart)
    Q_PROPERTY(QColor borderOutColorEnd READ getBorderOutColorEnd WRITE setBorderOutColorEnd)
    Q_PROPERTY(QColor borderInColorStart READ getBorderInColorStart WRITE setBorderInColorStart)
    Q_PROPERTY(QColor borderInColorEnd READ getBorderInColorEnd WRITE setBorderInColorEnd)
    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)

    Q_PROPERTY(bool canMove READ getCanMove WRITE setCanMove)
    Q_PROPERTY(bool showRect READ getShowRect WRITE setShowRect)
    Q_PROPERTY(bool showOverlay READ getShowOverlay WRITE setShowOverlay)
    Q_PROPERTY(QColor overlayColor READ getOverlayColor WRITE setOverlayColor)

public:
    explicit LightButton(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *);
    void drawBorderOut(QPainter *painter);
    void drawBorderIn(QPainter *painter);
    void drawBg(QPainter *painter);
    void drawText(QPainter *painter);
    void drawOverlay(QPainter *painter);

    //属性都是private
private:
    QString text;   //文本
    QColor textColor;   //文本颜色
    QColor alarmColor;  //报警颜色
    QColor normalColor; //正常颜色
    QColor borderOutColorStart; //外边框渐变开始颜色
    QColor borderOutColorEnd;   //外边框渐变结束颜色
    QColor borderInColorStart;  //内边框渐变开始颜色
    QColor borderInColorEnd;    //内边框渐变结束颜色
    QColor bgColor; //背景颜色
    bool showRect;  //是否显示成矩形
    bool canMove;   //是否能够移动
    bool showOverlay;   //是否显示遮罩层
    QColor overlayColor;    //遮罩层颜色
    bool pressed;   //鼠标是否按下
    QPoint lastPoint;   //鼠标最后按下坐标
    bool isAlarm;   //是否报警
    QTimer* timerAlarm; //定时器切换颜色

public:
    //默认尺寸和最小尺寸
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    //获取和设置文本
    QString getText() const;
    void setText(const QString &text);

    //获取和设置文本颜色
    QColor getTextColor() const;
    void setTextColor(const QColor &textColor);

    //获取和设置报警颜色
    QColor getAlarmColor() const;
    void setAlarmColor(const QColor &alarmColor);

    //获取和设置正常颜色
    QColor getNormalColor() const;
    void setNormalColor(const QColor &normalColor);

    //获取和设置外边框渐变颜色
    QColor getBorderOutColorStart() const;
    void setBorderOutColorStart(const QColor &borderOutColorStart);

    QColor getBorderOutColorEnd() const;
    void setBorderOutColorEnd(const QColor &borderOutColorEnd);

    //获取和设置里边框渐变颜色
    QColor getBorderInColorStart() const;
    void setBorderInColorStart(const QColor &borderInColorStart);

    QColor getBorderInColorEnd() const;
    void setBorderInColorEnd(const QColor &borderInColorEnd);

    //获取和设置背景色
    QColor getBgColor() const;
    void setBgColor(const QColor &bgColor);

    //获取和设置是否可移动
    bool getCanMove() const;
    void setCanMove(bool canMove);

    //获取和设置是否显示矩形
    bool getShowRect() const;
    void setShowRect(bool showRect);

    //获取和设置是否显示遮罩层
    bool getShowOverlay() const;
    void setShowOverlay(bool showOverlay);

    //获取和设置遮罩层颜色
    QColor getOverlayColor() const;
    void setOverlayColor(const QColor &overlayColor);


public slots:
    //设置为绿色
    void setGreen();
    //设置为红色
    void setRed();
    //设置为黄色
    void setYellow();
    //设置为黑色
    void setBlack();
    //设置为灰色
    void setGray();
    //设置为蓝色
    void setBlue();

    //设置为淡蓝色
    void setLightBlue();
    //设置为淡红色
    void setLightRed();
    //设置为淡绿色
    void setLightGreen();

    //设置报警闪烁
    void startAlarm();
    void stopAlarm();
    void alarm();

signals:
    void clicked();
};

#endif // LIGHTBUTTON_H
