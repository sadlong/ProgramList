#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QVector>

class Generate : public QObject
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    //任务函数
    void working(int num);

signals:
    void sendArray(QVector<int> num);

public slots:
};

class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void working(QVector<int> list);

signals:
    void finish(QVector<int> num);

public slots:
};

class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void working(QVector<int> list);

    void quickSort(QVector<int>& list, int l, int r);

signals:
    void finish(QVector<int> num);

public slots:
};

#endif // MYTHREAD_H
