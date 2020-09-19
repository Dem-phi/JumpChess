#ifndef CHOOSE_H
#define CHOOSE_H

#include <QDialog>
#include <QMessageBox>
#include "playwindow.h"
#include <QLabel>
#include <QPushButton>

namespace Ui {
class choose;
}

class choose : public QDialog
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = nullptr);
    ~choose();
    int chosen = -1;     //0是僵尸方，3是植物方


private slots:
    void on_enter_clicked();

    void on_plants_pressed();

    void on_zombies_pressed();

private:
    Ui::choose *ui;
    playwindow* side;
    QMediaPlayer *sound = new QMediaPlayer;

};

#endif // CHOOSE_H
