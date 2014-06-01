#include "dataworker.h"

DataWorker::DataWorker(QObject *parent) :
    QObject(parent)
{
}

void DataWorker::DoSetup(QThread &cThread)
{
    connect(&cThread, SIGNAL(started()),this,SLOT(DoWork()));

}

void DataWorker::DoWork()
{
    data_process = new QProcess(this);

    data_process->start("rosrun ardrone_explorer subscriber_altitude");

    qDebug() << "running";
    while(running){
        //qDebug() << "running";

        //if(data_process->bytesAvailable())
        //{
            data_process->waitForReadyRead();
            qDebug() << "data: "<< data_process->readLine();
        //}
    }
    qDebug() << "stopped";

}
