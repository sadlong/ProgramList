#include "battery.h"
#include "qpainter.h"
#include "qtimer.h"

battery::battery(QWidget *parent) : QWidget(parent)
{
    borderWidth = 5;
    borderRadius = 8;
    borderColorStart = QColor(100, 100, 100);
    borderColorEnd = QColor(80, 80, 80);

    value = 0;
    minValue = 0;
    maxValue = 100;
    currentValue = 0;
    alarmValue = 30;
    alarmColorStart = QColor(250, 118, 113);
    alarmColorEnd = QColor(204, 38, 38);
    normalColorStart = QColor(50, 205, 51);
    normalColorEnd = QColor(60, 179, 133);
    bgRadius = 5;
    isForward = false;
    animation = true;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    animationStep = 5;

    headRadius = 3;
}

battery::~battery() {

}

void battery::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制边框
    drawBorder(&painter);   //这里是取地址
    drawBg(&painter);
    drawHead(&painter);
}

//画边框
void battery::drawBorder(QPainter* painter) {
    painter->save();

    double headWidth = width() /15;
    double batteryWidth = width() - headWidth;

    //绘制电池边框
    QPointF topLeft(borderWidth, borderWidth);  //确定左上角
    QPointF bottomRight(batteryWidth, height()-borderWidth);    //确定右下角
    batteryRect = QRectF(topLeft, bottomRight);

    painter->setPen(QPen(borderColorStart, borderWidth));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(batteryRect, borderRadius, borderRadius);

    painter->restore();

}

//画背景颜色条 暂时没有显示出颜色 个人觉得先画电池头比较好
void battery::drawBg(QPainter* painter) {
    if(value <= minValue) return;
    painter->save();

    //渐变色 纵向
    QLinearGradient batteryGradient(QPointF(0, 0), QPointF(0, height()));
    if(currentValue <= alarmValue) {
        batteryGradient.setColorAt(0.0, alarmColorStart);
        batteryGradient.setColorAt(1.0, alarmColorEnd);
    } else {
        batteryGradient.setColorAt(0.0, normalColorStart);
        batteryGradient.setColorAt(1.0, normalColorEnd);
    }

    int margin = qMin(width(), height()) / 20;
    double unit = (batteryRect.width() - (margin * 2)) / (maxValue - minValue);
    double width = currentValue * unit;
    QPointF topLeft(batteryRect.topLeft().x() + margin, batteryRect.topLeft().y() + margin);
    QPointF bottomRight(width + margin + borderWidth, batteryRect.bottomRight().y() - margin);
    QRectF rect(topLeft, bottomRight);

    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    painter->drawRoundedRect(rect, bgRadius, bgRadius);

    painter->restore();
}

//画电池头部
void battery::drawHead(QPainter* painter) {
    painter->save();

    QPointF headRectTopLeft(batteryRect.topRight().x(), height()/3);
    QPointF headRectBottomRight(width(), height()-height()/3);
    QRectF headRect(headRectTopLeft, headRectBottomRight);

    QLinearGradient headRectGradient(headRect.topLeft(), headRect.bottomLeft());
    headRectGradient.setColorAt(0.0, borderColorStart);
    headRectGradient.setColorAt(1.0, borderColorEnd);

    painter->setPen(Qt::NoPen);
    painter->setBrush(headRectGradient);
    painter->drawRoundedRect(headRect, headRadius, headRadius);

    painter->restore();
}

QColor battery::getBorderColorStart() const{
    return this->borderColorStart;
}

void battery::setBorderColorStart(const QColor& borderColorStart) {
    if(this->borderColorStart != borderColorStart) {
        this->borderColorStart = borderColorStart;
        this->update();
    }
}

QColor battery::getBorderColorEnd() const{
    return this->borderColorEnd;
}

void battery::setBorderColorEnd(const QColor& borderColorEnd) {
    if(this->borderColorEnd != borderColorEnd) {
        this->borderColorEnd = borderColorEnd;
        this->update();
    }
}

QColor battery::getAlarmColorStart() const
{
    return this->alarmColorStart;
}

void battery::setAlarmColorStart(const QColor &alarmColorStart)
{
    if (this->alarmColorStart != alarmColorStart) {
        this->alarmColorStart = alarmColorStart;
        this->update();
    }
}

QColor battery::getAlarmColorEnd() const
{
    return this->alarmColorEnd;
}

void battery::setAlarmColorEnd(const QColor &alarmColorEnd)
{
    if (this->alarmColorEnd != alarmColorEnd) {
        this->alarmColorEnd = alarmColorEnd;
        this->update();
    }
}

QColor battery::getNormalColorStart() const
{
    return this->normalColorStart;
}

void battery::setNormalColorStart(const QColor &normalColorStart)
{
    if (this->normalColorStart != normalColorStart) {
        this->normalColorStart = normalColorStart;
        this->update();
    }
}

QColor battery::getNormalColorEnd() const
{
    return this->normalColorEnd;
}

void battery::setNormalColorEnd(const QColor &normalColorEnd)
{
    if (this->normalColorEnd != normalColorEnd) {
        this->normalColorEnd = normalColorEnd;
        this->update();
    }
}

double battery::getValue() const {
    return this->value;
}

void battery::setValue(double value) {
    //和当前值一致则无需处理
    if(value == this->value) return;

    //小于最小值则取最小 大于最大值则取最大
    if(value < minValue) value = minValue;
    else if(value > maxValue) value = maxValue;

    if(value > currentValue) isForward = false; //向右
    else if(value < currentValue) isForward = true; //向左
    else {
        this->value = value;
        this->update(); //更新
        return;
    }

    this->value = value;
    Q_EMIT valuechanged(value); //Qt信号发射函数 value发生变化 连接到valuechanged的槽函数都会被调用
    if(animation) {
        timer->stop();
        timer->start();
    }
}

void battery::setValue(int value) {
    setValue((double)value);
}

void battery::updateValue() {
    if(isForward) {
        currentValue -= animationStep;
        if(currentValue <= value) {
            currentValue = value;
            timer->stop();
        }
    } else {
        currentValue += animationStep;
        if(currentValue >= value) {
            currentValue = value;
            timer->stop();
        }
    }

    this->update();
}

double battery::getAlarmValue() const {
    return this->alarmValue;
}

void battery::setAlarmValue(double alarmValue) {
    if(this->alarmValue != alarmValue) {
        this->alarmValue = alarmValue;
        this->update();
    }
}

void battery::setAlarmValue(int alarmValue) {
    setAlarmValue((double)alarmValue);
}

void battery::setRange(double minValue, double maxValue) {
    //如果最小值大于等于最大值则不设置
    if(minValue >= maxValue) return;

    this->minValue = minValue;
    this->maxValue = maxValue;

    //目标值不在范围内，则重新设置目标值
    if(value < minValue) {
        setValue(minValue);
    } else if(value > maxValue) {
        setValue(maxValue);
    }

    this->update();
}

double battery::getMinValue() const
{
    return this->minValue;
}

void battery::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

double battery::getMaxValue() const
{
    return this->maxValue;
}

void battery::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void battery::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}


