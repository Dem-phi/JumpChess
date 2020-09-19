#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameplay.h"
#include "aigame.h"
#include "regulation.h"
#include "choose.h"
#include "record.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/res/chessico.png"));
    this->setWindowTitle("中国跳棋");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    gameplay* game = new gameplay();
    game->show();
}

void MainWindow::on_pushButton_2_clicked()
{
        this->close();
}

void MainWindow::on_pushButton_3_clicked()
{
    regulation* re =new regulation(this);
    re->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->hide();
    choose* ch = new choose();
    ch->show();

}

void MainWindow::on_pushButton_5_clicked()
{
    Record * c =new Record(this);
    c->show();
}
