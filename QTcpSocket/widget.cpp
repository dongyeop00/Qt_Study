#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectButton()));
    initialize();
}

void Widget::initialize(){
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void Widget::connectButton(){
    QString serverip = ui->lineEdit->text().trimmed();

    QHostAddress serverAddress(serverip);

    tcpSocket->connectToHost(serverAddress, 25000);
}

void Widget::readMessage(){
    if(tcpSocket->bytesAvailable() >= 0){
        QByteArray readData = tcpSocket->readAll();
        ui->textEdit->append(readData);
    }
}

void Widget::disconnected(){
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

Widget::~Widget()
{
    delete ui;
}
