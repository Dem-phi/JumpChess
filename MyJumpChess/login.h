#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QMovie>
#include "mainwindow.h"
#include <QFile>
#include "qdom.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <QJsonArray>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <QSound>
#include <QMediaPlayer>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_login_clicked();

    void on_signup_clicked();

    void on_login_pressed();

    void on_signup_pressed();

    void on_login_released();

    void on_signup_released();

    void isStart();

    void isSignUp();

private:
    Ui::Login *ui;
    MainWindow *d;
    QMediaPlayer *sound = new QMediaPlayer;
};

#endif // LOGIN_H
