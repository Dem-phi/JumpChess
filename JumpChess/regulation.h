#ifndef REGULATION_H
#define REGULATION_H

#include <QWidget>

namespace Ui {
class regulation;
}

class regulation : public QWidget
{
    Q_OBJECT

public:
    explicit regulation(QWidget *parent = 0);
    ~regulation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::regulation *ui;
};

#endif // REGULATION_H
