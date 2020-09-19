#include "gameover.h"
#include "ui_gameover.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>

gameover::gameover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/res/chessico.png"));
}

gameover::~gameover()
{
    delete ui;
}

void gameover::on_pushButton_clicked()
{
    QString fileName="D:\\chart.txt";
    QFile file(fileName);
    UserData* user;
    bool needadd = true;
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream in(&file);
    QString str1,str2,str3,str4;
    int win,fail,dual,rate;
    while(!in.atEnd()){
        str1=in.readLine();
        str2=in.readLine();
        str3=in.readLine();
        str4=in.readLine();
        win = str2.toInt();
        fail = str3.toInt();
        dual = str4.toInt();
        rate = win *100/(win+fail+dual);
        user = new UserData(str1,win,fail,dual,rate);
        ud.push_back(user);
    }
    for(vector<UserData*>::iterator iter = ud.begin();iter != ud.end();iter++)
    {
        user = *iter;
        if(user->getname()==ui->lineEdit->text()){
            needadd = false;
            win = user->getwin();
            fail = user->getfail();
            dual = user->getdual();
            rate = win *100/(win+fail+dual);
            if(flag.compare("玩家获胜")==0)
            {
                win++;
                user->setwin(win);
            }
            if(flag.compare("电脑获胜")==0)
            {
                fail++;
                user->setfail(fail);
            }
            if(flag.compare("平局")==0)
            {
                dual++;
                user->setdual(dual);
            }
            user->setrate(rate);
        }

    }
    if(needadd){
        if(flag.compare("玩家获胜")==0)
        {
            user = new UserData(ui->lineEdit->text(),1,0,0,100);
        }
        if(flag.compare("电脑获胜")==0)
        {
            user = new UserData(ui->lineEdit->text(),0,1,0,0);
        }
        if(flag.compare("平局")==0)
        {
            user = new UserData(ui->lineEdit->text(),0,0,1,0);
        }
        ud.push_back(user);
    }
    QFile file2(fileName);
    file2.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream out(&file2);
    for(vector<UserData*>::iterator iter = ud.begin();iter != ud.end();iter++)
    {
        user = *iter;
        out<<user->getname()<<endl;
        out<<user->getwin()<<endl;
        out<<user->getfail()<<endl;
        out<<user->getdual()<<endl;
    }
    this->hide();
    MainWindow* w = new MainWindow();
    w->show();
}
void gameover::set(QString f,QString s,int t)
{
    this->flag = f;
    this->step = s;
    this->time = t;
    int hour = 0;
    int minute = 0;
    int second = 0;
    hour = time / 3600;
    minute = (time - 3600*hour) / 60;
    second = time % 60;
    ui->label->setText(flag);
    ui->textBrowser->setText(s);
    ui->textBrowser_2->setText(QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second));
}
