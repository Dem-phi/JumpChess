#ifndef AIGAME_H
#define AIGAME_H

#include <QWidget>
#include "boardmatrix.h"
#include "graph.h"
#include <vector>
#include <QRectF>
#include "mystack.h"
#include "piece.h"
#include <QDebug>
#include<QTimer>
using namespace std;

namespace Ui {
class AIgame;
}

class AIgame : public QWidget
{
    Q_OBJECT

public:
    explicit AIgame(QWidget *parent = 0);
    ~AIgame();
    void paintEvent(QPaintEvent* event);
    void setPiece();        //我方布棋
    void setPieceAI();      //AI方布棋

    void produceRectF();    //生成可点击区域

    void producePiece();    //创建玩家棋子
    void producePieceAI();  //创建AI棋子
    void mousePressEvent(QMouseEvent* event);       //鼠标点击事件
    void Shiftmodify(int x1,int y1,int x2,int y2);  //根据坐标走棋后更正相关信息
    void modify(int m1,int n1,int m2,int n2);       //根据下标走棋后更正相关信息

    bool isLegalMove(int x1,int y1,int x2,int y2);  //判断是否合法走棋
    void getLegalMove(int x1,int y1);               //获得所有能走的位置
    void jumpMove(int x,int y);                     //寻找能跳到的位置
    void moveProcess();                             //根据数组完成棋子移动

    void judgeplaywin();                                //判断胜负函数
    void judgeAIwin();                               //判断胜负函数
    int AIJudge();                                  //AI判断函数，找到最有走棋方式
    void buildPath(int pnumber);                    //根据选定的棋子传建一条通路
    void longJump();                                //生成AI下一步每个棋子能走的最大权值的位置
    void humanJump();                               //生成玩家下一步每个棋子能走的最大权值的位置
    void OhumanJump();                              //生成玩家每个棋子当前能走的最大权值的位置

private:
    Ui::AIgame *ui;
    QPainter *paint;
    boardMatrix* b;             //坐标矩阵
    Graph* graph;               //路径图
    Piece* select;              //当前选棋子
    int clickPieceNum;          //点击次数
    int* way;                   //到目标点的前趋数组指针
    int waylen;                 //通路长度
    int flag[183];              //通路上的每一个点
    vector<QRectF*> vRectF;     //矩形区域链表
    vector<Piece*> vPieces;     //棋子链表
    vector<int> legal;          //记录可以达到的点
    vector<int> longjump;       //记录AI当前每个点可以到达的最大权值
    vector<int> opjump;         //记录玩家当前每个点可以到达的最大权值
    vector<int> Olongjump;      //记录AI上一步每个点可以到达的最大权值
    vector<int> Oopjump;        //记录玩家上一步每个点可以到达的最大权值
    myStack* allstep;           //玩家走过的每一步位置
    myStack* AIstep;            //AI走过的每一步位置
    int control;                //控制权 玩家 0 AI 1
    int range;                  //棋局控制权值
    int attck;                  //进攻比例
    int defence;                //防守比例
    int fornest;                //搭桥比例
    int judgeplay;              //判断输赢数值
    int judgeAI;
    QTimer *msTimer;            //倒计时
    int counttime;              //倒计时时间
    int totaltime;              //总时间
    int falsetime;              //超时次数
    void sleep();                   //延时函数
    void setState(int as);          //设置模式函数
    int ps;
public slots:
    void processClick(int,int);     //槽函数
    void TimeSlot();
private slots:
    void on_pushButton_clicked();   //按钮函数
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // AIGAME_H
