#ifndef PATH_WINDOW_H
#define PATH_WINDOW_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <drone_item.h>
#include <mythread.h>



namespace Ui {
class Path_window;
}

class Path_window : public QDialog
{
    Q_OBJECT
    
public:
    explicit Path_window(QWidget *parent = 0);
    ~Path_window();
    
    void new_coordinates(double_t new_x, double_t new_y);

private:
    Ui::Path_window *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    MyThread *mythread;

    Drone_item *my_drone;
    double_t lastcoordinateX = 0;
    double_t lastcoordinateY = 0;

    bool thread_running=false;
    float h11 = 1.0;
    float h12 = 0;
    float h21 = 1.0;
    float h22 = 0;

private slots:

    void on_but_zoomin_clicked();

    void on_but_zoomout_clicked();

    void on_but_startstop_clicked();

protected:
    //void advance(int phase);
    void paintEvent(QPaintEvent *e);
//    void timerEvent(QTimerEvent *event);

protected slots:
    void advance();

signals:

};


//class MyGraphicsView : public QGraphicsView
//{
//    Q_OBJECT
//public:
//    MyGraphicsView(QWidget* parent = NULL);

//protected:
//    virtual void wheelEvent(QWheelEvent *event);
//};

#endif // PATH_WINDOW_H
