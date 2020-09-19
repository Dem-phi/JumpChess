#include "board.h"
#include "iostream"

board::board()
{

}

void board::init()
{
    int i, j, count = 0; //i, j 为横纵坐标，count为第几号棋格
    for(i = 0; i<121; i++)//初始化
    {
            Board2XY[i].x=0;
            Board2XY[i].y=0;
            Board2XY[i].x_p=0;
            Board2XY[i].y_p=0;
            Board2XY[i].flag=0;
            Board2XY[i].pieceLocate=NULL;
    }
    for(i=0; i<17; i++)
    {
        for(j=0; j<17; j++)
        {
            if(XY2Board[i][j]>=0)
            {
                Board2XY[count].x = i;//x, y与i, j
                Board2XY[count].y = j;
                count++;
            }
        }
    }
    //坐标转换成像素
    for(int num = 0; num<121; num++){
        Board2XY[num].x_p = Board2XY[num].x*48+Board2XY[num].y*24-216;
        Board2XY[num].y_p = Board2XY[num].y*42+32;
    }

}

void board::initNearby()
{
    int i;
    Board2XY[0].nearby[0] = -1;
    Board2XY[0].nearby[1] = -1;
    Board2XY[0].nearby[2] = 2;
    Board2XY[0].nearby[3] = 1;
    Board2XY[0].nearby[4] = -1;
    Board2XY[0].nearby[5] = -1;

    Board2XY[22].nearby[0] = -1;
    Board2XY[22].nearby[1] = -1;
    Board2XY[22].nearby[2] = -1;
    Board2XY[22].nearby[3] = 34;
    Board2XY[22].nearby[4] = 21;
    Board2XY[22].nearby[5] = -1;

    Board2XY[98].nearby[0] = 86;
    Board2XY[98].nearby[1] = 99;
    Board2XY[98].nearby[2] = -1;
    Board2XY[98].nearby[3] = -1;
    Board2XY[98].nearby[4] = -1;
    Board2XY[98].nearby[5] = -1;

    Board2XY[120].nearby[0] = 119;
    Board2XY[120].nearby[1] = -1;
    Board2XY[120].nearby[2] = -1;
    Board2XY[120].nearby[3] = -1;
    Board2XY[120].nearby[4] = -1;
    Board2XY[120].nearby[5] = 118;
    for(i=0; i<121; i++)
    {
        if(i==0 || i==22 || i==98 || i==120){
            continue;
        }
        //右上
        if(XY2Board[Board2XY[i].x + 1][Board2XY[i].y - 1] != -1){
            Board2XY[i].nearby[0] = XY2Board[Board2XY[i].x + 1][Board2XY[i].y - 1];
        }
        else{
            Board2XY[i].nearby[0] = -1;
        }
        //右侧
        if(XY2Board[Board2XY[i].x + 1][Board2XY[i].y] != -1){
            Board2XY[i].nearby[1] = XY2Board[Board2XY[i].x + 1][Board2XY[i].y];
        }
        else{
            Board2XY[i].nearby[1] = -1;
        }
        //右下
        if(XY2Board[Board2XY[i].x][Board2XY[i].y + 1] != -1){
            Board2XY[i].nearby[2] = XY2Board[Board2XY[i].x][Board2XY[i].y + 1];
        }
        else{
            Board2XY[i].nearby[2] = -1;
        }
        //左下
        if(XY2Board[Board2XY[i].x - 1][Board2XY[i].y + 1] != -1){
            Board2XY[i].nearby[3] = XY2Board[Board2XY[i].x - 1][Board2XY[i].y + 1];
        }
        else{
            Board2XY[i].nearby[3] = -1;
        }
        //左侧
        if(XY2Board[Board2XY[i].x - 1][Board2XY[i].y] != -1){
            Board2XY[i].nearby[4] = XY2Board[Board2XY[i].x - 1][Board2XY[i].y];
        }
        else{
            Board2XY[i].nearby[4] = -1;
        }
        //左上
        if(XY2Board[Board2XY[i].x][Board2XY[i].y - 1] != -1){
            Board2XY[i].nearby[5] = XY2Board[Board2XY[i].x][Board2XY[i].y - 1];
        }
        else{
            Board2XY[i].nearby[5] = -1;
        }
    }
}
