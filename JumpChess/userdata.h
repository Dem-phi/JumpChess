#ifndef USERDATA_H
#define USERDATA_H
#include <QString>
class UserData{
    //用来存取新旧坐标的类
public:
    UserData(QString n,int w,int f,int d,int r);
    QString getname();
    void setname(QString name);
    int getwin();
    void setwin(int win);
    int getfail();
    void setfail(int fail);
    int getdual();
    void setdual(int dual);
    int getrate();
    void setrate(int rate);
private:
    QString name;
    int win;
    int fail;
    int dual;
    int rate;
};
#endif // USERDATA_H
