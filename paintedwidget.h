#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H
#include "pair.h"
#include <QPen>
#include <QTime>
#include <QPointF>
#include <QWidget>
#include <QPainter>
#include <QtGlobal>
#include <QPaintEvent>
#define MAXPOINTSNUM 1000005

class PaintedWidget : public QWidget
{
public:
        PaintedWidget(QWidget* w);
        ~PaintedWidget();
        void setPointsNumber(int number);
        void setDraw(bool flag);
        void setPainted(bool flag);
        void setLink(bool flag);
        void setAddPoint(bool flag);
        QPointF* getPoints();
        void setPair(int pa, int pb, double timeCost);
        void addPoints(int x, int y);

protected:
        void paintEvent(QPaintEvent *event);

private:
        bool readyToDrawPoints, readyToLink, painted, addPoint;
        int pointsNumber; // 当前鼠标输入的点的数量
        int penPixel;
        QPointF pointf[MAXPOINTSNUM];
        int pa, pb;
        double minDis, timeCost;
};

#endif // PAINTEDWIDGET_H
