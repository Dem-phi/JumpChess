#include "record.h"
#include "ui_record.h"
#include "QFile"
#include "QTextStream"

Record::Record(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Record)
{
    ui->setupUi(this);
    this->setWindowTitle("战绩");
    display();
}
void Record::display(){

    QString fileName="D:\\chart.txt";
    QFile file(fileName);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream in(&file);
    UserData* user;
    QString str1,str2,str3,str4;
    int rate = 0;
    while(!in.atEnd()){
        str1=in.readLine();
        str2=in.readLine();
        str3=in.readLine();
        str4=in.readLine();
        int win = str2.toInt();
        int fail = str3.toInt();
        int dual = str4.toInt();
        rate = win *100/(win+fail+dual);
        user = new UserData(str1,win,fail,dual,rate);
        ud.push_back(user);
    }
    vector<UserData*>::iterator iter = ud.begin();
    UserData* user1 = *iter;
    UserData* user2 = *(iter+1);
    UserData* user3 = *(iter+2);
    if(user1->getwin()<user2->getwin()){
        user=user1;
        user1=user2;
        user2=user;
    }
    if(user1->getwin()<user3->getwin()){
        user=user1;
        user1=user3;
        user3=user;
    }
    if(user2->getwin()<user3->getwin()){
        user=user2;
        user2=user3;
        user3=user;
    }
    for(vector<UserData*>::iterator iter = ud.begin()+3;iter != ud.end();iter++)
    {
        user = *iter;
        if(user->getwin()>user1->getwin())
        {
            user3=user2;
            user2=user1;
            user1=user;
        }
        else if(user->getwin()>user2->getwin())
        {
            user3=user2;
            user2=user;
        }
        else if(user->getwin()>user3->getwin())
        {
            user3=user;
        }
    }
    this->ui->label_5->setText(QString::number(user1->getwin()));
    this->ui->label_6->setText(QString::number(user1->getfail()));
    this->ui->label_9->setText(QString::number(user1->getdual()));
    this->ui->label_11->setText(user1->getname());
    this->ui->label_7->setText(QString::number(user1->getrate())+"%");
    this->ui->label_13->setText(QString::number(user2->getwin()));
    this->ui->label_14->setText(QString::number(user2->getfail()));
    this->ui->label_15->setText(QString::number(user2->getdual()));
    this->ui->label_12->setText(user2->getname());
    this->ui->label_16->setText(QString::number(user2->getrate())+"%");
    this->ui->label_18->setText(QString::number(user3->getwin()));
    this->ui->label_19->setText(QString::number(user3->getfail()));
    this->ui->label_20->setText(QString::number(user3->getdual()));
    this->ui->label_17->setText(user3->getname());
    this->ui->label_21->setText(QString::number(user3->getrate())+"%");
}

Record::~Record()
{
    delete ui;
}

void Record::on_pushButton_clicked()
{
    this->close();
}
