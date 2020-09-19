#include "login.h"
#include "ui_login.h"
#include <QLabel>
#include <QMovie>
#include <mainwindow.h>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <iostream>
#include <QJsonArray>
#include <json/json.h>
#include <fstream>
#include <string>
#include <QSound>
#include <QMediaPlayer>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("E:\\Coding\\Qt\\MyJumpChess\\res\\icon.png"));
    sound->setMedia(QUrl("qrc:/res/sounds/login.mp3"));
    sound->play();
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    isStart();

}

void Login::on_signup_clicked()
{
    isSignUp();
}

void Login::on_login_pressed()
{
    ui->login->setStyleSheet("background-image: url(:/res/Login/button_2.png);\
                             border: none;\
                             outline: none;\
                             font-size: 16px;\
                             margin: 2rem 0 0;\
                             width: 100%;\
                             height:3.5rem;\
                             border-radius: 3rem;\
                             color: white;");
}

void Login::on_signup_pressed()
{
    ui->signup->setStyleSheet("background-image: url(:/res/Login/signup2.png);\
                             border: none;\
                             outline: none;\
                             font-size: 16px;\
                             margin: 2rem 0 0;\
                             width: 100%;\
                             height:3.5rem;\
                             border-radius: 3rem;\
                             color: white;");
}

void Login::on_login_released()
{
    ui->login->setStyleSheet("background-image: url(:/res/Login/button_1.png);\
                             border: none;\
                             outline: none;\
                             font-size: 16px;\
                             margin: 2rem 0 0;\
                             width: 100%;\
                             height:3.5rem;\
                             border-radius: 3rem;\
                             color: white;");
}

void Login::on_signup_released()
{
    ui->signup->setStyleSheet("background-image: url(:/res/Login/signup.png);\
                             border: none;\
                             outline: none;\
                             font-size: 16px;\
                             margin: 2rem 0 0;\
                             width: 100%;\
                             height:3.5rem;\
                             border-radius: 3rem;\
                             color: white;");
}

void Login::isStart(){
    QFile file("E:\\Coding\\Qt\\MyJumpChess\\userlog.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    bool exist = false;
    QByteArray allData = file.readAll();
    file.close();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

    if(json_error.error != QJsonParseError::NoError){
        qDebug() << "json error!";
        return;
    }
    int i;
    QJsonObject rootObj = jsonDoc.object();
    QStringList keys = rootObj.keys();
    for (i = 0; i<keys.size(); i++) {
        qDebug() << "key" << i << "is:" << keys.at(i);
    }

    for (int j = 1; j<=(i+1); j++) {
        QString s, uname, pword;
        QJsonObject subObj;
        s= QString::number(j);
        subObj= rootObj["user"+s].toObject();
        uname = subObj["username"].toString();
        pword = subObj["password"].toString();
        if(uname == ui->username->text()){
            exist = true;
            if(!(pword == ui->password->text())){
                QMessageBox::information(NULL, "Warning", "Wrong password!");
                ui->password->clear();
                ui->password->setFocus();
                exist = false;
                return;
            }
            else{
                this->close();
                d = new MainWindow(0);
                d->setWindowTitle("JumpChess");
                d->show();
                sound->stop();
                break;
            }
        }
        if(exist == false && j == (i+1)){
            QMessageBox::information(NULL, "Warning", "No exist! Please change another username");
            ui->username->clear();
            ui->password->clear();
            ui->username->setFocus();
            return;
        }
    }
}

void Login::isSignUp(){
    QFile file("E:\\Coding\\Qt\\MyJumpChess\\userlog.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    bool exist = false;
    QByteArray allData = file.readAll();
    file.close();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    QJsonObject rootObj = jsonDoc.object();
    QStringList keys = rootObj.keys();
    int i = keys.size();
    for (int j = 1; j<=(i+1); j++) {
        //判断有无重复
        QString s, uname, pword;
        QJsonObject subObj;
        s= QString::number(j);
        subObj= rootObj["user"+s].toObject();
        uname = subObj["username"].toString();
        pword = subObj["password"].toString();
        if(uname == ui->username->text()){
            exist = true;
            QMessageBox::information(NULL, "Warning", "Already Exist!");
            ui->password->clear();
            ui->password->setFocus();
            break;
            }
        else if(!exist && j == i){
            s= QString::number(j+1);
            Json::Reader reader;
            Json::Value root;
            std::ifstream in("E:\\Coding\\Qt\\MyJumpChess\\userlog.json", std::ios::binary);
            if(reader.parse(in, root)){
                Json::Value user;
                user["username"] = Json::Value(ui->username->text().toStdString());
                user["password"] = Json::Value(ui->password->text().toStdString());
                root["user"+s.toStdString()] = Json::Value(user);
                Json::StyledWriter sw;
                std::ofstream os;
                os.open("E:\\Coding\\Qt\\MyJumpChess\\userlog.json", std::ios::out );
                os.clear();
                os << sw.write(root);
                os.close();
                QMessageBox::information(NULL, "Message", "Successfully!");
                break;
            }
        }

    }
}







