#ifndef POINT_H
#define POINT_H

#include <QPointF>

class Point : public QPointF
{
public:
    Point();
//    Point(int index, double x, double y);
    void setIndex(int index);
    int i();

private:
    int index;
};

#endif // POINT_H
