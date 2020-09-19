#include "userdata.h"

//设置和返回数据
UserData::UserData(QString n,int w,int f,int d,int r){
    this->name = n;
    this->win = w;
    this->fail = f;
    this->dual = d;
    this->rate = r;
}

void UserData::setname(QString n){
    this->name = n;
}
void UserData::setwin(int w){
    this->win = w;
}
void UserData::setfail(int f){
    this->fail = f;
}
void UserData::setdual(int d){
    this->dual = d;
}
void UserData::setrate(int r){
    this->rate = r;
}
QString UserData::getname(){
    return name;
}

int UserData::getwin(){
    return win;
}
int UserData::getfail(){
    return fail;
}
int UserData::getdual(){
    return dual;
}
int UserData::getrate(){
    return rate;
}
