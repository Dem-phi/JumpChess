#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include "boardmatrix.h"
#include "graph.h"
#include <vector>
#include <QRectF>
#include <QTimer>
#include"mystack.h"
#include "piece.h"
using namespace std;
namespace Ui {
class gameplay;
}

class gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit gameplay(QWidget *parent = 0);
    ~gameplay();
    void paintEvent(QPaintEvent* event);
    void setPiece();                //甲方布棋
    void setPieceAI();              //乙方布棋
    int clickPieceNum;              //点击次数
    void produceRectF();            //创建可点击区域
    void producePiece();            //创建棋子
    void producePieceAI();
    void mousePressEvent(QMouseEvent* event);
    void modifyInformation(int x1,int y1,int x2,int y2);//走棋后更正相关信息
    bool isLegalMove(int x1,int y1,int x2,int y2);      //判断是否合法走棋
    void jumpMove(int x,int y);
    void moveProcess();             //走棋流程
    void sleep();                   //延时函数
    void judgewinA();                //判断胜负
    void judgewinB();                //判断胜负
private:
    Ui::gameplay *ui;
    QPainter *paint;
    boardMatrix* b;
    Graph* graph;
    Piece* select;
    int* way;
    int waylen;
    int flag[183];
    vector<QRectF*> vRectF;     //可点击的有效区域
    vector<Piece*> vPieces;     //所有棋子
    vector<int> legal;          //所有可以走到的位置
    myStack* allstep;           //玩家走过的每一步位置
    myStack* AIstep;            //AI走过的每一步位置
    int control;                //当前控制权
    int judgeA;                 //判断胜负标识
    QTimer *msTimer;            //倒计时
    int counttime;              //倒计时时间
    int totaltime;              //总时间
    int falsetime;              //超时次数
    int falsetime2;              //超时次数
public slots:
    void processClick(int,int);
    void processClickAI(int,int);
    void TimeSlot();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

#endif // GAMEPLAY_H
