#ifndef PAINTEDWIDGET_H
#define PAINTEDWIDGET_H
#include <QPen>
#include <QTime>
#include <QPointF>
#include <QWidget>
#include <QPainter>
#include <QtGlobal>
#include <QPaintEvent>

#include "pair.h"
#define MAXPOINTSNUM 1000005
#define WIDGETWIDTH 940
#define WIDGETHEIGHT 740

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
        int pointsNumber; // 点的数量
        int penPixel;  // 点的大小
        QPointF pointf[MAXPOINTSNUM];  // 点数组
        int pa, pb;  // 最近点对两个点的编号
        double minDis, timeCost;  // 最近点对之间距离以及算法所用时间
};

#endif // PAINTEDWIDGET_H
