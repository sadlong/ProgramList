#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>

class Generate : public QThread
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void recvNum(int num);

protected:
    void run() override;

signals:
    void sendArray(QVector<int> num);


private:
    int m_num;

public slots:
};

class BubbleSort : public QThread
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void recvArray(QVector<int> list);

protected:
    void run() override;

signals:
    void finish(QVector<int> num);


private:
    QVector<int> m_list;

public slots:
};

class QuickSort : public QThread
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void recvArray(QVector<int> list);

protected:
    void run() override;

    void quickSort(QVector<int>& list, int l, int r);

signals:
    void finish(QVector<int> num);


private:
    QVector<int> m_list;

public slots:
};

#endif // MYTHREAD_H
