#ifndef PIECE_H
#define PIECE_H
#include <QPushButton>
#include<string>
using  std::string;
/*
 * 棋子类
 * 属于按钮
 */
class Piece : public QPushButton
{
    Q_OBJECT
public:
    Piece(QWidget *parent = 0);
    ~Piece();
    void setLocation(int line,int col);
    int getLine();
    void setLine(int guess);
    int getCol();
    void setCol(int col);
    void setClick(int click);
    int getClick();
    void setStatus(int s);
    int getStatus();

protected:
    void mousePressEvent(QMouseEvent* event);
private:

    int line;           //所在棋盘的行数
    int col;            //所在棋盘的列数
    int status;         //表明棋子属于哪一方，我方为0，AI方为1
    int click;          //是否被选中
signals:
    void pieceInfo(int,int);
};




#endif // PIECE_H

