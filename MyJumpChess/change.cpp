#include "change.h"

change::change()
{

}
void change::setlastX(int x){
    this->lx = x;
}
void change::setlastY(int y){
    this->ly = y;
}
void change::setnewX(int x){
    this->nx = x;
}
void change::setnewY(int y){
    this->ny = y;
}
int change::getlastX(){
    return lx;
}
int change::getlastY(){
    return ly;
}
int change::getnewX(){
    return nx;
}
int change::getnewY(){
    return ny;
}
