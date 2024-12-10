#include "mythread.h"
#include <QElapsedTimer>    //用于计算执行用时
#include <QDebug>
#include <QThread>

Generate::Generate(QObject *parent) : QObject(parent)
{

}

void Generate::working(int num)
{
    qDebug() << "生成随机数线程的地址为：" << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i = 0; i < num; i++) {
        list.push_back(qrand()%100000);
    }
    int deltaTime = time.elapsed();
    qDebug() << "生成" << num << "个随机数总共用时：" << deltaTime << "毫秒";
    emit sendArray(list);
}

BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}

void BubbleSort::working(QVector<int> list)
{
    qDebug() << "冒泡排序数线程的地址为：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();

    //冒泡排序逻辑
    for(int i = 0; i < list.size(); i++) {
        for(int j = 0; j < list.size()-i-1; j++) {
            if(list[j] > list[j+1]) {
                int tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
            }
        }
    }

    int deltaTime = time.elapsed();
    qDebug() << "冒泡排序总共用时：" << deltaTime << "毫秒";
    emit finish(list);
}

QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}

void QuickSort::quickSort(QVector<int>& s, int l, int r)
{
    if(l < r) {
        int i = l, j = r;
        int x = s[l];
        while(i < j) {
            while(i < j && s[j] >= x) j--;
            if(i < j) s[i++] = s[j];

            while(i < j && s[i] < x) i++;
            if(i < j) s[j--] = s[i];
        }

        s[i] = x;
        quickSort(s, l, i-1);
        quickSort(s, i+1, l);
    }
}

void QuickSort::working(QVector<int> list)
{
    qDebug() << "快速排序数线程的地址为：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quickSort(list, 0, list.size()-1);
    int deltaTime = time.elapsed();
    qDebug() << "快速排序总共用时：" << deltaTime << "毫秒";
    emit finish(list);
}
