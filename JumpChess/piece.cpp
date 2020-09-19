#include<QString>
#include"piece.h"
#include<QDebug>
#include<QMouseEvent>
#include<QToolTip>
Piece::Piece(QWidget *parent) :
    QPushButton(parent)
{
    setClick(0);
    setStatus(0);
}
Piece::~Piece()
{

}
void Piece::setLocation(int line,int col)
{
    this->setLine(line);\
    this->setCol(col);
}

int Piece::getLine()
{
    return this->line;
}

void Piece::setLine(int line)
{
    this->line=line;
}

int Piece::getCol()
{
    return this->col;
}

void Piece::setCol(int col)
{
    this->col=col;
}

void Piece::setClick(int click)
{
    this->click=click;
}

int Piece::getClick()
{
    return this->click;
}

void Piece::setStatus(int s)
{
    this->status=s;
}

int Piece::getStatus()
{
    return this->status;
}


void Piece::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->setClick(1);
        emit pieceInfo(this->getLine(),this->getCol());
    }

    QPushButton::mousePressEvent(event);
}


