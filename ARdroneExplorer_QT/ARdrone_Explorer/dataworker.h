#ifndef DATAWORKER_H
#define DATAWORKER_H

#include <QObject>
#include <QtCore>
#include <QThread>

class DataWorker : public QObject
{
    Q_OBJECT
public:
    explicit DataWorker(QObject *parent = 0);
    void DoSetup(QThread &cThread);

    bool running=false;
    
signals:
    
public slots:
    void DoWork();
private:
    QProcess *data_process;

};

#endif // DATAWORKER_H
