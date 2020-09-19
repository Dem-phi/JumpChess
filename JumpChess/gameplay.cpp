#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <vector>
#include <QDebug>
#include "gameplay.h"
#include "ui_gameplay.h"
#include "boardmatrix.h"
#include "mainwindow.h"
#include "graph.h"
#include <QTime>
#include "mystack.h"
#include "gameover.h"
#include "change.h"
using namespace std;
gameplay::gameplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameplay)
{
    ui->setupUi(this);
    /*s
     * 初始化各项数据
     * clickPieceNum（点击次数）
     * control（控制权）
     * range（AI棋局分布标识值）
     * select（选择的当前棋子）
     */
    this->totaltime = 0;
    this->counttime = 11;
    falsetime = 0;
    falsetime2 = 0;
    this->clickPieceNum = 0;
    this->control = 0;
    this->select = NULL;
    this->judgeA = 0;
    ui->textBrowser->setText("0");
    ui->textBrowser_2->setText("0");
    ui->label_10->setText("黑棋");

    this->msTimer=new QTimer(this);
    msTimer->start(1000);
    connect(msTimer,SIGNAL(timeout()),this,SLOT(TimeSlot()));
    //创建玩家棋子
    this->producePiece();
    //创建AI棋子
    this->producePieceAI();
    //创建棋盘区域
    this->produceRectF();
    //构建一个新的图，并进行初始化
    graph = new Graph();
    graph->init();

    //创建两个新的栈（用于保存棋子的每一步）
    allstep = new myStack();
    AIstep = new myStack();

    //创建一个新的坐标矩阵，并初始化
    b = new boardMatrix();
    b->init();

    //为每一个坐标添加正方形点击区域
    QRectF* qr;
    int k = 0;
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<13;j++)
        {
            qr=this->vRectF.at(k++);
            qr->setRect(this->b->Matrix[i][j].x,this->b->Matrix[i][j].y,40,40);
        }
    }

    //设置玩家棋子和AI的棋子
    this->setPiece();
    this->setPieceAI();

    //为每一个棋子（按钮）的点击设置槽函数
    for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
    {
        Piece* ptr = *iter;
        connect(ptr,SIGNAL(pieceInfo(int,int)),this,SLOT(processClick(int,int)));
    }
    for(vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
    {
        Piece* ptr = *iter;
        connect(ptr,SIGNAL(pieceInfo(int,int)),this,SLOT(processClickAI(int,int)));
    }

}

gameplay::~gameplay()
{
    delete ui;
}
void gameplay::paintEvent(QPaintEvent *event)
{
    /*
     * 获取widget大小
     * 填充棋盘图片
     */
    QPainter painter(this);
    int x = ui->widget->geometry().x();
    int y = ui->widget->geometry().y();
    int width = ui->widget->geometry().width();
    int height =ui->widget->geometry().height();
    QRectF rect(x,y,width,height);

    QImage image;
    image.load(":/res/chessboard.jpg");
    painter.drawImage(rect,image);


}
void gameplay::mousePressEvent(QMouseEvent* event)
{

    if(event->button()==Qt::LeftButton)
    {
        for(vector<QRectF*>::iterator iter = this->vRectF.begin();iter != this->vRectF.end();iter++)
        {
            QRectF* ptr =*iter;
            if(ptr->contains( mapFromGlobal(QCursor::pos()))==true)
            {
                if(this->select!=NULL){
                    //玩家1在操作
                    if(this->control==0){
                        if(isLegalMove(this->select->x(),this->select->y(),ptr->x(),ptr->y()))
                        {
                            counttime = 11;
                            //记录当前走的棋
                            Change* ch = new Change();
                            ch->setlastX(this->select->x());
                            ch->setlastY(this->select->y());
                            ch->setnewX(ptr->x());
                            ch->setnewY(ptr->y());
                            allstep->push(ch);
                            //更新数据
                            ui->textBrowser->setText(QString::number(allstep->num, 10));
                            modifyInformation(this->select->x(),this->select->y(),ptr->x(),ptr->y());
                            moveProcess();
                            this->clickPieceNum=0;
                            this->select->setIcon(QIcon(":/res/chess.png"));
                            this->select=NULL;
                            judgewinA();
                            control = 1;
                            ui->label_10->setText("红棋");
                        }
                        else{
                            this->clickPieceNum=0;
                            this->select->setIcon(QIcon(":/res/chess.png"));
                            this->select=NULL;
                        }
                    }
                    //玩家2在操作
                    else{
                        if(isLegalMove(this->select->x(),this->select->y(),ptr->x(),ptr->y()))
                        {
                            counttime = 11;
                            Change* ch = new Change();
                            ch->setlastX(this->select->x());
                            ch->setlastY(this->select->y());
                            ch->setnewX(ptr->x());
                            ch->setnewY(ptr->y());
                            AIstep->push(ch);
                            //更新数据
                            ui->textBrowser_2->setText(QString::number(AIstep->num, 10));
                            modifyInformation(this->select->x(),this->select->y(),ptr->x(),ptr->y());
                            moveProcess();
                            this->clickPieceNum=0;
                            this->select->setIcon(QIcon(":/res/chess2.png"));
                            this->select=NULL;
                            judgewinB();
                            control = 0;
                            ui->label_10->setText("黑棋");
                        }
                        else{
                            this->clickPieceNum=0;
                            this->select->setIcon(QIcon(":/res/chess2.png"));
                            this->select=NULL;
                        }

                    }
                }


            }

        }

    }

}
void gameplay::produceRectF()
{
    //创建棋盘可点击区域链表
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<13;j++)
        {
            QRectF* rect=new QRectF();
            this->vRectF.push_back(rect);
        }
    }
}
void gameplay::producePiece()
{
    //生成玩家方的棋子
    for(int i = 0;i<10;i++){
        Piece* p = new Piece();
        vPieces.push_back(p);
    }
    for(vector<Piece*>::iterator iter = vPieces.begin();iter != vPieces.end();iter++)
    {
        Piece* p = *iter;
        p->setStatus(0);                //玩家为0
        p->setIcon(QIcon(":/res/chess.png"));
        p->setIconSize(QSize(40,40));   //将图片大小设置成button的大小
        p->setFlat(true);               //去掉原来pushbutton的背景

        p->setParent(this);             //加入界面
    }
}
void gameplay::producePieceAI()
{
    //生成对方玩家方的棋子
    for(int i = 0;i<10;i++){
        Piece* p = new Piece();
        vPieces.push_back(p);
    }
    for(vector<Piece*>::iterator iter = vPieces.begin()+10;iter != vPieces.end();iter++)
    {
        Piece* p = *iter;
        p->setStatus(1);                //玩家为1
        p->setIcon(QIcon(":/res/chess2.png"));
        p->setIconSize(QSize(40,40));   //将图片大小设置成button的大小
        p->setFlat(true);               //去掉原来pushbutton的背景

        p->setParent(this);             //加入界面
    }
}
void gameplay::setPiece()
{
    //设置玩家棋子初始位置
    Piece* ptr;
    vector<Piece*>::iterator iter = this->vPieces.begin();
    /*
     * 设置棋子在界面中的位置
     * 设置Location数值
     * 更新flag（占位 1）
     */
    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[0][6].x,this->b->Matrix[0][6].y,40,40);
    ptr->setLocation(0,6);
    this->b->Matrix[0][6].flag=1;
    this->b->Matrix[0][6].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[1][6].x,this->b->Matrix[1][6].y,40,40);
    ptr->setLocation(1,6);
    this->b->Matrix[1][6].flag=1;
    this->b->Matrix[1][6].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[1][5].x,this->b->Matrix[1][5].y,40,40);
    ptr->setLocation(1,5);
    this->b->Matrix[1][5].flag=1;
    this->b->Matrix[1][5].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[2][5].x,this->b->Matrix[2][5].y,40,40);
    ptr->setLocation(2,5);
    this->b->Matrix[2][5].flag=1;
    this->b->Matrix[2][5].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[2][6].x,this->b->Matrix[2][6].y,40,40);
    ptr->setLocation(2,6);
    this->b->Matrix[2][6].flag=1;
    this->b->Matrix[2][6].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[2][7].x,this->b->Matrix[2][7].y,40,40);
    ptr->setLocation(2,7);
    this->b->Matrix[2][7].flag=1;
    this->b->Matrix[2][7].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[3][4].x,this->b->Matrix[3][4].y,40,40);
    ptr->setLocation(3,4);
    this->b->Matrix[3][4].flag=1;
    this->b->Matrix[3][4].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[3][5].x,this->b->Matrix[3][5].y,40,40);
    ptr->setLocation(3,5);
    this->b->Matrix[3][5].flag=1;
    this->b->Matrix[3][5].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[3][6].x,this->b->Matrix[3][6].y,40,40);
    ptr->setLocation(3,6);
    this->b->Matrix[3][6].flag=1;
    this->b->Matrix[3][6].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[3][7].x,this->b->Matrix[3][7].y,40,40);
    ptr->setLocation(3,7);
    this->b->Matrix[3][7].flag=1;
    this->b->Matrix[3][7].pieceLocate=ptr;

    for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
    {
        ptr=*iter;
        ptr->setParent(this);
    }
}
void gameplay::setPieceAI()
{
    //设置对方棋子初始位置
    Piece* ptr;//过渡指针
    vector<Piece*>::iterator iter = this->vPieces.begin()+10;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[16][6].x,this->b->Matrix[16][6].y,40,40);
    ptr->setLocation(16,6);
    this->b->Matrix[16][6].flag=1;
    this->b->Matrix[16][6].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[15][6].x,this->b->Matrix[15][6].y,40,40);
    ptr->setLocation(15,6);
    this->b->Matrix[15][6].flag=1;
    this->b->Matrix[15][6].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[15][5].x,this->b->Matrix[15][5].y,40,40);
    ptr->setLocation(15,5);
    this->b->Matrix[15][5].flag=1;
    this->b->Matrix[15][5].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[14][5].x,this->b->Matrix[14][5].y,40,40);
    ptr->setLocation(14,5);
    this->b->Matrix[14][5].flag=1;
    this->b->Matrix[14][5].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[14][6].x,this->b->Matrix[14][6].y,40,40);
    ptr->setLocation(14,6);
    this->b->Matrix[14][6].flag=1;
    this->b->Matrix[14][6].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[14][7].x,this->b->Matrix[14][7].y,40,40);
    ptr->setLocation(14,7);
    this->b->Matrix[14][7].flag=1;
    this->b->Matrix[14][7].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[13][4].x,this->b->Matrix[13][4].y,40,40);
    ptr->setLocation(13,4);
    this->b->Matrix[13][4].flag=1;
    this->b->Matrix[13][4].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[13][5].x,this->b->Matrix[13][5].y,40,40);
    ptr->setLocation(13,5);
    this->b->Matrix[13][5].flag=1;
    this->b->Matrix[13][5].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[13][6].x,this->b->Matrix[13][6].y,40,40);
    ptr->setLocation(13,6);
    this->b->Matrix[13][6].flag=1;
    this->b->Matrix[13][6].pieceLocate=ptr;
    iter++;

    ptr=*iter;
    ptr->setGeometry(this->b->Matrix[13][7].x,this->b->Matrix[13][7].y,40,40);
    ptr->setLocation(13,7);
    this->b->Matrix[13][7].flag=1;
    this->b->Matrix[13][7].pieceLocate=ptr;

    for(vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
    {
        ptr=*iter;
        ptr->setParent(this);

    }
}
void gameplay::processClick(int m,int n)
{
    //处理鼠标点击事件
    if(control==0){
        if(this->clickPieceNum==0)
        {
            this->clickPieceNum=1;
            this->select=this->b->Matrix[m][n].pieceLocate;
            this->select->setIcon(QIcon(":/res/chesss.png"));
        }
        else{

            this->clickPieceNum=0;
            this->select->setIcon(QIcon(":/res/chess.png"));
            this->select=NULL;
        }
    }

}
void gameplay::processClickAI(int m,int n)
{
    //处理鼠标点击事件
    if(control==1){
        if(this->clickPieceNum==0)
        {
            this->clickPieceNum=1;
            this->select=this->b->Matrix[m][n].pieceLocate;
            this->select->setIcon(QIcon(":/res/chess2s.png"));

        }
        else{
            this->clickPieceNum=0;
            this->select->setIcon(QIcon(":/res/chess2.png"));
            this->select=NULL;
        }
    }

}
void gameplay::modifyInformation(int x1,int y1,int x2,int y2)
{

    int m1=0;
    int n1=0;
    int n2=0;
    int m2=0;
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(b->Matrix[i][j].x==x1 && b->Matrix[i][j].y==y1){
                m1=i;
                n1=j;
            }
        }
    }
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(b->Matrix[i][j].x==x2&&b->Matrix[i][j].y==y2){
                m2=i;
                n2=j;
            }
        }
    }
    this->b->Matrix[m1][n1].flag=0;
    this->b->Matrix[m2][n2].pieceLocate=this->b->Matrix[m1][n1].pieceLocate;
    this->b->Matrix[m1][n1].pieceLocate=NULL;
    this->b->Matrix[m2][n2].flag=1;
    this->b->Matrix[m2][n2].pieceLocate->setLocation(m2,n2);
}
bool gameplay::isLegalMove(int x1,int y1,int x2,int y2){

    int m1=0;
    int n1=0;

    int m2=0;
    int n2=0;
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(b->Matrix[i][j].x==x1 && b->Matrix[i][j].y==y1){
                m1=i;
                n1=j;
            }
        }
    }
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<13;j++)
        {
            if(b->Matrix[i][j].x==x2&&b->Matrix[i][j].y==y2){
                m2=i;
                n2=j;
            }
        }
    }
    //将之前的图和链表初始化
    legal.clear();
    graph->init();
    /*
     * 向右跳
     * 1、跳的位置在棋盘内
     * 2、跳的位置没有棋子
     * 3、数组不越界
     */
    if(n1<12&&b->Matrix[m1][n1+1].x!=0&&b->Matrix[m1][n1+1].flag==0){
        legal.push_back(m1);
        legal.push_back(n1+1);
        graph->Matrix[m1*10+n1][m1*10+n1+1]=1;
        graph->Matrix[m1*10+n1+1][m1*10+n1]=1;



    }
    //向左跳
    if(n1>0&&b->Matrix[m1][n1-1].x!=0&&b->Matrix[m1][n1-1].flag==0){
        legal.push_back(m1);
        legal.push_back(n1-1);
        graph->Matrix[m1*10+n1][m1*10+n1-1]=1;
        graph->Matrix[m1*10+n1-1][m1*10+n1]=1;

    }
    //各个方向
    if(m1%2){

        if(m1>0&&b->Matrix[m1-1][n1].x!=0&&b->Matrix[m1-1][n1].flag==0){
            legal.push_back(m1-1);
            legal.push_back(n1);
            graph->Matrix[m1*10+n1][(m1-1)*10+n1]=1;
            graph->Matrix[(m1-1)*10+n1][m1*10+n1]=1;

        }
        if(m1>0&&n1<12&&b->Matrix[m1-1][n1+1].x!=0&&b->Matrix[m1-1][n1+1].flag==0){
            legal.push_back(m1-1);
            legal.push_back(n1+1);
            graph->Matrix[m1*10+n1][(m1-1)*10+n1+1]=1;
            graph->Matrix[(m1-1)*10+n1+1][m1*10+n1]=1;

        }
        if(m1<16&&b->Matrix[m1+1][n1].x!=0&&b->Matrix[m1+1][n1].flag==0){
            legal.push_back(m1+1);
            legal.push_back(n1);
            graph->Matrix[m1*10+n1][(m1+1)*10+n1]=1;
            graph->Matrix[(m1+1)*10+n1][m1*10+n1]=1;

        }
        if(m1<16&&n1<12&&b->Matrix[m1+1][n1+1].x!=0&&b->Matrix[m1+1][n1+1].flag==0){
            legal.push_back(m1+1);
            legal.push_back(n1+1);
            graph->Matrix[m1*10+n1][(m1+1)*10+n1+1]=1;
            graph->Matrix[(m1+1)*10+n1+1][m1*10+n1]=1;

        }
    }
    else{

        if(m1>0&&b->Matrix[m1-1][n1].x!=0&&b->Matrix[m1-1][n1].flag==0){
            legal.push_back(m1-1);
            legal.push_back(n1);
            graph->Matrix[m1*10+n1][(m1-1)*10+n1]=1;
            graph->Matrix[(m1-1)*10+n1][m1*10+n1]=1;

        }
        if(m1>0&&n1>0&&b->Matrix[m1-1][n1-1].x!=0&&b->Matrix[m1-1][n1-1].flag==0){
            legal.push_back(m1-1);
            legal.push_back(n1-1);
            graph->Matrix[m1*10+n1][(m1-1)*10+n1-1]=1;
            graph->Matrix[(m1-1)*10+n1-1][m1*10+n1]=1;

        }

        if(m1<16&&b->Matrix[m1+1][n1].x!=0&&b->Matrix[m1+1][n1].flag==0){
            legal.push_back(m1+1);
            legal.push_back(n1);
            graph->Matrix[m1*10+n1][(m1+1)*10+n1]=1;
            graph->Matrix[(m1+1)*10+n1][m1*10+n1]=1;

        }
        if(m1<16&&n1>0&&b->Matrix[m1+1][n1-1].x!=0&&b->Matrix[m1+1][n1-1].flag==0){
            legal.push_back(m1+1);
            legal.push_back(n1-1);
            graph->Matrix[m1*10+n1][(m1+1)*10+n1-1]=1;
            graph->Matrix[(m1+1)*10+n1-1][m1*10+n1]=1;

        }
    }
    jumpMove(m1,n1);

    way = graph->ShortestPath(m1*10+n1);

    int temp = m2*10+n2;
    int temp1, temp2;
    waylen = 0;
    while (temp!= -1)
    {
        flag[waylen++] = temp;
        temp1 = temp ;
        temp2 = way[temp1];
        temp = temp2;
    }
    for (int i = waylen-1; i >= 0; i--)
    {
        qDebug()<<flag[i] << "->";
    }
    for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){

        if(m2 == *it && n2 == *(it+1)){
            return true;
        }
    }

    return false;
}
void gameplay::jumpMove(int m1,int n1){
    //rep记录是否出现重复的点
    bool rep = false;
    /*
     * 向右跳
     * 1、跳的位置在棋盘内
     * 2、跳的位置没有棋子
     * 3、中间要有桥
     * 4、数组不越界
     */
    if(n1<11&&b->Matrix[m1][n1+2].x!=0&&b->Matrix[m1][n1+1].flag==1&&b->Matrix[m1][n1+2].flag==0){
        //如果和之前的重复了，就不用继续探索了，rep为true
        for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            if(*it==m1&&*(it+1)==n1+2){
                rep = true;
                break;
            }
            else{
                rep = false;
            }
        }
        //将相连的点加入图中
        graph->Matrix[m1*10+n1][m1*10+n1+2]=1;
        graph->Matrix[m1*10+n1+2][m1*10+n1]=1;

        //如果没重复，将可以走的点加入链表，递归调用JumpMove
        if(!rep){
            legal.push_back(m1);
            legal.push_back(n1+2);
            jumpMove(m1,n1+2);


        }
    }

    //向左跳
    if(n1>1&&b->Matrix[m1][n1-2].x!=0&&b->Matrix[m1][n1-1].flag==1&&b->Matrix[m1][n1-2].flag==0){
        for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            if(*it==m1&&*(it+1)==n1-2){
                rep = true;
                break;
            }
            else{
                rep = false;
            }
        }
        graph->Matrix[m1*10+n1][m1*10+n1-2]=1;
        graph->Matrix[m1*10+n1-2][m1*10+n1]=1;

        if(!rep){

            legal.push_back(m1);
            legal.push_back(n1-2);
            jumpMove(m1,n1-2);
        }
    }
    //单数行
    if(m1%2){
        //左上方
        if(m1>1&&n1>0&&b->Matrix[m1-2][n1-1].x!=0&&b->Matrix[m1-1][n1].flag==1&&b->Matrix[m1-2][n1-1].flag==0){
            for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
                if(*it==m1-2&&*(it+1)==n1+1){
                    rep = true;
                    break;
                }
                else{
                    rep = false;
                }
            }
            graph->Matrix[m1*10+n1][(m1-2)*10+n1-1]=1;
            graph->Matrix[(m1-2)*10+n1-1][m1*10+n1]=1;

            if(!rep){

                legal.push_back(m1-2);
                legal.push_back(n1-1);
                jumpMove(m1-2,n1-1);

            }
        }

        //右上方
        if(m1>1&&n1<12&&b->Matrix[m1-2][n1+1].x!=0&&b->Matrix[m1-1][n1+1].flag==1&&b->Matrix[m1-2][n1+1].flag==0){
            for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
                if(*it==m1-2&&*(it+1)==n1+1){
                    rep = true;
                    break;
                }
                else{
                    rep = false;
                }
            }
            graph->Matrix[m1*10+n1][(m1-2)*10+n1+1]=1;
            graph->Matrix[(m1-2)*10+n1+1][m1*10+n1]=1;

            if(!rep){

                legal.push_back(m1-2);
                legal.push_back(n1+1);

                jumpMove(m1-2,n1+1);

            }
        }
        //左下方
        if(m1<15&&n1>0&&b->Matrix[m1+2][n1-1].x!=0&&b->Matrix[m1+1][n1].flag==1&&b->Matrix[m1+2][n1-1].flag==0){
            for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
                if(*it==m1+2&&*(it+1)==n1-1){
                    rep = true;
                    break;
                }
                else{
                    rep = false;
                }
            }
            graph->Matrix[m1*10+n1][(m1+2)*10+n1-1]=1;
            graph->Matrix[(m1+2)*10+n1-1][m1*10+n1]=1;

            if(!rep){

                legal.push_back(m1+2);
                legal.push_back(n1-1);

                jumpMove(m1+2,n1-1);

            }
        }
        //右下方
        if(m1<15&&n1<12&&b->Matrix[m1+2][n1+1].x!=0&&b->Matrix[m1+1][n1+1].flag==1&&b->Matrix[m1+2][n1+1].flag==0){
            for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
                if(*it==m1+2&&*(it+1)==n1+1){
                    rep = true;
                    break;
                }
                else{
                    rep = false;
                }
            }
            graph->Matrix[m1*10+n1][(m1+2)*10+n1+1]=1;
            graph->Matrix[(m1+2)*10+n1+1][m1*10+n1]=1;

            if(!rep){

                legal.push_back(m1+2);
                legal.push_back(n1+1);
                jumpMove(m1+2,n1+1);

            }
        }


    }
    //双数行
    else{
        //右上方
        if(m1>1&&n1<12&&b->Matrix[m1-2][n1+1].x!=0&&b->Matrix[m1-1][n1].flag==1&&b->Matrix[m1-2][n1+1].flag==0){
            for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
                if(*it==m1-2&&*(it+1)==n1+1){
                    rep = true;
                    break;
                }
                else{
                    rep = false;
                }
            }
            graph->Matrix[m1*10+n1][(m1-2)*10+n1+1]=1;
            graph->Matrix[(m1-2)*10+n1+1][m1*10+n1]=1;

            if(!rep){

                legal.push_back(m1-2);
                legal.push_back(n1+1);
                jumpMove(m1-2,n1+1);

            }
        }

        //左上方
        if(m1>1&&n1>0&&b->Matrix[m1-2][n1-1].x!=0&&b->Matrix[m1-1][n1-1].flag==1&&b->Matrix[m1-2][n1-1].flag==0){
            for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
                if(*it==m1-2&&*(it+1)==n1-1){
                    rep = true;
                    break;
                }
                else{
                    rep = false;
                }
            }
            graph->Matrix[m1*10+n1][(m1-2)*10+n1-1]=1;
            graph->Matrix[(m1-2)*10+n1-1][m1*10+n1]=1;

            if(!rep){

                legal.push_back(m1-2);
                legal.push_back(n1-1);
                jumpMove(m1-2,n1-1);

            }
        }
        //右下方
        if(m1<15&&n1<12&&b->Matrix[m1+2][n1+1].x!=0&&b->Matrix[m1+1][n1].flag==1&&b->Matrix[m1+2][n1+1].flag==0){
            for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
                if(*it==m1+2&&*(it+1)==n1+1){
                    rep = true;
                    break;
                }
                else{
                    rep = false;
                }
            }
            graph->Matrix[m1*10+n1][(m1+2)*10+n1+1]=1;
            graph->Matrix[(m1+2)*10+n1+1][m1*10+n1]=1;

            if(!rep){

                legal.push_back(m1+2);
                legal.push_back(n1+1);
                jumpMove(m1+2,n1+1);

            }
        }
        //左下方
        if(m1<15&&n1>0&&b->Matrix[m1+2][n1-1].x!=0&&b->Matrix[m1+1][n1-1].flag==1&&b->Matrix[m1+2][n1-1].flag==0){
            for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
                if(*it==m1+2&&*(it+1)==n1-1){
                    rep = true;
                    break;
                }
                else{
                    rep = false;
                }
            }
            graph->Matrix[m1*10+n1][(m1+2)*10+n1-1]=1;
            graph->Matrix[(m1+2)*10+n1-1][m1*10+n1]=1;


            if(!rep){

                legal.push_back(m1+2);
                legal.push_back(n1-1);
                jumpMove(m1+2,n1-1);

            }
        }


    }


}
void gameplay::TimeSlot()
{
    this->totaltime++;
    int hour = 0;
    int minute = 0;
    int second = 0;
    hour = totaltime / 3600;
    minute = (totaltime - 3600*hour) / 60;
    second = totaltime % 60;
    this->ui->textBrowser_3->setText(QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second));
    this->counttime--;
    if(counttime>=0){
        this->ui->label_7->setText(QString::number(counttime, 10));
    }
    else{
        if(control == 0){
            falsetime++;
            counttime = 11;
            if(falsetime == 1){
                this->ui->label_8->setText("玩家已超时一次");
            }
            else if(falsetime == 2){
                this->ui->label_8->setText("玩家已超时两次");
            }
            else if(falsetime == 3){
                this->ui->label_8->setText("玩家已超时三次");
                gameover* over=new gameover();
                over->show();
                over->setWindowTitle("游戏结束");
                over->set("红棋获胜",QString::number(AIstep->num, 10),totaltime);
                this->close() ;
            }
        }
        else{
            falsetime2++;
            counttime = 11;
            if(falsetime2 == 1){
                this->ui->label_12->setText("玩家已超时一次");
            }
            else if(falsetime2 == 2){
                this->ui->label_12->setText("玩家已超时两次");
            }
            else if(falsetime2 == 3){
                this->ui->label_12->setText("玩家已超时三次");
                gameover* over=new gameover();
                over->show();
                over->setWindowTitle("游戏结束");
                over->set("黑棋获胜",QString::number(allstep->num, 10),totaltime);
                this->close() ;
            }
        }
    }
}
void gameplay::judgewinA(){
    int count=0;
    int line =0;
    int col=0;

    for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
    {
        Piece* ptr=new Piece();
        ptr=*iter;
        line = ptr->getLine();
        col = ptr->getCol();
        if((line==16&&col==6)||(line==15&&col==5)||(line==15&&col==6)||(line==14&&col==5)||
                (line==14&&col==6)||(line==14&&col==7)||(line==13&&col==4)||(line==13&&col==5)||(line==13&&col==6)||(line==13&&col==7)){
            count++;
        }
    }
    if(count==10){

        //先手完成标志
        judgeA=1;

    }

}
void gameplay::judgewinB(){
    int count=0;
    int line =0;
    int col=0;
    bool one = false;
    //玩家后手B，仅剩一步棋
    if(judgeA==1){
        one = true;
    }
    for(vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
    {
        Piece* ptr=new Piece();
        ptr=*iter;
        line = ptr->getLine();
        col = ptr->getCol();
        if((line==0&&col==6)||(line==1&&col==5)||(line==1&&col==6)||(line==2&&col==5)||
                (line==2&&col==6)||(line==2&&col==7)||(line==3&&col==4)||(line==3&&col==5)||(line==3&&col==6)||(line==3&&col==7)){
            count++;
        }
    }
    if(count==10){
        one = false;
        //后手先完成，直接胜利
        if(judgeA==0){
            gameover* over=new gameover();
            over->show();
            over->setWindowTitle("游戏结束");
            over->set("红棋获胜",QString::number(allstep->num, 10),totaltime);
            this->close();;
        }
        //在最后一步到位，平局
        if(judgeA==1){
            gameover* over=new gameover();
            over->show();
            over->setWindowTitle("游戏结束");
            over->set("平局",QString::number(allstep->num, 10),totaltime);
            this->close() ;
            qDebug()<<"dual";
        }

    }
    //最后一步未完成，失败
    if(one){
        gameover* over=new gameover();
        over->show();
        over->setWindowTitle("游戏结束");
        over->set("黑棋获胜",QString::number(allstep->num, 10),totaltime);
        this->close() ;
    }
}

void gameplay::sleep(){
    //使玩家看清棋子运行轨迹
    //延时效果
    QTime t;
    t.start();
    while(t.elapsed()<300)
        QCoreApplication::processEvents();
}
void gameplay::moveProcess(){
    msTimer->stop();
    //按照flag数组中的顺序，依次走过图中的点
    for (int i = waylen-1; i >= 0; i--)
    {
        int line = flag[i]/10;
        int col = flag[i]%10;
        this->select->move(b->Matrix[line][col].x,b->Matrix[line][col].y);
        this->sleep();
    }
    msTimer->start(1000);
}

void gameplay::on_pushButton_3_clicked()
{
    msTimer->stop();
    this->close();
    MainWindow* w = new MainWindow();
    w->show();
}

void gameplay::on_pushButton_clicked()
{
    if(control==1){
    //恢复玩家上一步的走棋
    if(Change* ch = allstep->pop()){
        for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
        {
            Piece* ptr=new Piece();
            ptr=*iter;
            if(ptr->x()==ch->getnewX()&&ptr->y()==ch->getnewY()){
                ptr->move(ch->getlastX(),ch->getlastY());
                modifyInformation(ch->getnewX(),ch->getnewY(),ch->getlastX(),ch->getlastY());

            }
        }
        //悔棋重置标志位
        judgeA =0;
        counttime=11;
    }
    ui->textBrowser->setText(QString::number(allstep->num, 10));
    control = 0;
    }
}

void gameplay::on_pushButton_2_clicked()
{
    if(control==0&&AIstep->num!=0){
        if(Change* aich = AIstep->pop()){
            for(vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
            {
                Piece* ptr=new Piece();
                ptr=*iter;
                if(ptr->x()==aich->getnewX()&&ptr->y()==aich->getnewY()){
                    ptr->move(aich->getlastX(),aich->getlastY());
                    modifyInformation(aich->getnewX(),aich->getnewY(),aich->getlastX(),aich->getlastY());

                }
            }
            counttime=11;
        }
        ui->textBrowser_2->setText(QString::number(AIstep->num, 10));
        control = 1;

    }

}

void gameplay::on_pushButton_4_clicked()
{
    msTimer->stop();
}

void gameplay::on_pushButton_5_clicked()
{
    msTimer->start(1000);
}
