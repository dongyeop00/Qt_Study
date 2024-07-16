#include "widget.h"
#include "./ui_widget.h"

#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initialize();
}

void Widget::initialize(){
    QHostAddress hostAddr;

    // QNetworkInterface : 네트워크 어댑터의 이름, IP 주소, 하드웨어 주소(예: MAC 주소) 등의 정보를 얻을 수 있다.
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();

    // Use something other than localhost (127.0.0.1)
    for(int i=0; i<ipList.size(); ++i){
        // ipList.at(i) != QHostAddress::LocalHost : 현재 IP 주소가 로컬 호스트 주소(127.0.0.1)가 아닌지 확인
        // ipList.at(i).toIPv4Address() : 현재 IP 주소가 IPv4 주소인지 확인
        if(ipList.at(i) != QHostAddress::LocalHost && ipList.at(i).toIPv4Address()){
            // 조건을 만족하는 경우, hostAddr 변수에 해당 IP 주소를 저장
            hostAddr = ipList.at(i);
            break;
        }
    }

    // 만약 적절한 IP 주소를 찾지 못했다면, hostAddr을 localhost 주소로 설정
    if(hostAddr.toString().isEmpty()){
        hostAddr = QHostAddress(QHostAddress::LocalHost);
    }

    tcpServer = new QTcpServer(this);

    // hostAddr과 포트 25000에서 수신 대기하도록 설정
    // 만약 서버를 시작하지 못하면, 에러 메시지를 표시하고 애플리케이션을 종료
    if (!tcpServer->listen(hostAddr, 25000)){
        QMessageBox::critical(this, tr("TCP Server"), tr("Cannot start the server, Error: %1.").arg(tcpServer->errorString()));
        close();
        return;
    }

    // 서버가 성공적으로 시작되면, labelStatus 위젯에 서버의 IP 주소와 포트 정보를 표시
    ui->labelStatus->setText(tr("Server running \n\n"
                                "IP : %1\n"
                                "PORT : %2\n").arg(hostAddr.toString()).arg(tcpServer->serverPort()));

    // newConnection()시그널을 newConnection()슬롯에 연결하여 새 클라이언트 연결이 있을 때 해당 슬롯이 호출
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

    ui->connMsgEdit->clear();
}


void Widget::newConnection(){

    //새 클라이언트 연결이 있을 때 tcpServer의 nextPendingConnection() 함수를 호출하여 대기 중인 클라이언트 소켓을 가져온다.
    // 이 소켓은 클라이언트와의 통신에 사
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    // 클라이언트 소켓의 disconnected() 시그널을 소켓의 deleteLater() 슬롯에 연결
    // 이렇게 하면 클라이언트가 연결을 끊을 때 소켓 객체가 자동으로 삭제
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));

    // 현재 시간을 hh:mm:ss 형식으로 가져와서 문자열로 변환합니다.
    QString currTime = QTime::currentTime().toString("hh:mm:ss");

    // Client Connection" 메시지에 현재 시간을 포함시킨 텍스트를 생성
    QString text = QString("Client Connection (%1)").arg(currTime);

    // connMsgEdit 위젯에 이 텍스트를 추가
    // 이는 새 클라이언트 연결이 생길 때마다 UI에 로그를 남기기 위함
    ui->connMsgEdit->append(text);

    QByteArray message = QByteArray("Hello Client ~ ");

    clientConnection->write(message);

    clientConnection->disconnectFromHost();
   }

Widget::~Widget()
{
    delete ui;
}

