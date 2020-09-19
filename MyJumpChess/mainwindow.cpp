#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choose.h"
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\icon.png"));
    soundList->addMedia(QUrl("qrc:/res/sounds/mainwindow.MP3"));
    soundList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mainsound->setPlaylist(soundList);
    mainsound->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    choose* cho = new choose();
    cho->show();
}

void MainWindow::on_exit_clicked()
{
    this->close();
}
