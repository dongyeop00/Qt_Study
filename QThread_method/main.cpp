#include <QCoreApplication>

#include <QDebug>
#include <QDeadlineTimer>
#include <QEventLoop>

#include "mythread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyThread thread;

    QObject::connect(&thread, &QThread::started, [](){
        qDebug() << "쓰레드가 시작되었습니다.";
    });

    QObject::connect(&thread, &QThread::finished, [](){
        qDebug() << "쓰레드가 종료되었습니다.";
    });

    // Start Thread
    thread.start();
    thread.sleep(1);
    qDebug() << "쓰레드가 작동중입니다." << thread.isRunning();

    // Set Thread Priority
    thread.setPriority(QThread::HighPriority);
    qDebug() << "쓰레드 우선 순위 : " << thread.priority();

    // Set Stack Szie
    thread.setStackSize(1024 * 1024); // 1 MB
    qDebug() << "쓰레드 스택 사이즈 : " << thread.stackSize();

    // Request interruption
    QThread::sleep(3); // Let the thread run for a while
    thread.requestInterruption();
    qDebug() << "중단 요청 : " << thread.isInterruptionRequested();

    // Wait for the thread to finish
    if (thread.wait(QDeadlineTimer(QDeadlineTimer::Forever))) {
        qDebug() << "스레드가 데드라인에 의한 종료";
    } else {
        qDebug() << "스레드가 데드라인까지 종료되지 못함";
    }

    qDebug() << "쓰레드가 종료된 상태 :" << thread.isFinished();

    return a.exec();
}
