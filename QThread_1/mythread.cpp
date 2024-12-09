#include "mythread.h"
#include <QElapsedTimer>    //用于计算执行用时
#include <QDebug>

Generate::Generate(QObject *parent) : QThread(parent)
{

}

void Generate::recvNum(int num)
{
    m_num = num;
}

void Generate::run()
{
    qDebug() << "生成随机数线程的地址为：" << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i = 0; i < m_num; i++) {
        list.push_back(qrand()%100000);
    }
    int deltaTime = time.elapsed();
    qDebug() << "生成" << m_num << "个随机数总共用时：" << deltaTime << "毫秒";
    emit sendArray(list);
}

BubbleSort::BubbleSort(QObject *parent) : QThread(parent)
{

}

void BubbleSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void BubbleSort::run()
{
    qDebug() << "冒泡排序数线程的地址为：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();

    //冒泡排序逻辑
    for(int i = 0; i < m_list.size(); i++) {
        for(int j = 0; j < m_list.size()-i-1; j++) {
            if(m_list[j] > m_list[j+1]) {
                int tmp = m_list[j];
                m_list[j] = m_list[j+1];
                m_list[j+1] = tmp;
            }
        }
    }

    int deltaTime = time.elapsed();
    qDebug() << "冒泡排序总共用时：" << deltaTime << "毫秒";
    emit finish(m_list);
}

QuickSort::QuickSort(QObject *parent) : QThread(parent)
{

}

void QuickSort::recvArray(QVector<int> list)
{
    m_list = list;
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

void QuickSort::run()
{
    qDebug() << "快速排序数线程的地址为：" << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quickSort(m_list, 0, m_list.size()-1);
    int deltaTime = time.elapsed();
    qDebug() << "快速排序总共用时：" << deltaTime << "毫秒";
    emit finish(m_list);
}
