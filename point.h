#ifndef POINT_H
#define POINT_H

#include <QPointF>

class Point : public QPointF
{
public:
    Point();
    void setIndex(int index);
    int i();

private:
    int index;
};

#endif // POINT_H
