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

    Pair closestPair();
    void setAttr(int pointNumber, QPointF* pointf);

signals:
    void returnResult(Pair);
    void returnTime(double);

protected:
    void run();

private:
    int pointNumber;
    QPointF* pointf;
    double timeCost;
};

#endif // NAIVETHREAD_H
