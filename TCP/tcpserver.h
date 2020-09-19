#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include <server.h>

namespace Ui {
class TcpServer;
}

class TcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private:
    Ui::TcpServer *ui;
    int port;
    Server *server;

public slots:
    void updateServer(QString, int);
    void on_CreateBtn_clicked();

};

#endif // TCPSERVER_H
