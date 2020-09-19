#ifndef RECORD_H
#define RECORD_H

#include <QDialog>
#include <vector>
#include "userdata.h"
using namespace std;
namespace Ui {
class Record;
}

class Record : public QDialog
{
    Q_OBJECT

public:
    explicit Record(QWidget *parent = 0);
    void display();
    ~Record();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Record *ui;
    vector<UserData*> ud;     //所有用户
};

#endif // RECORD_H
