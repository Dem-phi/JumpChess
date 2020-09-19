/********************************************************************************
** Form generated from reading UI file 'choose.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSE_H
#define UI_CHOOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_choose
{
public:
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *choose)
    {
        if (choose->objectName().isEmpty())
            choose->setObjectName(QString::fromUtf8("choose"));
        choose->resize(600, 400);
        choose->setMinimumSize(QSize(600, 400));
        choose->setMaximumSize(QSize(600, 400));
        choose->setStyleSheet(QString::fromUtf8("background-image: url(:/res/background5.png);"));
        widget = new QWidget(choose);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 601, 401));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 90, 161, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\345\272\267\344\277\252\351\207\221\351\273\221W8(P)"));
        font.setPointSize(20);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background: transparent;"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 180, 161, 71));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("background: transparent;"));
        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(320, 120, 101, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\200\240\345\255\227\345\267\245\346\210\277\346\202\246\345\234\206\357\274\210\351\235\236\345\225\206\347\224\250\357\274\211\345\270\270\350\247\204\344\275\223"));
        font1.setPointSize(18);
        comboBox->setFont(font1);
        comboBox_2 = new QComboBox(widget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(320, 190, 151, 41));
        comboBox_2->setFont(font1);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(110, 290, 131, 61));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\200\240\345\255\227\345\267\245\346\210\277\346\234\227\345\200\251\357\274\210\351\235\236\345\225\206\347\224\250\357\274\211\345\270\270\350\247\204\344\275\223"));
        font2.setPointSize(18);
        pushButton->setFont(font2);
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 290, 131, 61));
        pushButton_2->setFont(font2);

        retranslateUi(choose);

        QMetaObject::connectSlotsByName(choose);
    } // setupUi

    void retranslateUi(QWidget *choose)
    {
        choose->setWindowTitle(QCoreApplication::translate("choose", "Form", nullptr));
        label->setText(QCoreApplication::translate("choose", "\344\270\213\346\243\213\351\241\272\345\272\217", nullptr));
        label_2->setText(QCoreApplication::translate("choose", "AI\351\243\216\346\240\274", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("choose", "\345\205\210\346\211\213", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("choose", "\345\220\216\346\211\213", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("choose", "\350\277\233\346\224\273\345\236\213", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("choose", "\351\230\262\345\256\210\345\236\213", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("choose", "\345\235\207\350\241\241\345\236\213", nullptr));

        pushButton->setText(QCoreApplication::translate("choose", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("choose", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class choose: public Ui_choose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSE_H
