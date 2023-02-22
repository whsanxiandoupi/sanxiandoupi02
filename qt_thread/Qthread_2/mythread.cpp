#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>
#include <QRandomGenerator>

Generate::Generate(QObject *parent)
    : QObject{parent}
{

}

void Generate::working(int num)
{
    qDebug()<<"生成随机数的线程地址: "<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i=0;i<num;++i)
    {
        list.push_back(qrand()%100000);
    }
    int milsec=time.elapsed();
    qDebug()<<"生成"<<num<<"个随机数总共用时: "<<milsec<<"毫秒";
    emit sendArray(list);

}

BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}

void BubbleSort::working(QVector<int> list)
{
    qDebug()<<"冒泡排序的线程地址: "<<QThread::currentThread();
//    QVector<int> list;
    QElapsedTimer time;
    time.start();
    int temp;
    for(int i=0;i<list.size();++i){
        for(int j=0;j<list.size()-i-1;++j){
            if(list[j]>list[j+1]){
                temp=list[j];
                list[j]=list[j+1];
                list[j+1]=temp;
            }
        }
    }

    int milsec=time.elapsed();
    qDebug()<<"冒泡排序总共用时: "<<milsec<<"毫秒";
    emit finish(list);
}

QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}
void QuickSort::working(QVector<int> list)
{
    qDebug()<<"快速排序的线程地址: "<<QThread::currentThread();
//    QVector<int> list;
    QElapsedTimer time;
    time.start();
    quickSort(list,0,list.size()-1);

    int milsec=time.elapsed();
    qDebug()<<"快速排序总共用时: "<<milsec<<"毫秒";
    emit finish(list);
}

void QuickSort::quickSort(QVector<int> &list, int l, int r)
{
    if(l<r){
        int i=l,j=r;
        // 拿出第一个元素，保存到x中，第一个位置为一个坑
        int x=list[l];
        while(i<j)
        {
            // 从右向左找小于x的数
            while(i<j && list[j]>=x)
            {
                // 左移，直到遇到小于等于x的数
                j--;
            }
            if(i<j){
                //将右侧找到小于x的元素放入左侧坑中，右侧出现一个坑
                //左侧元素索引后移
                list[i++]=list[j];
            }

            // 从左向右找大于x的数
            while(i<j && list[i]<x)
            {
                //右移，直到遇到大于x的数
                i++;
            }
            if(i<j){
                list[j--]=list[i];
            }
        }
        list[i]=x;
        quickSort(list,l,i-1);
        quickSort(list,i+1,r);
    }
}


