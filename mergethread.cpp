#include "mergethread.h"

MergeThread::MergeThread()
{

}

MergeThread::~MergeThread()
{
    delete [] pointX;
}

// 使用归并排序，将点的数组按照x坐标由小到大排序
void MergeThread::mergeSortX(QPointF *p, int lt, int rt){
    if (lt >= rt) return;

    // 一分为二，递归调用
    int mid = (lt + rt) / 2;
    mergeSortX(p, lt, mid);
    mergeSortX(p, mid + 1, rt);

    QPointF *tmp = new QPointF[rt - lt + 1];
    int i = lt, j = mid + 1, k = 0;
    while (i <= mid && j <= rt) {
        if (p[i].x() < p[j].x()) {
            tmp[k++] = p[i++];
        } else if (p[i].x() > p[j].x()) {
            tmp[k++] = p[j++];
        } else if (p[i].x() == p[j].x() && p[i].y() < p[j].y()) {
            tmp[k++] = p[i++];
        } else {
            tmp[k++] = p[j++];
        }
    }

    if (i > mid) {
        while (j <= rt) tmp[k++] = p[j++];
    } else {
        while (i <= mid) tmp[k++] = p[i++];
    }

    for (int i = lt; i <= rt; i++){
        p[i] = tmp[i - lt];
    }

    delete [] tmp;
}

// 使用归并排序，将点的数组按照y坐标由小到大排序
void MergeThread::mergeSortY(Point *p, int lt, int rt){
    if (lt >= rt) return;

    // 一分为二，递归调用
    int mid = (lt + rt) / 2;
    mergeSortY(p, lt, mid);
    mergeSortY(p, mid + 1, rt);

    Point *tmp = new Point[rt - lt + 1];
    int i = lt, j = mid + 1, k = 0;
    while (i <= mid && j <= rt) {
        if (p[i].y() < p[j].y()) {
            tmp[k++] = p[i++];
        } else if (p[i].y() > p[j].y()) {
            tmp[k++] = p[j++];
        } else if (p[i].y() == p[j].y() && p[i].x() < p[j].x()) {
            tmp[k++] = p[i++];
        } else {
            tmp[k++] = p[j++];
        }
    }

    if (i > mid) {
        while (j <= rt) tmp[k++] = p[j++];
    } else {
        while (i <= mid) tmp[k++] = p[i++];
    }

    for (int i = lt; i <= rt; i++){
        p[i] = tmp[i - lt];
    }

    delete [] tmp;
}


// 最近点对
Pair MergeThread::closestPair(QPointF *pointX, Point *pointY, int lt, int rt){
    // 只剩下两个点
    if (rt - lt == 1){
        return Pair(lt, rt, getDis(pointX[lt], pointX[rt]));
    }

    // 只剩下三个点
    if(rt - lt == 2){
        double dis1 = getDis(pointX[lt], pointX[lt + 1]);
        double dis2 = getDis(pointX[lt], pointX[rt]);
        double dis3 = getDis(pointX[lt + 1], pointX[rt]);

        if (dis1 <= dis2 && dis1 <= dis3) return Pair(lt, lt + 1, dis1);
        if (dis2 <= dis1 && dis2 <= dis3) return Pair(lt, rt, dis2);
        if (dis3 <= dis2 && dis3 <= dis1) return Pair(lt + 1, rt, dis3);
    }

    //多于三个点，先将所有点一分为二
    int mid = (lt + rt) / 2;
    // 将pointY按照划分情况进行划分
    Point *yLeft = new Point[mid - lt + 1];
    Point *yRight = new Point[rt - mid];
    int l = 0, r = 0;
    for(int i = 0; i <= rt - lt; i++){
        if (pointY[i].i() <= mid) {
            yLeft[l++] = pointY[i];
        }
        else {
            yRight[r++] = pointY[i];
        }
    }

    // 找到左边的所有点中最近点对
    Pair leftP = closestPair(pointX, yLeft, lt, mid);
    // 找到右边的所有点中最近点对
    Pair rightP = closestPair(pointX, yRight, mid + 1, rt);

    // 确定当前最近点对，并确定delta
    Pair tmpBestPair;
    if (leftP.getDis() <= rightP.getDis()) tmpBestPair = leftP;
    else tmpBestPair = rightP;

    double wallX = pointX[mid].x();
    double delta = tmpBestPair.getDis();

    // 将在宽度为2 * delta的带子中的点放入一个数组中寻找最近点对
    Point *yInDelta = new Point[rt - lt + 1];
    // 记录这些点的index
    int *index = new int[rt - lt + 1];

    int cnt = 0;
    for (int i = 0; i <= rt - lt; i++){
        if (pointY[i].x() >= wallX - delta && pointY[i].x() <= wallX + delta){
            yInDelta[cnt] = pointY[i];
            index[cnt++] = pointY[i].i();
        }
    }

    int a = -1, b = -1;
    double minDis = 999999999;
    for(int i = 0; i < cnt; i++){
        // 每个点只往后比较7个点
        for(int j = i + 1; j <= i + 7 && j < cnt; j++){
            double dis = getDis(yInDelta[i], yInDelta[j]);
            if (minDis > dis){
                a = index[i];
                b = index[j];
                minDis = dis;
            }
        }
    }

    delete [] yLeft;
    delete [] yRight;
    delete [] yInDelta;
    delete [] index;

    // 如果在带子中找到的最近点对是最优解，则返回带子中的最近点对
    if (minDis < delta) return Pair(a, b, minDis);
    else return tmpBestPair;
}


void MergeThread::setAttr(int pointNumber, QPointF* pointf){
    this->pointNumber = pointNumber;
    this->pointX = pointf;
}

void MergeThread::run(){
    auto start = system_clock::now();

    mergeSortX(pointX, 0, pointNumber - 1);
    Point *pointY = new Point[pointNumber];
    for(int i = 0; i < pointNumber; i++){
        pointY[i].setIndex(i);
        pointY[i].setX(pointX[i].x());
        pointY[i].setY(pointX[i].y());
    }

    mergeSortY(pointY, 0, pointNumber - 1);

    Pair p = closestPair(pointX, pointY, 0, pointNumber - 1);
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    timeCost = double(duration.count()) * microseconds::period::num / microseconds::period::den;

    emit returnResult(p);
    emit returnTime(timeCost);
}

double MergeThread::getDis(QPointF a, QPointF b){
    return sqrt(pow((a.x() - b.x()), 2) + pow((a.y() - b.y()), 2));
}
