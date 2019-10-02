#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pair.h"
#include "paintedwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置画板为白色
    QPalette Pal(palette()); // TODO: learn this
    Pal.setColor(QPalette::Background, Qt::white);
    ui->paintedWidget->setAutoFillBackground(true);
    ui->paintedWidget->setPalette(Pal);

    // 设置lineEdit的输入类型为1到100万的整数
    ui->lineEdit->setValidator(new QIntValidator(1, 1000000, this));

    // 常规方法线程对象
    nt = new NaiveThread();
    mt = new MergeThread();
    // 将点的数量初始化为0
    pointNumber = 0;

    // 设置信号槽
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clear()));
    connect(ui->mouseButton, SIGNAL(clicked(bool)), this, SLOT(addPointsByMouse()));
    connect(ui->randomButton, SIGNAL(clicked(bool)), this, SLOT(generatePointsRandomly()));

    connect(ui->n2Button, SIGNAL(clicked(bool)), this, SLOT(naiveMethod()));
    connect(nt, SIGNAL(returnResult(Pair)), this, SLOT(drawLine(Pair)));
    connect(nt, SIGNAL(returnTime(double)), this, SLOT(showTime(double)));

    connect(ui->nlgnButton, SIGNAL(clicked(bool)), this, SLOT(mergeMethod()));
    connect(mt, SIGNAL(returnResult(Pair)), this, SLOT(drawLine(Pair)));
    connect(mt, SIGNAL(returnTime(double)), this, SLOT(showTime(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete nt;
    delete mt;
}

// 清空画板
void MainWindow::clear(){
    if(finding)
    {
        QMessageBox::warning(this, "Error!", "You can't clean now!");
        return;
    }
    //恢复初始状态
    finding = false;
    painted = false;
    mouse = false;
    pointNumber = 0;
    ui->paintedWidget->setLink(false);
    ui->paintedWidget->setPainted(false);
    ui->paintedWidget->setDraw(false);
    ui->paintedWidget->setAddPoint(false);
    ui->paintedWidget->update();
    ui->paintedWidget->setPointsNumber(0);
    clearLabels();
}

// 随机产生点
void MainWindow::generatePointsRandomly(){
    if (finding){
        QMessageBox::warning(this, "Error!", "You can't generate points now.");
        return;
    }

    // 获取输入的点数
    int inputNumber = ui->lineEdit->text().toInt();
    if(inputNumber > 1000000)
    {
        QMessageBox::warning(this, "Error!", "Too many points!");
        return;
    }

    if(inputNumber < 2)
    {
        QMessageBox::warning(this, "Error!", "At least two point!");
        return;
    }

    // 设置相关状态
    painted = true;
    mouse = false;
    pointNumber = inputNumber;

    clearLabels();
    ui->paintedWidget->setPointsNumber(pointNumber);
    ui->paintedWidget->setDraw(true);
    ui->paintedWidget->setLink(false);
    ui->paintedWidget->update();
}

// 在线程中使用常规方法
void MainWindow::naiveMethod(){
    if (finding){
        QMessageBox::warning(this, "Error!", "Busy now.");
        return;
    }

    if (!painted){
        QMessageBox::warning(this, "Error!", "No points!");
        return;
    }

    if (pointNumber < 2){
        QMessageBox::warning(this, "Error!", "At least two point!");
        return;
    }

    finding = true;

    clearLabels();
    ui->paintedWidget->setLink(false);
    ui->paintedWidget->setPainted(true);
    ui->paintedWidget->update();
    // 设置常规线程对象的一些属性
    nt->setAttr(pointNumber, ui->paintedWidget->getPoints());
    // 使用常规方法寻找最近点对
    nt->start();
}

// 在线程中使用分治方法
void MainWindow::mergeMethod(){
    if (finding){
        QMessageBox::warning(this, "Error!", "Busy now.");
        return;
    }

    if (!painted){
        QMessageBox::warning(this, "Error!", "No points!");
        return;
    }

    if (pointNumber < 2){
        QMessageBox::warning(this, "Error!", "At least two point!");
        return;
    }


    finding = true;

    clearLabels();
    ui->paintedWidget->setLink(false);
    ui->paintedWidget->setPainted(true);
    ui->paintedWidget->update();
    // 设置常规线程对象的一些属性
    mt->setAttr(pointNumber, ui->paintedWidget->getPoints());
    // 使用常规方法寻找最近点对
    mt->start();
}

// 将最近点对连线，同时在label上显示点的数量以及最近点对之间的距离
void MainWindow::drawLine(Pair p){
    ui->countLabel->setText(QString::number(pointNumber));
    ui->disLabel->setText(QString::number(p.getDis()));
    ui->paintedWidget->setLink(true);
    ui->paintedWidget->setPair(p.getP1(), p.getP2(), p.getDis());
    finding = false;
    ui->paintedWidget->update();
}

// 展示算法运行的时间
void MainWindow::showTime(double timeCost){
    QString t = QString::number(timeCost);

    ui->resultLabel->setText(t + "s");
}

// 将数据信息清空
void MainWindow::clearLabels(){
    ui->countLabel->clear();
    ui->disLabel->clear();
    ui->resultLabel->clear();
}

// 使用鼠标添加点
void MainWindow::addPointsByMouse(){
    if (finding){
        QMessageBox::warning(this, "Error!", "Busy now.");
        return;
    }

    clear();
    mouse = true;
    ui->paintedWidget->update();
}

// 鼠标点击事件
void MainWindow::mousePressEvent(QMouseEvent *event){
    if (mouse && event->button() == Qt::LeftButton){
        // 获取鼠标当前的位置
        const int x = event->x();
        const int y = event->y();
        // 如果当前位置不在可以画点的位置上，退出，不画点
        if (x < 5 || y < 5 || x > WIDGETWIDTH + 5 || y > WIDGETHEIGHT + 5) return;

        // 在点的数组中添加当前点并画出
        painted = true;
        ui->paintedWidget->addPoints(x, y);
        pointNumber++;
        clearLabels();
        ui->countLabel->setText(QString::number(pointNumber));
        ui->paintedWidget->setAddPoint(true);
        ui->paintedWidget->setDraw(false);
        ui->paintedWidget->setLink(false);
        ui->paintedWidget->update();
    }
}
