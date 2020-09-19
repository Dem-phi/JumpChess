#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QHostAddress>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpClient; }
QT_END_NAMESPACE

class TcpClient : public QMainWindow
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();

private:
    Ui::TcpClient *ui;
    bool status;
    int port;
    QHostAddress *serverIP;
    QString userName;
    QTcpSocket *tcpSocket;

public slots:
    void slotConnected();
    void slotDisconnected();
    void dataReceived();

private slots:
    void on_sendBtn_clicked();
    void on_enterBtn_clicked();
};
#endif // TCPCLIENT_H




