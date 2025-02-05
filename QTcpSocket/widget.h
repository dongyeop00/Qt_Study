#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket *tcpSocket;

    void initialize();

private slots:
    void connectButton();
    void readMessage();
    void disconnected();
};
#endif // WIDGET_H
