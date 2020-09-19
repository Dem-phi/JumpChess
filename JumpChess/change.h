#ifndef CHANGE_H
#define CHANGE_H
class Change{
    //用来存取新旧坐标的类
public:
    int getlastX();
    void setlastX(int x);
    int getlastY();
    void setlastY(int y);
    int getnewX();
    void setnewX(int x);
    int getnewY();
    void setnewY(int y);
private:
    int lx;
    int ly;
    int nx;
    int ny;
};

#endif // CHANGE_H
