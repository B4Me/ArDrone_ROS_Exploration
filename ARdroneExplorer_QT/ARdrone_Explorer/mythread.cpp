#include "mythread.h"
#include <QtCore>
#include <QDebug>

MyThread::MyThread()
{
}

void MyThread::run()
{
    qDebug() << "process run";

    data_process = new QProcess(this);

    data_process->start("rosrun ardrone_explorer subscriber_altitude");

    while(running){
        //qDebug() << "running";

        if(data_process->bytesAvailable())
        {
            qDebug() << "data: "<< data_process->readLine();
        }
        sleep(1);
    }
    qDebug() << "stopped";
}

void MyThread::stop()
{
    qDebug() << "stopping thread";
    data_process->terminate();
    running=false;
}

