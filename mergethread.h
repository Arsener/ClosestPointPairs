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

    Pair closestPair(QPointF *pointX, Point *pointY, int lt, int rt);
    void setAttr(int pointNumber, QPointF* pointX);

signals:
    void returnResult(Pair);
    void returnTime(double);

protected:
    void run();

private:
    int pointNumber;
    QPointF* pointX;
    double timeCost;

    void mergeSortX(QPointF *p, int lt, int rt);
    void mergeSortY(Point *p, int lt, int rt);
    double getDis(QPointF a, QPointF b);

};

#endif // MERGETHREAD_H
