#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pair.h"
#include "paintedwidget.h"
#include "naivethread.h"
#include <QPointF>
#include <QString>
#include <QPalette>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QIntValidator>
#include <QMouseEvent>
#include <QMainWindow>

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
    void clear();
    void generatePointsRandomly();
    void naiveMethod();
    void drawLine(Pair);
    void showTime(double);
    void addPointsByMouse();


private:
    Ui::MainWindow *ui;
    // 是否正在进行查找
    bool finding = false;
    // 是否正在用鼠标输入点
    bool mouse = false;
    // 是否已产生点
    bool painted = false;
    int pointNumber;
    NaiveThread *nt;

    void clearLabels();
    void mousePressEvent(QMouseEvent *event);
};
#endif // MAINWINDOW_H
