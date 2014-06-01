#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "path_window.h"
#include "sstream"
#include <stdio.h>
#include "iostream"
#include <QProcess>
#include "stdlib.h"

#include "dataworker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    path_window = new Path_window(this);

    DataWorkerThread = new QThread;
    cDataWorker = new DataWorker;

    cDataWorker->DoSetup(*DataWorkerThread);
    cDataWorker->moveToThread(DataWorkerThread);

    //mythread = new MyThread;
}

MainWindow::~MainWindow()
{
    delete ui;
    DataWorkerThread->exit();
    delete DataWorkerThread;
    delete cDataWorker;
}

void MainWindow::on_but_startros_clicked()
{
    //system("env");
   system("./launch_script.sh");
}


void MainWindow::on_but_stopros_clicked()
{
    system("killall rosmaster");
    system("killall roslaunch");
    system("killall rosout");
    system("killall rostopic");
}

void MainWindow::on_but_takeoff_clicked()
{
    QProcess process1;
    system("rosservice call /ardrone/setledanimation 1 4 5 &");
    system("rostopic pub /ardrone/takeoff std_msgs/Empty &");
}

void MainWindow::on_but_land_clicked()
{
    system("rosservice call /ardrone/setledanimation 2 4 5 &");
    system("rostopic pub /ardrone/land std_msgs/Empty &");
}

void MainWindow::on_but_forward_clicked()
{
    system("rostopic pub /cmd_vel geometry_msgs/Twist '[0.1, 0.0, 0.0]' '[0.0, 0.0, 0.0]' &");
}

void MainWindow::on_but_backward_clicked()
{
     system("rostopic pub /cmd_vel geometry_msgs/Twist '[-0.1, 0.0, 0.0]' '[0.0, 0.0, 0.0]' &");
}

void MainWindow::on_but_left_clicked()
{
     system("rostopic pub /cmd_vel geometry_msgs/Twist '[0.0, 0.1, 0.0]' '[0.0, 0.0, 0.0]' &");
}

void MainWindow::on_but_right_clicked()
{
     system("rostopic pub /cmd_vel geometry_msgs/Twist '[0.0, -0.1, 0.0]' '[0.0, 0.0, 0.0]' &");
}

void MainWindow::on_but_hover_clicked()
{
     system("rostopic pub /cmd_vel geometry_msgs/Twist '[0.0, 0.0, 0.0]' '[0.0, 0.0, 0.0]' &");
}
void MainWindow::on_but_nothover_clicked()
{
    system("rostopic pub /cmd_vel geometry_msgs/Twist '[0.0, 0.0, 0.0]' '[0.1, 0.1, 0.0]' &");
}

void MainWindow::on_but_reset_clicked()
{
    system("rostopic pub /ardrone/reset std_msgs/Empty &");
}



void MainWindow::on_but_flattrim_clicked()
{
    system("rosservice call /ardrone/flattrim &");
}

void MainWindow::on_but_path_clicked()
{
//    Path_window path_window;
//    path_window.setModal(true);
//    path_window.exec();

    path_window->show();
}

void MainWindow::data_process_output()
{
    qDebug() << "data_process_output\n";
    QString tempString = data_process->readAllStandardOutput();
    QStringList tempList = tempString.split(",");

    if(loop_time < 2)
    {
        loop_time++;
        last_time = tempList.at(0).toLong();
        last_vy = tempList.at(1).toFloat()/1000;
        last_vx = tempList.at(2).toFloat()/1000;
    }else{
    qDebug() << tempList.at(0);
    qDebug() << tempList.at(1);
    qDebug() << tempList.at(2);

    new_time = tempList.at(0).toLong();
    new_vy = -tempList.at(1).toFloat()/100;
    new_vx = -tempList.at(2).toFloat()/100;

    new_x = (old_x+((new_time-last_time)/1000000)*last_vx);
    new_y = (old_y+((new_time-last_time)/1000000)*last_vy);

    qDebug() << "delta time: "<< ((new_time-last_time)/1000000);


    qDebug() << "x,y : "<< new_x << "," << new_y;

    path_window->new_coordinates(new_x,new_y);

    last_time = new_time;
    last_vx = new_vx;
    last_vy = new_vy;
    old_x = new_x;
    old_y = new_y;
    }}

void MainWindow::data_process_error()
{
    qDebug() << "data_process_error\n";
    qDebug()  << data_process->readAllStandardError();
}

void MainWindow::on_but_datalog_clicked(bool checked)
{
    if(checked)
    {
        data_process = new QProcess(this);
        connect(data_process, SIGNAL(readyReadStandardOutput()), this, SLOT(data_process_output()));
        connect(data_process, SIGNAL(readyReadStandardError()), this, SLOT(data_process_error()));

        data_process->start("rosrun ardrone_explorer subscriber_altitude");
        //system("rosrun ardrone_explorer subscriber_altitude &");
    }else{
        qDebug() << "depressed\n";
        cDataWorker->running=false;
       DataWorkerThread->exit();

        data_process->terminate();
    }
}
