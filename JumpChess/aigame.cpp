#include "aigame.h"
#include "ui_aigame.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <vector>
#include <QDebug>
#include <QTime>
#include "boardmatrix.h"
#include "graph.h"
#include "mystack.h"
#include "choose.h"
#include "mainwindow.h"
#include "gameover.h"

extern int playerState;
extern int AIState;

using namespace std;
AIgame::AIgame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AIgame)
{

    ps = playerState;
    int as = AIState;
    //AI对战界面
    ui->setupUi(this);
    ui->textBrowser->setText("0");
    //加载图标
    this->setWindowIcon(QIcon(":/res/chessico.png"));
    this->setWindowTitle("AI对战");

    /*
     * 初始化各项数据
     * clickPieceNum（点击次数）
     * control（控制权）
     * range（AI棋局分布标识值）
     * select（选择的当前棋子）
     */
    this->totaltime = 0;
    this->counttime = 11;
    falsetime = 0;
    this->msTimer=new QTimer(this);
    msTimer->start(1000);
    connect(msTimer,SIGNAL(timeout()),this,SLOT(TimeSlot()));

    this->clickPieceNum = 0;
    if(ps==0)
    {
        ui->label_4->setText("先手");
        ui->label_10->setText("玩家");
        this->control = 0;
    }
    this->range = 0;
    this->select = NULL;
    judgeAI = 0;
    judgeplay = 0;

    //创建玩家棋子
    this->producePiece();
    //创建AI棋子
    this->producePieceAI();
    //创建棋盘区域
    this->produceRectF();
    //构建一个新的图，并进行初始化
    graph = new Graph();
    graph->init();
    //设置游戏模式
    setState(as);

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

    if(ps==1)
        {
            ui->label_4->setText("后手");
            ui->label_10->setText("电脑");
            //AI玩法
            buildPath(AIJudge());
            //变换图片，更新指针
            this->clickPieceNum=0;
            this->select=NULL;
            control=0;
        }

}

AIgame::~AIgame()
{
    delete ui;
}
void AIgame::setState(int as)
{

    if(as==0)
    {
        ui->label_5->setText("进攻型");
        attck = 3;
        defence = 1;
        fornest = 1;
    }
    else if(as==1)
    {
        ui->label_5->setText("防守型");
        attck = 1;
        defence = 3;
        fornest = 1;
    }
    else if(as==2)
    {
        ui->label_5->setText("均衡型");
        attck = 1;
        defence = 1;
        fornest = 1;
    }
}

void AIgame::paintEvent(QPaintEvent *event)
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
void AIgame::mousePressEvent(QMouseEvent* event)
{

    if(event->button()==Qt::LeftButton)
    {
        //玩家回合点击鼠标有效
        if(control==0){
            for(vector<QRectF*>::iterator iter = this->vRectF.begin();iter != this->vRectF.end();iter++)
            {
                QRectF* ptr =*iter;
                if(ptr->contains( mapFromGlobal(QCursor::pos()))==true)
                {
                    //鼠标落在矩形块中
                    if(this->select!=NULL){

                            if(isLegalMove(this->select->x(),this->select->y(),ptr->x(),ptr->y()))
                            {

                                control=1;
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
                                Shiftmodify(this->select->x(),this->select->y(),ptr->x(),ptr->y());
                                // 走棋步骤
                                moveProcess();
                                //变换图片，更新指针
                                this->clickPieceNum=0;
                                this->select->setIcon(QIcon(":/res/chess.png"));
                                this->select=NULL;
                                //判断输赢
                                judgeplaywin();
                                ui->label_10->setText("电脑");

                                QTime t;
                                t.start();
                                while(t.elapsed()<800)
                                    QCoreApplication::processEvents();
                            }
                            else{
                                //变换图片，更新指针
                                this->clickPieceNum=0;
                                this->select->setIcon(QIcon(":/res/chess.png"));
                                this->select=NULL;
                            }

                        if(control==1){
                            //AI玩法
                            buildPath(AIJudge());
                            //变换图片，更新指针
                            this->clickPieceNum=0;
                            this->select=NULL;
                            //判断输赢
                            judgeAIwin();
                            control=0;
                            ui->label_10->setText("玩家");
                            counttime = 11;

                        }
                    }
                }


            }
        }

    }



}
void AIgame::produceRectF()
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
void AIgame::producePiece()
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
void AIgame::producePieceAI()
{
    //生成AI方的棋子
    for(int i = 0;i<10;i++){
        Piece* p = new Piece();
        vPieces.push_back(p);
    }
    for(vector<Piece*>::iterator iter = vPieces.begin()+10;iter != vPieces.end();iter++)
    {
        Piece* p = *iter;
        p->setStatus(1);              //电脑为1

        p->setIcon(QIcon(":/res/chess2.png"));
        p->setIconSize(QSize(40,40));//将图片大小设置成button的大小
        p->setFlat(true);            //去掉原来pushbutton的背景

        p->setParent(this);          //加入界面
    }
}
void AIgame::setPiece()
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

    for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end();iter++)
    {
        ptr=*iter;
        ptr->setParent(this);
    }
}
void AIgame::setPieceAI()
{
    //设置AI棋子初始位置
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

    for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end();iter++)
    {
        ptr=*iter;
        ptr->setParent(this);

    }


}
void AIgame::processClick(int m,int n)
{
    //处理鼠标点击棋子事件
    if(control==0){
        //如果是第一次点击，选中当前棋子并更改图片
        if(this->clickPieceNum==0)
        {
            this->clickPieceNum=1;
            this->select=this->b->Matrix[m][n].pieceLocate;
            this->select->setIcon(QIcon(":/res/chesss.png"));

        }
        //如果不是，取消选中并更改图片
        else{
            this->clickPieceNum=0;
            this->select->setIcon(QIcon(":/res/chess.png"));
            this->select=NULL;

        }
    }
}

void AIgame::Shiftmodify(int x1,int y1,int x2,int y2)
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
    modify(m1,n1,m2,n2);
}

void AIgame::modify(int m1,int n1,int m2,int n2)
{
    //将改变的棋子位置进行设置
    this->b->Matrix[m1][n1].flag=0;
    this->b->Matrix[m2][n2].pieceLocate=this->b->Matrix[m1][n1].pieceLocate;
    this->b->Matrix[m1][n1].pieceLocate=NULL;
    this->b->Matrix[m2][n2].flag=1;
    this->b->Matrix[m2][n2].pieceLocate->setLocation(m2,n2);
}
bool AIgame::isLegalMove(int x1,int y1,int x2,int y2){

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

    getLegalMove(m1,n1);
//    for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
//        qDebug()<<*it<<*(it+1);
//    }

    //求出最短路径
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
void AIgame::jumpMove(int m1,int n1){
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
//判断玩家是否胜利
void AIgame::judgeplaywin(){
    int count=0;
    int line =0;
    int col=0;
    bool one = false;
    //玩家后手，仅剩一步棋
    if(playerState==1&&judgeAI==1){
        one = true;
    }
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
        one = false;
        //后手先完成，直接胜利
        if(playerState==1&&judgeAI==0){
            msTimer->stop();
            gameover* over=new gameover();
            over->show();
            over->setWindowTitle("游戏结束");
            over->set("玩家获胜",QString::number(allstep->num, 10),totaltime);
            this->close();
            qDebug()<<"Awin";
        }
        //在最后一步到位，平局
        if(playerState==1&&judgeAI==1){
            msTimer->stop();
            gameover* over=new gameover();
            over->show();
            over->setWindowTitle("游戏结束");
            over->set("平局",QString::number(allstep->num, 10),totaltime);
            this->close() ;
            qDebug()<<"dual";
        }
        //先手完成标志
        if(playerState==0){
            judgeplay=1;
        }
    }
    //最后一步未完成，失败
    if(one){
        msTimer->stop();
        gameover* over=new gameover();
        over->show();
        over->setWindowTitle("游戏结束");
        over->set("电脑获胜",QString::number(allstep->num, 10),totaltime);
        this->close() ;
        qDebug()<<"Bwin";
    }

}

void AIgame::judgeAIwin(){
    int count=0;
    int line =0;
    int col=0;
    bool two = false;
    //玩家先手完成，电脑仅剩一步
    if(playerState==0&&judgeplay==1){
        two = true;
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
        two = false;
        //后手先完成，胜利
        if(playerState==0&&judgeplay==0){
            msTimer->stop();
            gameover* over=new gameover();
            over->show();
            over->setWindowTitle("游戏结束");
            over->set("电脑获胜",QString::number(allstep->num, 10),totaltime);
            this->close();
            qDebug()<<"Bwin";
        }
        //最后一步完成，平局
        if(playerState==0&&judgeplay==1){
            msTimer->stop();
            gameover* over=new gameover();
            over->show();
            over->setWindowTitle("游戏结束");
            over->set("平局",QString::number(allstep->num, 10),totaltime);
            this->close();
            qDebug()<<"dual";
        }
        //电脑先手完成标志
        if(playerState==1){
            judgeAI=1;
        }
    }
    //最后一步未完成，失败
    if(two){
        msTimer->stop();
        gameover* over=new gameover();
        over->show();
        over->setWindowTitle("游戏结束");
        over->set("玩家获胜",QString::number(allstep->num, 10),totaltime);
        this->close();
        qDebug()<<"Awin";
    }

}
void AIgame::sleep(){
    //使玩家看清棋子运行轨迹
    //延时效果
    QTime t;
    t.start();
    while(t.elapsed()<300)
        QCoreApplication::processEvents();
}
void AIgame::moveProcess(){
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
void AIgame::getLegalMove(int m1,int n1){
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

}

int AIgame::AIJudge(){
    //初始化score作为判断标准
    int score[10];
    for(int i=0;i<10;i++){
        score[i]=0;
    }
    //先对当前玩家能走的最大权值算出来
    OhumanJump();

    //初始化各个数值
    int x=0;
    int y=0;
    int m1=0;
    int n1=0;
    int mmax=0;
    int nmax=0;
    int number = 0;
    int Opower = 0;
    int Npower = 0;
    Olongjump.clear();
    int len = 0;

    for(vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
    {
        //遍历全部棋子
        Piece* ptr=new Piece();
        ptr=*iter;
        len = 0;
        x = ptr->getLine();
        y = ptr->getCol();
        //计算当前快要完成的棋子个数
        if(x<6){
            number++;
        }
        Opower = b->AIpower[x][y];
        getLegalMove(x,y);

        for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            //遍历每一个可以到达的点
            m1 = *it;
            n1 = *(it+1);
            Npower =b->AIpower[m1][n1];

            if(Npower-Opower>len){
                //记录最大权值的位置
                len = Npower-Opower;
                mmax = m1;
                nmax = n1;
            }
        }
        //如果快完成的棋子多了，就增加落后棋子的权重，保证整体性
        if(x>6){
            if(x>10){
                if(x>13){
                    len = len+80*range;
                }
                else{
                    len = len+50*range;
                }
            }
            else{
                len = len+5*range;
            }
        }
        Olongjump.push_back(len);
        //假设走到了最大权值的位置
        modify(x,y,mmax,nmax);
        //计算假设的下一步玩家能走的最大权值
        //下一步AI能走的最大权值
        humanJump();
        longJump();
        //交换回来
        modify(mmax,nmax,x,y);

    }
    range = number;
    //qDebug()<<range;
    len = 0;
    int p = 0;

    if(range>5&&range<8){
        for(vector<int>::iterator it = this->longjump.begin();it !=this->longjump.end();it++)
        {
            score[p] = score[p]+ (*it)*fornest;
            p++;
        }
        p=0;
        for(vector<int>::iterator it = this->Olongjump.begin();it !=this->Olongjump.end();it++)
        {
            score[p] = score[p] + (*it)*attck;
            p++;
        }
        p=0;
    }

    if(range==0||range>=8){
        for(vector<int>::iterator it = this->longjump.begin();it !=this->longjump.end();it++)
        {
            score[p] = score[p]+(*it)*0;
            p++;
        }
        p=0;
        for(vector<int>::iterator it = this->Olongjump.begin();it !=this->Olongjump.end();it++)
        {
            score[p] = score[p] + (*it)*1;
            p++;
        }

    }
    else{
        for(vector<int>::iterator it = this->longjump.begin();it !=this->longjump.end();it++)
        {
            score[p] = score[p]+(*it)*fornest;
            p++;
        }
        p=0;
        for(vector<int>::iterator it = this->Olongjump.begin();it !=this->Olongjump.end();it++)
        {
            score[p] = score[p] + (*it)*attck;
            p++;
        }
        p=0;
        for(vector<int>::iterator it = this->opjump.begin();it !=this->opjump.end();it++)
        {
            qDebug()<<*it;
            score[p] = score[p] - (*it)*defence;
            p++;
        }
        p=0;
        for(vector<int>::iterator it = this->Oopjump.begin();it !=this->Oopjump.end();it++)
        {
            qDebug()<<*it;
            score[p] = score[p] + (*it)*defence;
            p++;
        }
    }
    //计算出最合理的移动棋子
    int maxmum = score[0];
    int fg = 0;
    for(int i=0;i<10;i++){
        if(score[i]>maxmum){
            maxmum = score[i];
            fg = i;
        }
    }
    qDebug()<<fg;
    return fg;

}
//创建路径函数
void AIgame::buildPath(int pnumber){
    //数据初始化
    int x=0;
    int y=0;
    int m1=0;
    int n1=0;
    int mmax=0;
    int nmax=0;
    int Opower = 0;
    int Npower = 0;
    int len = 0;
    Olongjump.clear();
    //选定指定棋子
    vector<Piece*>::iterator iter = this->vPieces.begin()+10+pnumber;
    Piece* ptr = new Piece();
    ptr = *iter;
    this->select = ptr;
    //计算该棋子的走到的最大权值位置
    len = -100;
    x = ptr->getLine();
    y = ptr->getCol();
    //qDebug()<<x<<y;
    Opower = b->AIpower[x][y];
    getLegalMove(x,y);
    vector<int>::iterator it = legal.begin();
    mmax = *it;
    nmax = *(it+1);
    for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
        m1 = *it;
        n1 = *(it+1);
        Npower =b->AIpower[m1][n1];
        if(Npower-Opower>len){
            len = Npower-Opower;
            mmax = m1;
            nmax = n1;
        }
    }

    //新位置入栈
    Change* aich = new Change();
    aich->setlastX(b->Matrix[x][y].x);
    aich->setlastY(b->Matrix[x][y].y);
    aich->setnewX(b->Matrix[mmax][nmax].x);
    aich->setnewY(b->Matrix[mmax][nmax].y);

    AIstep->push(aich);
    //qDebug()<<mmax<<nmax;

    //求出最短路径，更新数据并且移动
    way = graph->ShortestPath(x*10+y);
    int temp = mmax*10+nmax;
    int temp1, temp2;
    waylen = 0;
    while (temp!= -1)
    {
        flag[waylen++] = temp;
        temp1 = temp ;
        temp2 = way[temp1];
        temp = temp2;
    }
    modify(x,y,mmax,nmax);
    moveProcess();

}
//AI下一步每一个棋子能到达的最大权值
void AIgame::longJump(){
    //初始化各个数值
    int x=0;
    int y=0;
    int m1=0;
    int n1=0;
    int Opower = 0;
    int Npower = 0;
    longjump.clear();
    int len = 0;
    for(vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
    {
        //遍历全部棋子
        Piece* ptr=new Piece();
        ptr=*iter;
        len = 0;
        x = ptr->getLine();
        y = ptr->getCol();
        //qDebug()<<x<<y;
        Opower = b->AIpower[x][y];
        getLegalMove(x,y);
        for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            //遍历每一个可以到达的点
            m1 = *it;
            n1 = *(it+1);
            Npower =b->AIpower[m1][n1];

            if(Npower-Opower>len){
                len = Npower-Opower;
            }
        }
        //将该棋子的最大权值进行记录
        longjump.push_back(len);

    }

}
//玩家下一步每一个棋子能到达的最大权值
void AIgame::humanJump(){
    //初始化各个数值
    int x=0;
    int y=0;
    int m1=0;
    int n1=0;
    int Opower = 0;
    int Npower = 0;
    opjump.clear();
    int len = 0;
    for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
    {
        //遍历全部棋子
        Piece* ptr=new Piece();
        ptr=*iter;
        len = 0;
        x = ptr->getLine();
        y = ptr->getCol();
        //qDebug()<<x<<y;
        Opower = b->humanpower[x][y];
        getLegalMove(x,y);
        for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            //遍历每一个可以到达的点
            m1 = *it;
            n1 = *(it+1);
            Npower =b->humanpower[m1][n1];

            if(Npower-Opower>len){
                len = Npower-Opower;
            }
        }
        //将该棋子的最大权值进行记录
        opjump.push_back(len);

    }

}
//玩家当前每一个棋子能到达的最大权值
void AIgame::OhumanJump(){
    //初始化各个数值
    int x=0;
    int y=0;
    int m1=0;
    int n1=0;
    int Opower = 0;
    int Npower = 0;
    Oopjump.clear();
    int len = 0;
    for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
    {
        //遍历全部棋子
        Piece* ptr=new Piece();
        ptr=*iter;
        len = 0;
        x = ptr->getLine();
        y = ptr->getCol();
        //qDebug()<<x<<y;
        Opower = b->humanpower[x][y];
        getLegalMove(x,y);
        for(vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            //遍历每一个可以到达的点
            m1 = *it;
            n1 = *(it+1);
            Npower =b->humanpower[m1][n1];

            if(Npower-Opower>len){
                len = Npower-Opower;
            }
        }
        //将该棋子的最大权值进行记录
        Oopjump.push_back(len);

    }


}
void AIgame::TimeSlot()
{
    this->totaltime++;
    int hour = 0;
    int minute = 0;
    int second = 0;
    hour = totaltime / 3600;
    minute = (totaltime - 3600*hour) / 60;
    second = totaltime % 60;
    this->ui->textBrowser_2->setText(QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second));
    this->counttime--;
    if(counttime>=0){
        this->ui->label_7->setText(QString::number(counttime, 10));
    }
    else{
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
            msTimer->stop();
            gameover* over=new gameover();
            over->show();
            over->setWindowTitle("游戏结束");
            over->set("电脑获胜",QString::number(allstep->num, 10),totaltime);
            this->close() ;
        }
    }
}
void AIgame::on_pushButton_clicked()
{

    if(control==0){

        //恢复玩家上一步的走棋
        if(Change* ch = allstep->pop()){
            for(vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
            {
                Piece* ptr=new Piece();
                ptr=*iter;
                if(ptr->x()==ch->getnewX()&&ptr->y()==ch->getnewY()){
                    ptr->move(ch->getlastX(),ch->getlastY());
                    Shiftmodify(ch->getnewX(),ch->getnewY(),ch->getlastX(),ch->getlastY());

                }
            }
            //悔棋重置标志位
            judgeplay =0;
            counttime=11;

        }
        ui->textBrowser->setText(QString::number(allstep->num, 10));
        if(ps==0){
            if(AIstep->num!=0){
                //恢复AI上一步的走棋
                if(Change* aich = AIstep->pop()){
                    for(vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
                    {
                        Piece* ptr=new Piece();
                        ptr=*iter;
                        if(ptr->x()==aich->getnewX()&&ptr->y()==aich->getnewY()){
                            ptr->move(aich->getlastX(),aich->getlastY());
                            Shiftmodify(aich->getnewX(),aich->getnewY(),aich->getlastX(),aich->getlastY());

                        }
                    }
                    judgeAI =0;
                }
            }
        }
        else{
            if(AIstep->num!=1){
                //恢复AI上一步的走棋
                if(Change* aich = AIstep->pop()){
                    for(vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
                    {
                        Piece* ptr=new Piece();
                        ptr=*iter;
                        if(ptr->x()==aich->getnewX()&&ptr->y()==aich->getnewY()){
                            ptr->move(aich->getlastX(),aich->getlastY());
                            Shiftmodify(aich->getnewX(),aich->getnewY(),aich->getlastX(),aich->getlastY());

                        }
                    }
                    judgeAI =0;
                }
            }
        }

    }



}

void AIgame::on_pushButton_2_clicked()
{
    msTimer->stop();
    this->close();
    MainWindow* w = new MainWindow();
    w->show();
}

void AIgame::on_pushButton_3_clicked()
{
    msTimer->stop();
}

void AIgame::on_pushButton_4_clicked()
{
    msTimer->start(500);
}
