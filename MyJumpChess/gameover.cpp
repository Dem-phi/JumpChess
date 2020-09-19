#include "gameover.h"
#include "ui_gameover.h"
#include <QIcon>

Gameover::Gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gameover)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\icon.png"));
}

Gameover::~Gameover()
{
    delete ui;
}
