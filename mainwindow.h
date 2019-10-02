#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPointF>
#include <QString>
#include <QPalette>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMainWindow>
#include <QIntValidator>

#include "pair.h"
#include "naivethread.h"
#include "mergethread.h"
#include "paintedwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void clear(); // 清空画板
    void generatePointsRandomly();  // 随机产生点
    void naiveMethod();  // 常规方法寻找最近点对
    void mergeMethod();  // 分治方法寻找最近点对
    void drawLine(Pair);  // 在最近点对之间连线
    void showTime(double);  // 显示算法所用时间
    void addPointsByMouse();  // 使用鼠标添加点


private:
    Ui::MainWindow *ui;
    bool finding = false;  // 是否正在进行查找
    bool mouse = false;  // 是否正在用鼠标输入点
    bool painted = false;  // 是否已产生点
    int pointNumber;  // 点的数量
    NaiveThread *nt;  // 常规方法对应线程
    MergeThread *mt;  // 分治法对应线程

    void clearLabels();  // 清除标签
    void mousePressEvent(QMouseEvent *event);  // 鼠标点击事件
};
#endif // MAINWINDOW_H
