#include "playwindow.h"
#include "ui_playwindow.h"
#include "mainwindow.h"
#include <vector>
#include <QWidget>
#include "board.h"
#include <vector>
#include <QRectF>
#include <QTimer>
#include <QTime>
#include <QImage>
#include "piece.h"
#include <math.h>
#include <QMouseEvent>
#include <gameover.h>

playwindow::playwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::playwindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\icon.png"));
    //init
    this->clickPieceNum = 0;
    this->control = 3;  //0是僵尸方 3是植物方
    this->select = NULL;    //选择当前棋子
    this->judge = -1;
    ui->turn->setText("Plants Turn");   //植物先手

    //create pieces
    this->producePiece3();  //创建植物棋子
    this->producePiece0();
    this->produceRectF();

    //创建两个新的栈（用于保存棋子的每一步）
    allstep3 = new mystack();
    allstep0 = new mystack();


    //初始化board
    boardMatrix = new board();
    boardMatrix->init();
    boardMatrix->initNearby();

    //为每一个坐标添加正方形点击区域
    QRectF* qr;
    int k = 0;
    for (int i = 0; i<121; i++) {
        qr = this->vRectF.at(k++);
        qr->setRect(this->boardMatrix->Board2XY[i].x_p, this->boardMatrix->Board2XY[i].y_p, 40, 40);
    }

    //设置玩家的棋子
    this->setPiece3();
    this->setPiece0();

    //为每一个棋子（按钮）的点击设置槽函数
    for(std::vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
    {
        Piece* ptr = *iter;
        connect(ptr,SIGNAL(pieceInfo(int,int)),this,SLOT(processClick0(int,int)));
    }
    for(std::vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
    {
        Piece* ptr = *iter;
        connect(ptr,SIGNAL(pieceInfo(int,int)),this,SLOT(processClick3(int,int)));
    }

}

playwindow::~playwindow()
{
    delete ui;
}

void playwindow::setPiece3(){   //植物方
    Piece* p;
    std::vector<Piece*>::iterator iter = this->vPieces.begin();
    //初始化棋子在界面中的位置
    p = *iter;
    p->setGeometry(288,578,40,40); // (0,0) 为屏幕的左上角
    p->setLocation(4,13);
    this->boardMatrix->Board2XY[111].flag=1;
    this->boardMatrix->Board2XY[111].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(336,578,40,40);
    p->setLocation(5,13);
    this->boardMatrix->Board2XY[112].flag=1;
    this->boardMatrix->Board2XY[112].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(384,578,40,40);
    p->setLocation(6,13);
    this->boardMatrix->Board2XY[113].flag=1;
    this->boardMatrix->Board2XY[113].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(432,578,40,40);
    p->setLocation(7,13);
    this->boardMatrix->Board2XY[114].flag=1;
    this->boardMatrix->Board2XY[114].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(312,620,40,40);
    p->setLocation(4,14);
    this->boardMatrix->Board2XY[115].flag=1;
    this->boardMatrix->Board2XY[115].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(360,620,40,40);
    p->setLocation(5,14);
    this->boardMatrix->Board2XY[116].flag=1;
    this->boardMatrix->Board2XY[116].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(408,620,40,40);
    p->setLocation(6,14);
    this->boardMatrix->Board2XY[117].flag=1;
    this->boardMatrix->Board2XY[117].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(336,662,40,40);
    p->setLocation(4,15);
    this->boardMatrix->Board2XY[118].flag=1;
    this->boardMatrix->Board2XY[118].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(384,662,40,40);
    p->setLocation(4,15);
    this->boardMatrix->Board2XY[119].flag=1;
    this->boardMatrix->Board2XY[119].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(360,704,40,40);
    p->setLocation(4,16);
    this->boardMatrix->Board2XY[120].flag=1;
    this->boardMatrix->Board2XY[120].pieceLocate=p;

    //共10个棋子
    for(std::vector<Piece*>::iterator iter = this->vPieces.begin();iter !=this->vPieces.end()-10;iter++)
    {
        p=*iter;
        p->setParent(this);
    }
}

void playwindow::setPiece0(){   //僵尸方
    Piece* p;
    std::vector<Piece*>::iterator iter = this->vPieces.begin()+10;
    //初始化棋子在界面中的位置
    p = *iter;
    p->setGeometry(360,42,40,40); // (0,0) 为屏幕的左上角
    p->setLocation(12,0);
    this->boardMatrix->Board2XY[0].flag=1;
    this->boardMatrix->Board2XY[0].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(336,84,40,40);
    p->setLocation(11,1);
    this->boardMatrix->Board2XY[1].flag=1;
    this->boardMatrix->Board2XY[1].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(384,84,40,40);
    p->setLocation(12,1);
    this->boardMatrix->Board2XY[2].flag=1;
    this->boardMatrix->Board2XY[2].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(312,126,40,40);
    p->setLocation(10,2);
    this->boardMatrix->Board2XY[3].flag=1;
    this->boardMatrix->Board2XY[3].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(360,126,40,40);
    p->setLocation(11,2);
    this->boardMatrix->Board2XY[4].flag=1;
    this->boardMatrix->Board2XY[4].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(408,126,40,40);
    p->setLocation(12,2);
    this->boardMatrix->Board2XY[5].flag=1;
    this->boardMatrix->Board2XY[5].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(288,168,40,40);
    p->setLocation(9,3);
    this->boardMatrix->Board2XY[6].flag=1;
    this->boardMatrix->Board2XY[6].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(336,168,40,40);
    p->setLocation(10,3);
    this->boardMatrix->Board2XY[7].flag=1;
    this->boardMatrix->Board2XY[7].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(384,168,40,40);
    p->setLocation(11,3);
    this->boardMatrix->Board2XY[8].flag=1;
    this->boardMatrix->Board2XY[8].pieceLocate=p;
    iter++;

    p = *iter;
    p->setGeometry(432,168,40,40);
    p->setLocation(12,3);
    this->boardMatrix->Board2XY[9].flag=1;
    this->boardMatrix->Board2XY[9].pieceLocate=p;

    //共10个棋子
    for(std::vector<Piece*>::iterator iter = this->vPieces.begin()+10;iter !=this->vPieces.end();iter++)
    {
        p=*iter;
        p->setParent(this);
    }
}

void playwindow::jumpMove(int m, int n){
    bool rep = false;//判断有无重复
    int i = this->boardMatrix->XY2Board[m][n];//存取当前是几号棋格

    //右上 跳的位置在棋盘内部/跳的位置没有棋子/中间有棋子/数组不越界
    int bridge = this->boardMatrix->Board2XY[i].nearby[0];
    int target = this->boardMatrix->Board2XY[bridge].nearby[0];
    if(bridge!=-1 && target!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 1 && \
       this->boardMatrix->Board2XY[target].flag == 0){
        for (std::vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            if(*it==(m+2) && *(it+1)==(n-2)){
                rep = true;
            }
            else{
                rep = false;
            }
        }

        if(!rep){
            legal.push_back(m+2);
            legal.push_back(n-2);
            jumpMove(m+2,n-2);
        }
    }

    //右侧
    bridge = this->boardMatrix->Board2XY[i].nearby[1];
    target = this->boardMatrix->Board2XY[bridge].nearby[1];
    if(bridge!=-1 && target!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 1 && \
       this->boardMatrix->Board2XY[target].flag == 0){
        for (std::vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            if(*it==(m+2) && *(it+1)==n ){
                rep = true;
            }
            else{
                rep = false;
            }
        }

        if(!rep){
            legal.push_back(m+2);
            legal.push_back(n);
            jumpMove(m+2,n);
        }
    }

    //右下
    bridge = this->boardMatrix->Board2XY[i].nearby[2];
    target = this->boardMatrix->Board2XY[bridge].nearby[2];
    if(bridge!=-1 && target!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 1 && \
       this->boardMatrix->Board2XY[target].flag == 0){
        for (std::vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            if(*it==m && *(it+1)==(n+2) ){
                rep = true;
            }
            else{
                rep = false;
            }
        }

        if(!rep){
            legal.push_back(m);
            legal.push_back(n+2);
            jumpMove(m,n+2);
        }
    }

    //左下
    bridge = this->boardMatrix->Board2XY[i].nearby[3];
    target = this->boardMatrix->Board2XY[bridge].nearby[3];
    if(bridge!=-1 && target!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 1 && \
       this->boardMatrix->Board2XY[target].flag == 0){
        for (std::vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            if(*it==(m-2) && *(it+1)==(n+2) ){
                rep = true;
            }
            else{
                rep = false;
            }
        }

        if(!rep){
            legal.push_back(m-2);
            legal.push_back(n+2);
            jumpMove(m-2,n+2);
        }
    }

    //左侧
    bridge = this->boardMatrix->Board2XY[i].nearby[4];
    target = this->boardMatrix->Board2XY[bridge].nearby[4];
    if(bridge!=-1 && target!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 1 && \
       this->boardMatrix->Board2XY[target].flag == 0){
        for (std::vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            if(*it==(m-2) && *(it+1)==n ){
                rep = true;
            }
            else{
                rep = false;
            }
        }

        if(!rep){
            legal.push_back(m-2);
            legal.push_back(n);
            jumpMove(m-2,n);
        }
    }

    //左上
    bridge = this->boardMatrix->Board2XY[i].nearby[5];
    target = this->boardMatrix->Board2XY[bridge].nearby[5];
    if(bridge!=-1 && target!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 1 && \
       this->boardMatrix->Board2XY[target].flag == 0){
        for (std::vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
            if(*it==m && *(it+1)==(n-2) ){
                rep = true;
            }
            else{
                rep = false;
            }
        }

        if(!rep){
            legal.push_back(m);
            legal.push_back(n-2);
            jumpMove(m,n-2);
        }
    }
}

bool playwindow::isLegalMove(int x1, int y1, int x2, int y2){
    int i,j ;
    for(int k=0;k<121;k++)
    {
            if(boardMatrix->Board2XY[k].x_p == x1 && boardMatrix->Board2XY[k].y_p == y1 ){
                i=k;
            }
    }
    for(int k=0;k<121;k++)
    {
            if(boardMatrix->Board2XY[k].x_p == x2 && boardMatrix->Board2XY[k].y_p == y2){
                j=k;
            }
    }
    legal.clear();

    //右上 跳的位置在棋盘内部/跳的位置没有棋子/数组不越界
    int bridge = this->boardMatrix->Board2XY[i].nearby[0];
    if(bridge!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 0){
        legal.push_back(boardMatrix->Board2XY[i].x+1);
        legal.push_back(boardMatrix->Board2XY[i].y-1);
    }
    //右侧
    bridge = this->boardMatrix->Board2XY[i].nearby[1];
    if(bridge!=-1 && \
        this->boardMatrix->Board2XY[bridge].flag == 0){
        legal.push_back(boardMatrix->Board2XY[i].x+1);
        legal.push_back(boardMatrix->Board2XY[i].y);
    }
    //右下
    bridge = this->boardMatrix->Board2XY[i].nearby[2];
    if(bridge!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 0){
        legal.push_back(boardMatrix->Board2XY[i].x);
        legal.push_back(boardMatrix->Board2XY[i].y+1);
    }
    //左下
    bridge = this->boardMatrix->Board2XY[i].nearby[3];
    if(bridge!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 0){
        legal.push_back(boardMatrix->Board2XY[i].x-1);
        legal.push_back(boardMatrix->Board2XY[i].y+1);
    }
    //左侧
    bridge = this->boardMatrix->Board2XY[i].nearby[4];
    if(bridge!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 0){
        legal.push_back(boardMatrix->Board2XY[i].x-1);
        legal.push_back(boardMatrix->Board2XY[i].y);
    }
    //左上
    bridge = this->boardMatrix->Board2XY[i].nearby[5];
    if(bridge!=-1 && \
       this->boardMatrix->Board2XY[bridge].flag == 0){
        legal.push_back(boardMatrix->Board2XY[i].x);
        legal.push_back(boardMatrix->Board2XY[i].y-1);
    }
    jumpMove(boardMatrix->Board2XY[i].x, boardMatrix->Board2XY[i].y);


    for(std::vector<int>::iterator it = legal.begin();it!=legal.end();it=it+2){
        if(boardMatrix->Board2XY[j].x == *it && boardMatrix->Board2XY[j].y == *(it+1)){
             return true;
        }
    }
    return false;
}

void playwindow::modifyInformation(int x1, int y1, int x2, int y2){
    int i,j;
    for(int k=0;k<121;k++)
    {
            if(boardMatrix->Board2XY[k].x_p == x1 && boardMatrix->Board2XY[k].y_p == y1 ){
                i=k;
            }
    }
    for(int k=0;k<121;k++)
    {
            if(boardMatrix->Board2XY[k].x_p == x2 && boardMatrix->Board2XY[k].y_p == y2){
                j=k;
            }
    }
    this->boardMatrix->Board2XY[i].flag = 0;
    this->boardMatrix->Board2XY[j].flag = 1;
    this->boardMatrix->Board2XY[j].pieceLocate = this->boardMatrix->Board2XY[i].pieceLocate;
    this->boardMatrix->Board2XY[i].pieceLocate = NULL;
    this->boardMatrix->Board2XY[j].pieceLocate->setLocation(boardMatrix->Board2XY[j].x, boardMatrix->Board2XY[j].y);
}

void playwindow::produceRectF(){
    for (int i=0; i<121; i++) {
        QRectF* rect = new QRectF();
        this->vRectF.push_back(rect);
    }
}

void playwindow::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        for(std::vector<QRectF*>::iterator iter = this->vRectF.begin();iter != this->vRectF.end();iter++) {
            QRectF* ptr = *iter;
            if(ptr->contains(mapFromGlobal(QCursor::pos()))==true){
                if(this->select!=NULL){
                    //植物方操作
                    if(this->control == 3){
                        if(isLegalMove(this->select->x(), this->select->y(), ptr->x(), ptr->y())){
                            change* ch = new change();
                            ch->setlastX(this->select->x());
                            ch->setlastY(this->select->y());
                            ch->setnewX(ptr->x());
                            ch->setnewY(ptr->y());
                            allstep3->push(ch);
                            //modify information
                            modifyInformation(this->select->x(), this->select->y(), ptr->x(), ptr->y());
                            moveProcess(ptr->x(), ptr->y());
                            this->clickPieceNum=0;
                            this->select->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess1.png"));
                            this->select=NULL;
                            judgewin3();
                            control=0;  //转换
                            ui->turn->setText("Zombies!");
                        }
                        else {
                            this->clickPieceNum=0;
                            this->select->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess1.png"));
                            this->select=NULL;
                        }
                    }
                    //僵尸方操作
                    else{
                        if(isLegalMove(this->select->x(), this->select->y(), ptr->x(), ptr->y())){
                            change* ch = new change();
                            ch->setlastX(this->select->x());
                            ch->setlastY(this->select->y());
                            ch->setnewX(ptr->x());
                            ch->setnewY(ptr->y());
                            allstep0->push(ch);
                            //modify information
                            modifyInformation(this->select->x(), this->select->y(), ptr->x(), ptr->y());
                            moveProcess(ptr->x(), ptr->y());
                            this->clickPieceNum=0;
                            this->select->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess2.png"));
                            this->select=NULL;
                            judgewin0();
                            control=3;
                            ui->turn->setText("Plants!");
                        }
                        else {
                            this->clickPieceNum=0;
                            this->select->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess2.png"));
                            this->select=NULL;
                        }
                    }
                }
            }

        }
    }
}

void playwindow::producePiece3(){   //植物方
    for (int i=0; i<10; i++) {
        Piece* p = new Piece();
        vPieces.push_back(p);
    }
    for(std::vector<Piece*>::iterator iter = vPieces.begin(); iter != vPieces.end(); iter++){
        Piece* p = *iter;
        p->setStatus(3);
        p->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess1.png"));
        p->setIconSize(QSize(40,40));
        p->setFlat(true);
        p->setParent(this);
    }
}

void playwindow::producePiece0(){   //僵尸方
    for (int i=0; i<10; i++) {
        Piece* p = new Piece();
        vPieces.push_back(p);
    }
    for(std::vector<Piece*>::iterator iter = vPieces.begin()+10; iter != vPieces.end(); iter++){
        Piece* p = *iter;
        p->setStatus(0);
        p->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess2.png"));
        p->setIconSize(QSize(40,40));
        p->setFlat(true);
        p->setParent(this);
    }
}

void playwindow::sleep(){
    //延时效果
    QTime t;
    t.start();
    while (t.elapsed()<300) {
        QCoreApplication::processEvents();
    }
}

void playwindow::judgewin0(){   //僵尸后手
    int count = 0;
    int line, col = 0;
    bool one = false;
    if(judge==3){
        one = true;
    }
    for (std::vector<Piece*>::iterator iter = this->vPieces.begin()+10; iter!=this->vPieces.end(); iter++){
        Piece* ptr = new Piece();
        ptr = *iter;
        line = ptr->getLine();
        col = ptr->getCol();
        if((line==12&&col==0)||(line==11&&col==1)||(line==12&&col==1)||(line==10&&col==2)
                ||(line==11&&col==2)||(line==12&&col==2)||(line==9&&col==3)
                ||(line==10&&col==3)||(line==11&&col==3)||(line==12&&col==3)){
            count++;
        }
    }
    if(count==10){
        one = false;
        //后手僵尸先完成
        if(judge==-1){
            Gameover* over = new Gameover();
            over->show();
            over->setWindowTitle("GameOver");
            this->close();
        }

        if(judge==3){
            Gameover* over = new Gameover();
            over->show();
            over->setWindowTitle("GameOver");
            //平局背景
            this->close();
        }
    }
    //植物方获胜
    if(one){
        Gameover* over = new Gameover();
        over->show();
        over->setWindowTitle("GameOver");
        this->close();
    }
}

void playwindow::judgewin3(){
    int count = 0;
    int line, col = 0;
    for (std::vector<Piece*>::iterator iter = this->vPieces.begin(); iter != this->vPieces.end()-10; iter++) {
        Piece* ptr = new Piece();
        ptr=*iter;
        line = ptr->getLine();
        col = ptr->getCol();
        if((line==4&&col==13)||(line==5&&col==13)||(line==6&&col==13)||(line==7&&col==13)
                ||(line==4&&col==14)||(line==5&&col==14)||(line==6&&col==14)
                ||(line==4&&col==15)||(line==5&&col==15)||(line==4&&col==16)){
            count++;
        }
    }
    if(count==10){
        judge=3;
    }
}

void playwindow::moveProcess(int x2, int y2){
    int j;
    for(int k=0;k<121;k++)
    {
            if(boardMatrix->Board2XY[k].x_p == x2 && boardMatrix->Board2XY[k].y_p == y2 ){
                j=k;
            }
    }
    this->select->move(boardMatrix->Board2XY[j].x_p, boardMatrix->Board2XY[j].y_p);

}

void playwindow::processClick0(int m, int n){   //僵尸
    int i = this->boardMatrix->XY2Board[m][n];
    if(control == 0){
        if(this->clickPieceNum == 0){
            this->clickPieceNum =1;
            this->select = this->boardMatrix->Board2XY[i].pieceLocate;
            this->select->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess2s.png"));
        }
        else{
            this->clickPieceNum = 0;
            this->select->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess2.png"));
            this->select = NULL;
        }
    }
}

void playwindow::processClick3(int m, int n){   //植物    可以加上按下的效果
    int i = this->boardMatrix->XY2Board[m][n];
    if(control == 3){
        if(this->clickPieceNum == 0){
            this->clickPieceNum =1;
            this->select = this->boardMatrix->Board2XY[i].pieceLocate;
            this->select->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess1s.png"));
        }
        else{
            this->clickPieceNum = 0;
            this->select->setIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\playwindow\\chess1.png"));
            this->select = NULL;
        }
    }
}

void playwindow::on_regret_clicked()
{
    if(control == 0 && allstep0->num!=0){    //僵尸方
        if(change* ch0 = allstep0->pop()){
            for (std::vector<Piece*>::iterator iter = this->vPieces.begin();iter != this->vPieces.end()-10; iter++){
                    Piece* ptr=new Piece();
                    ptr=*iter;
                    if(ptr->x() == ch0->getnewX() && ptr->y() == ch0->getnewY()){
                        ptr->move(ch0->getlastX(), ch0->getlastY());
                        modifyInformation(ch0->getnewX(), ch0->getnewY(), ch0->getlastX(), ch0->getlastY());
                    }
            }
        }
        control = 3;
    }
    else if(control == 3){      //植物方
        if(change* ch3 = allstep3->pop()){
            for (std::vector<Piece*>::iterator iter = this->vPieces.begin(); iter != this->vPieces.end()-10; iter++) {
                Piece* ptr=new Piece();
                ptr=*iter;
                if(ptr->x() == ch3->getnewX() && ptr->y() == ch3->getnewY()){
                    ptr->move(ch3->getlastX(), ch3->getlastY());
                    modifyInformation(ch3->getnewX(), ch3->getnewY(), ch3->getlastX(), ch3->getlastY());
                }

            }
            judge = -1;
        }
        control = 0;
    }
}

void playwindow::on_exit_clicked()
{
    this->close();
    MainWindow* w = new MainWindow();
    w->show();
}
