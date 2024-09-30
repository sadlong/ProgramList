#include "lightbutton.h"
#include "qtimer.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qdebug.h"
#include "qevent.h"

LightButton::LightButton(QWidget *parent) : QWidget(parent)
{
    text = "";  //输入啥就会显示啥 调整字体的函数font.setPixelSize()
    textColor = QColor(255, 255, 255);
    alarmColor = QColor(255, 107, 107);
    normalColor = QColor(10, 10, 10);
    borderOutColorStart = QColor(255, 255, 255);
    borderOutColorEnd = QColor(166, 166, 166);
    borderInColorStart = QColor(166, 166, 166);
    borderInColorEnd = QColor(255, 255, 255);
    bgColor = QColor(100, 184, 255);
    showRect = false;
    showOverlay = true;
    overlayColor = QColor(255, 255, 255);
    canMove = true;
    pressed = false;
    this->installEventFilter(this);
    isAlarm = false;
    timerAlarm = new QTimer(this);
    connect(timerAlarm, SIGNAL(timeout()), this, SLOT(alarm()));
    timerAlarm->setInterval(500);
}

//这个函数必须写 不写不显示控件 实现一个可拖动的按钮 watched 是被监视的对象，event 是接收到的事件
bool LightButton::eventFilter(QObject *watched, QEvent *event) {
    int type = event->type();   //获取事件的类型，并将其存储在 type 变量中
    QMouseEvent* mouseEvent = (QMouseEvent*) event;
    //检查事件类型是否为鼠标按下（MouseButtonPress）
    if(type == QEvent::MouseButtonPress) {
        //检查鼠标点击的位置是否在按钮的矩形区域内 判断鼠标是否是左键点击
        if(this->rect().contains(mouseEvent->pos()) && (mouseEvent->button() == Qt::LeftButton)) {
            lastPoint = mouseEvent->pos();
            pressed = true;
        }
    } else if(type == QEvent::MouseMove && pressed) { //检查事件类型是否为鼠标移动（MouseMove），并且按钮当前是被按下状态（pressed）
        //如果允许移动（canMove 为 true），计算鼠标当前位置与上一次记录位置的偏移量 dx 和 dy
        if(canMove) {
            int dx = mouseEvent->pos().x()-lastPoint.x();
            int dy = mouseEvent->pos().y()-lastPoint.y();
            //使用 this->move() 方法，将按钮移动到新的位置，实现拖动效果
            this->move(this->x()+dx, this->y()+dy);
        }
    } else if(type == QEvent::MouseButtonRelease && pressed) {//检查事件类型是否为鼠标释放（MouseButtonRelease），并且按钮当前是被按下状态
        pressed = false;
        //触发 clicked() 信号，表示按钮被点击完成，可以连接到其他槽函数进行处理
        Q_EMIT clicked();
    }

    //调用基类的 eventFilter 方法以确保其他事件仍然得到处理，返回该值以指示事件是否被处理
    return QWidget::eventFilter(watched, event);
}

void LightButton::paintEvent(QPaintEvent *) {
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height); //qt中求min的函数
    //qDebug() << this->pressed;
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if(showRect) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(bgColor);
        painter.drawRoundedRect(this->rect(), 5, 5);

        //绘制文字
        if(!text.isEmpty()) {
            QFont font;
            font.setPixelSize(side - 200);
            painter.setFont(font);
            painter.setPen(textColor);
            painter.drawText(this->rect(), Qt::AlignCenter, text);

        }
    } else {
        painter.translate(width/2, height/2);
        painter.scale(side/200.0, side/200.0);

        //绘制外边框
        drawBorderOut(&painter);
        drawBorderIn(&painter);
        drawBg(&painter);
        drawText(&painter);
        drawOverlay(&painter);
    }

}

void LightButton::drawBorderOut(QPainter *painter) {
    int radius = 100;   //设置半径
    painter->save();
    painter->setPen(Qt::NoPen);
    //创建一个线性渐变对象 borderGradient，其起始点为 (0, -radius)，终止点为 (0, radius)。这意味着渐变将沿着 Y 轴垂直方向进行
    QLinearGradient borderGradient(0, -radius, 0, radius);
    //在渐变的起始位置（Y=−radius）设置开始颜色
    borderGradient.setColorAt(0, borderOutColorStart);
    //在渐变的结束位置（Y=radius）设置结束颜色
    borderGradient.setColorAt(1, borderOutColorEnd);
    painter->setBrush(borderGradient);
    //使用 drawEllipse 方法绘制一个圆形。圆心在 (0, 0)，宽和高均为 radius * 2（即直径为 200），因此绘制的圆形的边界从 (-radius, -radius) 开始，覆盖到 (radius, radius)
    painter->drawEllipse(-radius, -radius, radius*2, radius*2); //画圆形
    painter->restore();
}

//和上面一个函数基本一样 就是半径不同而已 但是重叠之后的效果真的恍然大悟！
void LightButton::drawBorderIn(QPainter *painter) {
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderInColorStart);
    borderGradient.setColorAt(1, borderInColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius*2, radius*2);
    painter->restore();
}

void LightButton::drawBg(QPainter *painter) {
    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius*2, radius*2);
    painter->restore();
}

void LightButton::drawText(QPainter *painter) {
    if(text.isEmpty()) return;
    int radius = 100;
    painter->save();
    QFont font;
    font.setPixelSize(100);
    painter->setPen(textColor);
    //定义绘制区域
    QRect rect(-radius, -radius, radius*2, radius*2);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

void LightButton::drawOverlay(QPainter *painter) {
    if(!showOverlay) return;
    int radius = 80;
    painter->save();

    painter->setPen(Qt::NoPen);
    QPainterPath smallCircle, bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius*2, radius*2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius+140, radius*2, radius*2);

    //高光的形状为小圆抠掉大圆的部分
    QPainterPath highlight = smallCircle-bigCircle;
    QLinearGradient linearGradient(0, -radius/2, 0, 0);
    overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, overlayColor);
    overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

QSize LightButton::sizeHint() const
{
    return QSize(100, 100);
}

QSize LightButton::minimumSizeHint() const
{
    return QSize(10, 10);
}

QString LightButton::getText() const
{
    return this->text;
}

void LightButton::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        this->update();
    }
}

QColor LightButton::getTextColor() const
{
    return this->textColor;
}

void LightButton::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

QColor LightButton::getAlarmColor() const
{
    return this->alarmColor;
}

void LightButton::setAlarmColor(const QColor &alarmColor)
{
    if (this->alarmColor != alarmColor) {
        this->alarmColor = alarmColor;
        this->update();
    }
}

QColor LightButton::getNormalColor() const
{
    return this->normalColor;
}

void LightButton::setNormalColor(const QColor &normalColor)
{
    if (this->normalColor != normalColor) {
        this->normalColor = normalColor;
        this->update();
    }
}

QColor LightButton::getBorderOutColorStart() const
{
    return this->borderOutColorStart;
}

void LightButton::setBorderOutColorStart(const QColor &borderOutColorStart)
{
    if (this->borderOutColorStart != borderOutColorStart) {
        this->borderOutColorStart = borderOutColorStart;
        this->update();
    }
}

QColor LightButton::getBorderOutColorEnd() const
{
    return this->borderOutColorEnd;
}

void LightButton::setBorderOutColorEnd(const QColor &borderOutColorEnd)
{
    if (this->borderOutColorEnd != borderOutColorEnd) {
        this->borderOutColorEnd = borderOutColorEnd;
        this->update();
    }
}

QColor LightButton::getBorderInColorStart() const
{
    return this->borderInColorStart;
}

void LightButton::setBorderInColorStart(const QColor &borderInColorStart)
{
    if (this->borderInColorStart != borderInColorStart) {
        this->borderInColorStart = borderInColorStart;
        this->update();
    }
}

QColor LightButton::getBorderInColorEnd() const
{
    return this->borderInColorEnd;
}

void LightButton::setBorderInColorEnd(const QColor &borderInColorEnd)
{
    if (this->borderInColorEnd != borderInColorEnd) {
        this->borderInColorEnd = borderInColorEnd;
        this->update();
    }
}

QColor LightButton::getBgColor() const
{
    return this->bgColor;
}

void LightButton::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

bool LightButton::getCanMove() const
{
    return this->canMove;
}

void LightButton::setCanMove(bool canMove)
{
    if (this->canMove != canMove) {
        this->canMove = canMove;
        this->update();
    }
}

bool LightButton::getShowRect() const
{
    return this->showRect;
}

void LightButton::setShowRect(bool showRect)
{
    if (this->showRect != showRect) {
        this->showRect = showRect;
        this->update();
    }
}

bool LightButton::getShowOverlay() const
{
    return this->showOverlay;
}

void LightButton::setShowOverlay(bool showOverlay)
{
    if (this->showOverlay != showOverlay) {
        this->showOverlay = showOverlay;
        this->update();
    }
}

QColor LightButton::getOverlayColor() const
{
    return this->overlayColor;
}

void LightButton::setOverlayColor(const QColor &overlayColor)
{
    if (this->overlayColor != overlayColor) {
        this->overlayColor = overlayColor;
        this->update();
    }
}

void LightButton::setGreen()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(0, 166, 0));
}

void LightButton::setRed()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(255, 0, 0));
}

void LightButton::setYellow()
{
    textColor = QColor(25, 50, 7);
    setBgColor(QColor(238, 238, 0));
}

void LightButton::setBlack()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(10, 10, 10));
}

void LightButton::setGray()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(129, 129, 129));
}

void LightButton::setBlue()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(0, 0, 166));
}

void LightButton::setLightBlue()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(100, 184, 255));
}

void LightButton::setLightRed()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(255, 107, 107));
}

void LightButton::setLightGreen()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(24, 189, 155));
}

void LightButton::startAlarm()
{
    if (!timerAlarm->isActive()) {
        timerAlarm->start();
    }
}

void LightButton::stopAlarm()
{
    if (timerAlarm->isActive()) {
        timerAlarm->stop();
    }
}

void LightButton::alarm() {
    if(isAlarm) {
        textColor = QColor(255, 255, 255);
        bgColor = normalColor;
    } else {
        textColor = QColor(255, 255, 255);
        bgColor = alarmColor;
    }

    this->update(); //更新界面
    isAlarm = !isAlarm; //取反操作
}
