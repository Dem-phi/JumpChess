#ifndef BOARDMATRIX_H
#define BOARDMATRIX_H
#include "piece.h"
typedef struct{
    int x;              //横坐标
    int y;              //纵坐标
    int flag;           //占用标志
    Piece* pieceLocate; //棋子指针
}information;

class boardMatrix{
public:
    information Matrix[17][13];     //棋盘矩阵
    boardMatrix();
    ~boardMatrix();
    int AIpower[17][13];            //AI权值表
    int humanpower[17][13];         //玩家权值表
    void init();                    //初始化函数
};
#endif // BOARDMATRIX_H
