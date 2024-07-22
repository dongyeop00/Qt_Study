#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent) {

}

void MyThread::run() {
    qDebug() << "쓰레드 시작";
    while(!isInterruptionRequested()){
        QThread::sleep(1);
        qDebug() << "쓰레드가 작동중입니다.";
    }
    qDebug() << "쓰레드가 종료 중입니다.";
}
