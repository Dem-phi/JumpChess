#include "tcpserver.h"
#include "ui_tcpserver.h"

TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    port = 8010;
    ui->PortLineEdit->setText(QString::number(port));
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::on_CreateBtn_clicked()
{
    server = new Server(this, port);
    connect(server, SIGNAL(updateServer(QString, int)),
            this, SLOT(updateServer(QString, int)));
    ui->CreateBtn->setEnabled(false);
}

void TcpServer::updateServer(QString msg, int length){
    ui->ContentListWidget->addItem(msg.left(length));
}
