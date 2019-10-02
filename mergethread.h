#ifndef MERGETHREAD_H
#define MERGETHREAD_H

#include <QThread>
#include <QPointF>
#include <cmath>
#include <chrono>
#include "pair.h"
#include "point.h"

using namespace std;
using namespace chrono;

class MergeThread : public QThread
{
    Q_OBJECT

public:
    MergeThread();
    ~MergeThread();

    Pair closestPair(QPointF *pointX, Point *pointY, int lt, int rt);  // 寻找最近点对
    void setAttr(int pointNumber, QPointF* pointX);

signals:
    void returnResult(Pair);  // 发送最近点对
    void returnTime(double);  // 发送算法所用时间

protected:
    void run();

private:
    int pointNumber;  // 点的数量
    QPointF* pointX;  // 点数组
    double timeCost;  // 算法所用时间

    void mergeSortX(QPointF *p, int lt, int rt);  // 使用归并排序，将点的数组按照x坐标由小到大排序
    void mergeSortY(Point *p, int lt, int rt);  // 使用归并排序，将点的数组按照y坐标由小到大排序
    double getDis(QPointF a, QPointF b);  // 计算两点间距

};

#endif // MERGETHREAD_H
