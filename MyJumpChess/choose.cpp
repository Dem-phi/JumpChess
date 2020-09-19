#include "choose.h"
#include "ui_choose.h"
#include <QMessageBox>
#include "playwindow.h"
#include <QLabel>
#include <QPushButton>

choose::choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choose)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\icon.png"));
}

choose::~choose()
{
    delete ui;
}

void choose::on_enter_clicked()
{
    /*
    if(chosen == 3){    //植物方

    }
    else if(chosen == 0){   //僵尸方

    }
    else{
        QMessageBox::information(NULL, "Warning", "Unchecked!");
    }
    */
    this->hide();
    // 关闭原来的mainwindow
    sound->stop();
    playwindow* p = new playwindow();
    p->show();

}

void choose::on_plants_pressed()
{
    sound->setMedia(QUrl("qrc:/res/sounds/choose_plants.mp3"));
    sound->play();
    ui->plants->setStyleSheet("QPushButton{background:transparent;\
                               background-image: url(:/res/choose/plants_2.png);}");
    ui->plants_side->setStyleSheet("background-image: url(:/res/choose/chosen.png);");
    if(chosen == 0){
        ui->zombies->setStyleSheet("background:transparent;\
                                    background-image: url(:/res/choose/zombies_1.png);");
        ui->zombies_side->setStyleSheet("background-image: url(:/res/choose/unchosen.png);");
    }
    chosen = 3;
}

void choose::on_zombies_pressed()
{
    sound->setMedia(QUrl("qrc:/res/sounds/choose_zombies.mp3"));
    sound->play();
    if(chosen == 3){
        ui->plants->setStyleSheet("QPushButton{background:transparent;\
                                   background-image: url(:/res/choose/plants_1.png);}");
        ui->plants_side->setStyleSheet("background-image: url(:/res/choose/unchosen.png);");
    }

    ui->zombies->setStyleSheet("background:transparent;\
                                background-image: url(:/res/choose/zombies_2.png);");
    ui->zombies_side->setStyleSheet("background-image: url(:/res/choose/chosen.png);");
    chosen = 0;
}

