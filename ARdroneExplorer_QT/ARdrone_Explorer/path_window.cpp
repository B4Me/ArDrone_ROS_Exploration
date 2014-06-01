#include "path_window.h"
#include "ui_path_window.h"
#include <QScrollBar>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMouseEvent>
#include <drone_item.h>
#include <QTimer>

Path_window::Path_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Path_window)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setSceneRect(-4000,-4000,8000,8000);

    mythread = new MyThread;
    my_drone = new Drone_item;
    scene->addItem(my_drone);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),scene,SLOT(advance()));
    connect(timer, SIGNAL(timeout()),this,SLOT(advance()));

    timer->start(100);
}

void Path_window::advance()
{

}


Path_window::~Path_window()
{
    delete ui;
}

void Path_window::new_coordinates(double_t new_x, double_t new_y)
{
    scene->addLine(lastcoordinateX,lastcoordinateY,new_x,new_y,QPen(Qt::red));
    lastcoordinateX = new_x;
    lastcoordinateY = new_y;

    my_drone->newValue(new_x, new_y);
    ui->graphicsView->centerOn(new_x,new_y);
}


void Path_window::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pointpen(Qt::black);
    pointpen.setWidth(6);
    QPen linepen(Qt::red);
    linepen.setWidth(2);

    QPen polypen(Qt::blue);
    pointpen.setWidth(2);

    QPoint p1;
    p1.setX(10);
    p1.setY(10);
    QPoint p2;
    p2.setX(100);
    p2.setY(100);

    painter.setPen(linepen);
    painter.drawLine(p1,p2);
    painter.setPen(pointpen);
    painter.drawPoint(p1);
    painter.drawPoint(p2);

    painter.setPen(polypen);
}

void Path_window::on_but_zoomin_clicked()
{
      double scaleFactor = 1.0; //How fast we zoom
      const qreal minFactor = 1.0;
      const qreal maxFactor = 50.0;
      h11 = (h11 >= maxFactor) ? h11 : (h11 + scaleFactor);
      h22 = (h22 >= maxFactor) ? h22 : (h22 + scaleFactor);

      ui->graphicsView->scale(2,2);      
}

void Path_window::on_but_zoomout_clicked()
{
    double scaleFactor = 0.5; //How fast we zoom
    const qreal minFactor = 0.1;
    const qreal maxFactor = 10.0;

    h11 = (h11 <= minFactor) ? minFactor : (h11 - scaleFactor);
    h22 = (h22 <= minFactor) ? minFactor : (h22 - scaleFactor);

    ui->graphicsView->scale(0.5,0.5);
}

void Path_window::on_but_startstop_clicked()
{
    if(mythread->running==false){
        mythread->running=true;
         mythread->start();
    }else{
        mythread->stop();
    }

}
