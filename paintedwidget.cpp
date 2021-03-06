#include "paintedwidget.h"

PaintedWidget::PaintedWidget(QWidget* w) : QWidget(w)
{
    readyToDrawPoints = false;
    readyToLink = false;
    painted = false;
    addPoint = false;
    pointsNumber = 0;

    // 随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}


PaintedWidget::~PaintedWidget()
{

}


void PaintedWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 不同的点的数量规模对应不同的像素
    if (pointsNumber > 50000) penPixel = 1;
    else if (pointsNumber <= 5000) penPixel = 4;
    else penPixel = 2;

    if (readyToDrawPoints){
        painter.setPen(QPen(QColor(0, 0, 0), penPixel)); // 设置画笔
        // 随机产生点
        for (int i=0; i<pointsNumber; ++i)
        {
            pointf[i].setX(qrand()%WIDGETWIDTH + 5);
            pointf[i].setY(qrand()%WIDGETHEIGHT + 5);
        }

        painter.drawPoints(pointf, pointsNumber);
        readyToDrawPoints = false;
        painted = true;
    }

    // 当处于连线状态和描点结束状态时，保证窗口失焦后不重绘
    if(painted || addPoint)
    {
        painter.setPen(QPen(QColor(0, 0, 0), penPixel));
        painter.drawPoints(pointf, pointsNumber);
    }

    // 计算出结果之后开始连线
    if(readyToLink)
    {
        painter.setPen(QPen(QColor(0, 0, 0), penPixel));
        painter.drawPoints(pointf, pointsNumber);

        // 直线无锯齿
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor(255, 0, 0), 2));
        painter.drawLine(pointf[pa], pointf[pb]);

        // 画圆，将最近点对圈出
        painter.setPen(QPen(QColor(255, 0, 0), 4));
        painter.drawEllipse(QPointF((pointf[pa].x() + pointf[pb].x()) / 2, (pointf[pa].y() + pointf[pb].y()) / 2), minDis / 2 + 20, minDis / 2 + 20);
        painted = false;
        addPoint = false;
    }

    QWidget::paintEvent(event);
}


void PaintedWidget::setPointsNumber(int number){
    this->pointsNumber = number;
}

void PaintedWidget::setDraw(bool flag){
    this->readyToDrawPoints = flag;
}

void PaintedWidget::setPainted(bool flag){
    this->painted = flag;
}

void PaintedWidget::setLink(bool flag){
    this->readyToLink = flag;
}

void PaintedWidget::setAddPoint(bool flag){
    this->addPoint = flag;
}

QPointF* PaintedWidget::getPoints(){
    return pointf;
}

void PaintedWidget::setPair(int pa, int pb, double minDis){
    this->pa = pa;
    this->pb = pb;
    this->minDis = minDis;
}

void PaintedWidget::addPoints(int x, int y){
    pointf[pointsNumber].setX(x);
    pointf[pointsNumber].setY(y);
    pointsNumber++;
}

