#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>

class battery : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor borderColorStart READ getBorderColorStart WRITE setBorderColorStart)
    Q_PROPERTY(QColor borderColorEnd READ getBorderColorEnd WRITE setBorderColorEnd)

    Q_PROPERTY(QColor alarmColorStart READ getAlarmColorStart WRITE setAlarmColorStart)
    Q_PROPERTY(QColor alarmColorEnd READ getAlarmColorEnd WRITE setAlarmColorEnd)

    Q_PROPERTY(QColor normalColorStart READ getNormalColorStart WRITE setNormalColorStart)
    Q_PROPERTY(QColor normalColorEnd READ getNormalColorEnd WRITE setNormalColorEnd)

    Q_PROPERTY(double value READ getValue WRITE setValue)

    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)

public:
    explicit battery(QWidget *parent = nullptr);
    ~battery();

protected:
    void paintEvent(QPaintEvent *);
    void drawBorder(QPainter* painter);
    void drawBg(QPainter* painter);
    void drawHead(QPainter* painter);


private:

    //画边框
    int borderWidth; //边框粗细
    int borderRadius;    //边框圆角角度
    QRectF batteryRect;  //电池主体区域
    QColor borderColorStart;
    QColor borderColorEnd;

    //画背景
    double minValue;    //最小值
    double value;   //目标电量
    double maxValue;
    double currentValue;
    double alarmValue;
    QColor alarmColorStart;
    QColor alarmColorEnd;
    QColor normalColorStart;
    QColor normalColorEnd;
    int bgRadius;
    bool isForward;
    bool animation;
    QTimer* timer;
    double animationStep;

    //画电池头
    double headRadius;

public:
    QColor getBorderColorStart() const;
    void setBorderColorStart(const QColor& borderColorStart);
    QColor getBorderColorEnd() const;
    void setBorderColorEnd(const QColor& borderColorEnd);

    //获取和设置电池电量报警时的渐变颜色
    QColor getAlarmColorStart() const;
    void setAlarmColorStart(const QColor &alarmColorStart);
    QColor getAlarmColorEnd() const;
    void setAlarmColorEnd(const QColor &alarmColorEnd);

    //获取和设置电池电量正常时的渐变颜色
    QColor getNormalColorStart() const;
    void setNormalColorStart(const QColor &normalColorStart);
    QColor getNormalColorEnd() const;
    void setNormalColorEnd(const QColor &normalColorEnd);

    //获取和设置电池电量值
    double getValue() const;
    void setValue(double value);

    double getAlarmValue() const;
    void setAlarmValue(double alarmValue);

    //获取和设置最小值
    double getMinValue() const;
    void setMinValue(double minValue);

    //获取和设置最大值
    double getMaxValue() const;
    void setMaxValue(double maxValue);

    //设置范围值
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

private slots:
    void updateValue();
    void setAlarmValue(int alarmValue);

public slots:
    void setValue(int value);

signals:
    void valuechanged(double value);
};

#endif // BATTERY_H
