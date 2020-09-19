/********************************************************************************
** Form generated from reading UI file 'record.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORD_H
#define UI_RECORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Record
{
public:
    QWidget *widget;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_10;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_8;
    QLabel *label_4;
    QPushButton *pushButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_11;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_7;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;

    void setupUi(QDialog *Record)
    {
        if (Record->objectName().isEmpty())
            Record->setObjectName(QString::fromUtf8("Record"));
        Record->resize(600, 400);
        Record->setMinimumSize(QSize(600, 400));
        Record->setMaximumSize(QSize(600, 400));
        Record->setStyleSheet(QString::fromUtf8("background-image: url(:/res/background8.jpg);"));
        widget = new QWidget(Record);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 601, 401));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 0, 131, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font.setPointSize(36);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background: transparent;"));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 60, 581, 71));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font1.setPointSize(22);
        label_10->setFont(font1);
        label_10->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout->addWidget(label_10);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout->addWidget(label_3);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout->addWidget(label_8);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout->addWidget(label_4);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 340, 111, 51));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font2.setPointSize(20);
        pushButton->setFont(font2);
        layoutWidget1 = new QWidget(widget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 130, 581, 71));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setWeight(75);
        label_11->setFont(font3);
        label_11->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_2->addWidget(label_11);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font3);
        label_5->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_2->addWidget(label_5);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font3);
        label_6->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_2->addWidget(label_6);

        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font3);
        label_9->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_2->addWidget(label_9);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font3);
        label_7->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_2->addWidget(label_7);

        layoutWidget_2 = new QWidget(widget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 200, 581, 71));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font3);
        label_12->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_3->addWidget(label_12);

        label_13 = new QLabel(layoutWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font3);
        label_13->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_3->addWidget(label_13);

        label_14 = new QLabel(layoutWidget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font3);
        label_14->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_3->addWidget(label_14);

        label_15 = new QLabel(layoutWidget_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font3);
        label_15->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_3->addWidget(label_15);

        label_16 = new QLabel(layoutWidget_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font3);
        label_16->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_3->addWidget(label_16);

        layoutWidget_3 = new QWidget(widget);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(20, 270, 581, 71));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_17 = new QLabel(layoutWidget_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font3);
        label_17->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_4->addWidget(label_17);

        label_18 = new QLabel(layoutWidget_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font3);
        label_18->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_4->addWidget(label_18);

        label_19 = new QLabel(layoutWidget_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font3);
        label_19->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_4->addWidget(label_19);

        label_20 = new QLabel(layoutWidget_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font3);
        label_20->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_4->addWidget(label_20);

        label_21 = new QLabel(layoutWidget_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font3);
        label_21->setStyleSheet(QString::fromUtf8("background: transparent;"));

        horizontalLayout_4->addWidget(label_21);


        retranslateUi(Record);

        QMetaObject::connectSlotsByName(Record);
    } // setupUi

    void retranslateUi(QDialog *Record)
    {
        Record->setWindowTitle(QCoreApplication::translate("Record", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Record", "\346\210\230\347\273\251", nullptr));
        label_10->setText(QCoreApplication::translate("Record", "\345\247\223\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("Record", "\350\203\234\345\234\272", nullptr));
        label_3->setText(QCoreApplication::translate("Record", "\350\264\237\345\234\272", nullptr));
        label_8->setText(QCoreApplication::translate("Record", "\345\271\263\345\261\200", nullptr));
        label_4->setText(QCoreApplication::translate("Record", "\350\203\234\347\216\207", nullptr));
        pushButton->setText(QCoreApplication::translate("Record", "\350\277\224\345\233\236", nullptr));
        label_11->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        label_9->setText(QString());
        label_7->setText(QString());
        label_12->setText(QString());
        label_13->setText(QString());
        label_14->setText(QString());
        label_15->setText(QString());
        label_16->setText(QString());
        label_17->setText(QString());
        label_18->setText(QString());
        label_19->setText(QString());
        label_20->setText(QString());
        label_21->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Record: public Ui_Record {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORD_H
