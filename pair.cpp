#include "pair.h"


Pair::Pair()
{
    qRegisterMetaType<Pair>("Pair");
}

Pair::Pair(int p1, int p2, double distance)
{
    this->p1 = p1;
    this->p2 = p2;
    this->distance = distance;

    qRegisterMetaType<Pair>("Pair");
}

int Pair::getP1(){
    return this->p1;
}

int Pair::getP2(){
    return this->p2;
}

double Pair::getDis(){
    return this->distance;
}
