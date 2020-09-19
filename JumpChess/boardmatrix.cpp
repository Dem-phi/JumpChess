#include"boardmatrix.h"
#include<iostream>
using namespace std;
boardMatrix::boardMatrix()
{

}

boardMatrix::~boardMatrix()
{

}
void boardMatrix::init()
{
    int i = 0;
    int j = 0;
    int iba = 0;
    int count = 0;
    //权值表（自己设计）
    int powerdata[17][13] ={{-1,-1,-1,-1,-1,-1,99,-1,-1,-1,-1,-1,-1},
                            {-1,-1,-1,-1,-1,97,97,-1,-1,-1,-1,-1,-1},
                            {-1,-1,-1,-1,-1,95,94,95,-1,-1,-1,-1,-1,},
                            {-1,-1,-1,-1,94,93,93,94,-1,-1,-1,-1,-1,},
                            { 0,15,30,45,88,92,91,92,88,45,30,15, 0},
                            { 1,15,30,70,82,84,84,82,70,30,15, 1,-1},
                            {-1,15,30,40,67,70,71,70,67,40,30,15,-1},
                            {-1,10,34,50,58,60,60,58,50,34,10,-1,-1},
                            {-1,-1,18,40,46,48,47,48,46,40,18,-1,-1},
                            {-1, 5,15,30,35,34,34,35,30,15, 5,-1,-1},
                            {-1, 5,10,20,26,28,27,28,26,20,10, 5,-1},
                            { 1, 2, 5,10,15,18,18,15,10, 5, 2, 1,-1},
                            { 0, 1, 2, 5,12,14,13,14,12, 5, 2, 1, 0},
                            {-1,-1,-1,-1, 9,10,10, 9,-1,-1,-1,-1,-1},
                            {-1,-1,-1,-1,-1, 5, 5, 5,-1-1,-1,-1,-1},
                            {-1,-1,-1,-1,-1, 3, 3,-1,-1,-1,-1,-1,-1},
                            {-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1},
                           };

    //本数表用来规定权重
    for(i=0;i<17;i++)
    {
        for(j=0;j<13;j++)
        {
            //设置AI和玩家权重表
            AIpower[i][j] = powerdata[i][j];
            humanpower[16-i][j] = powerdata[i][j];
            //各项数据初始化
            Matrix[i][j].x=0;
            Matrix[i][j].y=0;
            Matrix[i][j].flag=0;
            Matrix[i][j].pieceLocate = NULL;
        }
    }

    //坐标的录入
    int line[17];
    int column0[13];
    int column1[13];
    //横纵坐标
    for(i=0;i<17;i++){
        line[i] = 60 + 46 * i;
    }
    for(i=0;i<13;i++){
        column0[i] = 122 + 59 * i;
    }
    for(i=0;i<13;i++){
        column1[i] = 152 + 59 * i;
    }
    //生成有效的棋盘，每个点对应各个坐标
    for(i=0;i<17;i++)
    {
        count = 0;
        for(j=0;j<13;j++)
        {
            this->Matrix[i][j].y=line[i];

            if(i<4 ||(i>=8 && i<13) ){

                if(i%2){
                    if(count<i+1){
                        this->Matrix[i][6-(i+1)/2+count].x=column1[6-(i+1)/2+count];
                        count++;
                    }

                }
                else{
                    if(count<i+1){
                        this->Matrix[i][(12-i)/2+count].x=column0[(12-i)/2+count];
                        count++;
                    }

                }
            }

            else if((i>=13 && i<17)||(i>=4 && i<8)){
                iba = 17-i-1;
                if(iba%2){
                    if(count<iba+1){
                        this->Matrix[i][6-(iba+1)/2+count].x=column1[6-(iba+1)/2+count];
                        count++;
                    }

                }
                else{
                    if(count<iba+1){
                        this->Matrix[i][(12-iba)/2+count].x=column0[(12-iba)/2+count];
                        count++;
                    }

                }
            }
        }
    }
}
