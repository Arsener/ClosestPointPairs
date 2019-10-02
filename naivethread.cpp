#include "naivethread.h"

NaiveThread::NaiveThread()
{

}

NaiveThread::~NaiveThread()
{
    delete [] pointf;
}

// 寻找最近点对
Pair NaiveThread::closestPair(){
    int a = -1, b = -1;
    double minDis = 999999999;

    // 两重循环
    for(int i = 0; i < pointNumber - 1; i++){
        for(int j = i + 1; j < pointNumber; j++){
            double dis = sqrt(pow((pointf[i].x() - pointf[j].x()), 2) + pow((pointf[i].y() - pointf[j].y()), 2));
            if (dis < minDis){
                a = i;
                b = j;
                minDis = dis;
            }
        }
    }

    return Pair(a, b, minDis);
}


void NaiveThread::setAttr(int pointNumber, QPointF* pointf){
    this->pointNumber = pointNumber;
    this->pointf = pointf;
}

void NaiveThread::run(){
    // 计算时间
    auto start = system_clock::now();
    Pair p = closestPair();
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    timeCost = double(duration.count()) * microseconds::period::num / microseconds::period::den;

    // 将最近点对和算法所用时间发射出去
    emit returnResult(p);
    emit returnTime(timeCost);
}
