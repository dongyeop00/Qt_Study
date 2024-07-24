#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , workerThread(new QThread(this))
    , customThread(new QThread(this))
    , worker(new Worker)
    , custom(new Custom)
{
    ui->setupUi(this);

    worker->moveToThread(workerThread);
    custom->moveToThread(customThread);

    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(customThread, SIGNAL(started()), custom, SLOT(doWork()));

    connect(worker, SIGNAL(workFinished()), this, SLOT(on_workFinished()));
    connect(custom, SIGNAL(workFinished()), this, SLOT(on_workFinished()));

    connect(worker, SIGNAL(workFinished()), workerThread, SLOT(quit()));
    connect(custom, SIGNAL(workFinished()), customThread, SLOT(quit()));

    connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(customThread, SIGNAL(finished()), custom, SLOT(deleteLater()));

    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(customThread, SIGNAL(finished()), customThread, SLOT(deleteLater()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    workerThread->start();
    customThread->start();
}

void MainWindow::on_workFinished()
{
    qDebug() << "Work finished in thread : " << QThread::currentThread();
}

