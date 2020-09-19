#include "regulation.h"
#include "ui_regulation.h"

regulation::regulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regulation)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/res/chessico.png"));
    this->setWindowTitle("游戏规则");
}

regulation::~regulation()
{
    delete ui;
}

void regulation::on_pushButton_clicked()
{
    this->close();
}
