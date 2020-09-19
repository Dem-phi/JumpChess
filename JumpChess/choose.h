#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>

namespace Ui {
class choose;
}

class choose : public QWidget
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = 0);
    void getGameState();
    ~choose();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:

    Ui::choose *ui;
};

#endif // CHOOSE_H
