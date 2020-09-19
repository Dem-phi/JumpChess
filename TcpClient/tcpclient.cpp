#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QMessageBox>
#include <QHostInfo>
#include <QTcpSocket>

TcpClient::TcpClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    status = false;
    port = 8010;
    ui->portLineEdit->setText(QString::number(port));
    serverIP = new QHostAddress();
    ui->sendBtn->setEnabled(false);
}

TcpClient::~TcpClient()
{
    delete ui;
}


void TcpClient::on_sendBtn_clicked()
{
    if(ui->sendLineEdit->text()==""){
        return;
    }
    QString msg = userName+":"+ui->sendLineEdit->text();
    tcpSocket->write(msg.toLatin1(), msg.length());
    ui->sendLineEdit->clear();
}

void TcpClient::slotConnected(){
    ui->sendBtn->setEnabled(true);
    ui->enterBtn->setText(tr("Leave"));
    int length = 0;
    QString msg=userName+tr(":Enter Chat Room");
    if((length = tcpSocket->write(msg.toLatin1(), msg.length()))!=msg.length()){
        return;
    }
}

void TcpClient::on_enterBtn_clicked()
{
    if(!status){
        QString ip = ui->serverIPLineEdit->text();
        if(!serverIP->setAddress(ip)){
            QMessageBox::information(NULL, "Error", "server ip address error!");
            return;
        }
       if(ui->userNameLineEdit->text()==""){
            QMessageBox::information(NULL, "Error", "User name error!");
            return;
       }
       userName = ui->userNameLineEdit->text();
       tcpSocket = new QTcpSocket(this);
       connect(tcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
       connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
       connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
       tcpSocket->connectToHost(*serverIP, port);
       status = true;
    }
    else{
        int length=0;
        QString msg = userName+tr(":Leave Chat Room");
        if((length = tcpSocket->write(msg.toLatin1(), msg.length()))!=msg.length()){
            return;
        }
        tcpSocket->disconnectFromHost();
        status = false;
    }
}

void TcpClient::slotDisconnected(){
    ui->sendBtn->setEnabled(false);
    ui->enterBtn->setText(tr("Enter Chat room"));
}

void TcpClient::dataReceived(){
    while(tcpSocket->bytesAvailable()){
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());
        tcpSocket->read(datagram.data(), datagram.size());
        QString msg=datagram.data();
        ui->contentListWidget->addItem(msg.left(datagram.size()));
    }
}
