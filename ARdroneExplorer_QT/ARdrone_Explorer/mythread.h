#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtCore>

class MyThread : public QThread
{

public:
    MyThread();
    void run();
    void stop();
    volatile bool running = false;
private:
    QProcess *data_process;
signals:
    
public slots:
    
};

#endif // MYTHREAD_H
