#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include <vector>
#include "userdata.h"
using namespace std;
namespace Ui {
class gameover;
}

class gameover : public QWidget
{
    Q_OBJECT

public:
    explicit gameover(QWidget *parent = 0);
    ~gameover();
    QString step;
    QString flag;
    int time;
    void set(QString flag,QString step,int time);

private slots:
    void on_pushButton_clicked();

private:
    Ui::gameover *ui;
    vector<UserData*> ud;     //所有用户
};

#endif // GAMEOVER_H
