#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

class Worker : public QThread {
public:
    Worker(QMutex *mutex, int *counter) : mutex(mutex), counter(counter) {}

protected:
    void run() override {
        for (int i = 0; i < 100; ++i) {
            QMutexLocker locker(mutex);
            (*counter)++;
        }
    }

private:
    QMutex *mutex;
    int *counter;
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    const int numThreads = 10;
    QMutex mutex;
    int counter = 0;

    Worker *workers[numThreads];

    for (int i = 0; i < numThreads; ++i) {
        workers[i] = new Worker(&mutex, &counter);
        workers[i]->start();
    }

    for (int i = 0; i < numThreads; ++i) {
        workers[i]->wait();
        delete workers[i];
    }

    qDebug() << "Final counter value:" << counter;

    return a.exec();
}
