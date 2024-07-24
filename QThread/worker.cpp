#include "worker.h"
#include <QThread>
#include <QDebug>


Worker::Worker(QObject *parent)
    : QObject{parent}
{

}

void Worker::doWork()
{
    for(int i=0; i<5; i++){
        QThread::sleep(1);
        qDebug() << "[Worker] in thread : " << QThread::currentThread();
    }
    emit workFinished();
}
