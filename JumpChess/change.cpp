#include "change.h"

//设置和返回数据

void Change::setlastX(int x){
    this->lx = x;
}
void Change::setlastY(int y){
    this->ly = y;
}
void Change::setnewX(int x){
    this->nx = x;
}
void Change::setnewY(int y){
    this->ny = y;
}
int Change::getlastX(){
    return lx;
}
int Change::getlastY(){
    return ly;
}
int Change::getnewX(){
    return nx;
}
int Change::getnewY(){
    return ny;
}
