#ifndef PIECE_H
#define PIECE_H
#include <QPushButton>
#include <iostream>
#include <QMouseEvent>
using std::string;

class Piece : public QPushButton
{
    Q_OBJECT
public:
    Piece(QWidget *parent = 0);
    ~Piece();
    void setLocation(int x, int y);
    int getLine();  // X轴
    void setLine(int x);
    int getCol();   // Y轴
    void setCol(int y);
    void setClick(int click);
    int getClick();
    void setStatus(int s);
    int getStatus();

protected:
    void mousePressEvent(QMouseEvent* event);
private:
    int line;      //x坐标
    int col;       //y坐标
    int status; //棋子所属 0-5 上方 顺时针
    int click;  // 0->未选中，1->选中
signals:
    void pieceInfo(int, int);
};

#endif // PIECE_H
