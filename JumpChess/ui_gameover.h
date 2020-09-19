/********************************************************************************
** Form generated from reading UI file 'gameover.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOVER_H
#define UI_GAMEOVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gameover
{
public:
    QWidget *widget;
    QLabel *label;
    QTextBrowser *textBrowser;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_4;
    QTextBrowser *textBrowser_2;
    QLineEdit *lineEdit;

    void setupUi(QWidget *gameover)
    {
        if (gameover->objectName().isEmpty())
            gameover->setObjectName(QString::fromUtf8("gameover"));
        gameover->resize(400, 300);
        gameover->setMinimumSize(QSize(400, 300));
        gameover->setMaximumSize(QSize(400, 300));
        gameover->setStyleSheet(QString::fromUtf8("background-image: url(:/res/background6.png);"));
        widget = new QWidget(gameover);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 401, 301));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 0, 201, 121));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\345\272\267\344\277\252\351\207\221\351\273\221W8(P)"));
        font.setPointSize(28);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background: transparent;"));
        textBrowser = new QTextBrowser(widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(80, 120, 71, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\200\240\345\255\227\345\267\245\346\210\277\346\234\227\345\200\251\357\274\210\351\235\236\345\225\206\347\224\250\357\274\211\345\270\270\350\247\204\344\275\223"));
        font1.setPointSize(14);
        textBrowser->setFont(font1);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 120, 91, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\200\240\345\255\227\345\267\245\346\210\277\346\234\227\345\200\251\357\274\210\351\235\236\345\225\206\347\224\250\357\274\211\345\270\270\350\247\204\344\275\223"));
        font2.setPointSize(18);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("background: transparent;"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 250, 111, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font3.setPointSize(18);
        pushButton->setFont(font3);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 180, 91, 41));
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("background: transparent;"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 120, 91, 41));
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8("background: transparent;"));
        textBrowser_2 = new QTextBrowser(widget);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(230, 120, 161, 41));
        textBrowser_2->setFont(font1);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 180, 241, 41));
        lineEdit->setFont(font1);

        retranslateUi(gameover);

        QMetaObject::connectSlotsByName(gameover);
    } // setupUi

    void retranslateUi(QWidget *gameover)
    {
        gameover->setWindowTitle(QCoreApplication::translate("gameover", "Form", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("gameover", "\346\255\245\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("gameover", "\350\277\224\345\233\236", nullptr));
        label_3->setText(QCoreApplication::translate("gameover", "\345\247\223\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("gameover", "\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gameover: public Ui_gameover {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVER_H
