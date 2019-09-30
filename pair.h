#ifndef PAIR_H
#define PAIR_H

#include <QMetaType>

class Pair
{
public:
    Pair();
    Pair(int p1, int p2, double distance);
    int getP1();
    int getP2();
    double getDis();

private:
    int p1, p2;
    double distance;
};

#endif // PAIR_H
