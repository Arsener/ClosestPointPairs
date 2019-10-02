#ifndef NAIVETHREAD_H
#define NAIVETHREAD_H

#include <QThread>
#include <QPointF>
#include <cmath>
#include <chrono>
#include "pair.h"

using namespace std;
using namespace chrono;


class NaiveThread : public QThread
{
    Q_OBJECT

public:
    NaiveThread();
    ~NaiveThread();

    Pair closestPair();  // 寻找最近点对
    void setAttr(int pointNumber, QPointF* pointf);

signals:
    void returnResult(Pair);  // 发送最近点对
    void returnTime(double);  // 发送算法所用时间

protected:
    void run();

private:
    int pointNumber;  // 点的数量
    QPointF* pointf;  // 点数组
    double timeCost;  // 算法所用时间
};

#endif // NAIVETHREAD_H
