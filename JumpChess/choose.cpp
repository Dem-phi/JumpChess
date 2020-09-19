#include "choose.h"
#include "ui_choose.h"
#include "mainwindow.h"
#include "aigame.h"
int playerState;
int AIState;
choose::choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/res/chessico.png"));
    this->setWindowTitle("模式选择");
}

choose::~choose()
{
    delete ui;
}
void choose::getGameState()
{
    QString str;
    str=ui->comboBox->currentText();
    if(str=="先手")
    {
        playerState=0;
    }
    else
    {
        playerState=1;
    }
    str=ui->comboBox_2->currentText();
    if(str=="进攻型")
    {
        AIState=0;
    }
    else if(str=="防守型")
    {
        AIState=1;
    }
    else
    {
        AIState=2;
    }
    qDebug()<<playerState<<AIState;

}
void choose::on_pushButton_2_clicked()
{
    this->hide();
    MainWindow* w = new MainWindow();
    w->show();
}

void choose::on_pushButton_clicked()
{
    getGameState();
    AIgame* g = new AIgame();
    g->show();
    this->hide();
}
