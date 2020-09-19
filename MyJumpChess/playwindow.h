#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkInterface>
#include <QRectF>
#include <QTimer>
#include <vector>
#include "qdom.h"
#include "board.h"
#include "piece.h"
#include "mainwindow.h"
#include <math.h>
#include <mystack.h>
#include <QMouseEvent>
#include <gameover.h>

enum ChatMsgType
{
  ChatMsg, OffLine
};

namespace Ui {
class playwindow;
}

class playwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit playwindow(QWidget *parent = nullptr);
    ~playwindow();
    // ForChat
    /*void initMainWindow();
    void offLine(QString name, QString time);
    void sendChatMsg(ChatMsgType msgType, QString rmtName="");
    QString getLocHostIP();
    QString getLocChatMsg();
    */
    //For Game
    int clickPieceNum;
    //void paintEvent(QPaintEvent* event);
    void setPiece0();   // 0号玩家初始化棋子
    void setPiece3();   // 3号玩家初始化棋子
    void jumpMove(int m, int n);    // 计算并显示所有可达的位置
    bool isLegalMove(int x1, int y1, int x2, int y2);   //判断是否合法
    void modifyInformation(int x1, int y1, int x2, int y2);   //更新棋盘、棋子信息
    void produceRectF(); // 创建可点击的区域
    void producePiece0();
    void producePiece3();
    void mousePressEvent(QMouseEvent* event);
    void moveProcess(int x2, int y2); //走棋流程
    void sleep();       //延时函数
    void judgewin0();
    void judgewin3();

private slots:
    void on_regret_clicked();

    void on_exit_clicked();

public slots:
    void processClick0(int,int);
    void processClick3(int,int);

private:
    Ui::playwindow *ui;
    QString myname = "";
    QPainter *paint;
    //QUdpSocket *myUdpSocket;
    //qint16 myUdpPort;
    //For Game
    board* boardMatrix;         //棋盘对象
    Piece* select;
    int* way;
    int waylen;
    int flag[183];
    std::vector<QRectF*> vRectF;//可点击的区域
    std::vector<Piece*> vPieces;//所有棋子
    std::vector<int> legal;     //所有可走合法位置 动态链表
    mystack* allstep0;          //玩家0走的位置
    mystack* allstep3;          //玩家3走的位置
    int judge;                  //判断胜负
    int control;                //控制权 0-5 上方 顺时针
};

#endif // PLAYWINDOW_H
