#include "point.h"

Point::Point()
{

}

//Point::Point(int index, double x, double y)
//{
//    this->index = index;
//    this->setX(x);
//    this->setY(y);
//}

void Point::setIndex(int index){
    this->index = index;
}

int Point::i(){
    return this->index;
}
