#include "custom.h"
#include <QThread>
#include <QDebug>

Custom::Custom(QObject *parent)
    : QObject{parent}
{

}

void Custom::doWork()
{
    for(int i=0; i<5; i++){
        QThread::sleep(1);
        qDebug() << "[Custom] in thread : " << QThread::currentThread();
    }
    emit workFinished();
}
