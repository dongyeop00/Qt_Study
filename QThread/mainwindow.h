#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "worker.h"
#include "custom.h"
#include <QMainWindow>
#include <QThread>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QThread *workerThread;
    QThread *customThread;
    Worker *worker;
    Custom *custom;

private slots:
    void on_startButton_clicked();
    void on_workFinished();
};
#endif // MAINWINDOW_H
