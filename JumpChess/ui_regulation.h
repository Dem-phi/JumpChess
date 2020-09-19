/********************************************************************************
** Form generated from reading UI file 'regulation.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGULATION_H
#define UI_REGULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_regulation
{
public:
    QWidget *widget;
    QLabel *label;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *regulation)
    {
        if (regulation->objectName().isEmpty())
            regulation->setObjectName(QString::fromUtf8("regulation"));
        regulation->resize(800, 600);
        regulation->setMinimumSize(QSize(800, 600));
        regulation->setMaximumSize(QSize(800, 600));
        regulation->setStyleSheet(QString::fromUtf8("background-image: url(:/res/background4.png);"));
        widget = new QWidget(regulation);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(-1, -1, 811, 611));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 191, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\345\272\267\344\277\252\351\207\221\351\273\221W8(P)"));
        font.setPointSize(24);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background: transparent;"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(620, 480, 121, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(24);
        pushButton->setFont(font1);
        textBrowser = new QTextBrowser(widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(60, 130, 671, 291));
        textBrowser->setStyleSheet(QString::fromUtf8("background: transparent;"));

        retranslateUi(regulation);

        QMetaObject::connectSlotsByName(regulation);
    } // setupUi

    void retranslateUi(QWidget *regulation)
    {
        regulation->setWindowTitle(QCoreApplication::translate("regulation", "Form", nullptr));
        label->setText(QCoreApplication::translate("regulation", "\346\270\270\346\210\217\350\247\204\345\210\231", nullptr));
        pushButton->setText(QCoreApplication::translate("regulation", "OK", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("regulation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'arial,\345\256\213\344\275\223,sans-serif'; font-size:16pt; font-weight:600; color:#333333; background-color:#ffffff;\">     \350\267\263\346\243\213\347\232\204\346\270\270\346\210\217\350\247\204\345\210\231\345\276\210\347\256\200\345\215\225\357\274\214\346\243\213\345\255\220\347\232\204\347\247\273\345\212\250\345\217\257\344\273\245\344\270\200\346\255\245\346\255\245\345\234\250\346\234\211\347\233\264\347\272\277\350\277\236\346\216\245\347\232\204\347\233\270\351\202\273\345\205\255\344\270\252\346\226\271\345\220\221\350\277\233"
                        "\350\241\214\357\274\214\345\246\202\346\236\234\347\233\270\351\202\273\344\275\215\347\275\256\344\270\212\346\234\211\344\273\273\344\275\225\346\226\271\347\232\204\344\270\200\344\270\252\346\243\213\345\255\220\357\274\214\350\257\245\344\275\215\347\275\256\347\233\264\347\272\277\346\226\271\345\220\221\344\270\213\344\270\200\344\270\252\344\275\215\347\275\256\346\230\257\347\251\272\347\232\204\357\274\214\345\210\231\345\217\257\344\273\245\347\233\264\346\216\245\342\200\234\350\267\263\342\200\235\345\210\260\350\257\245\347\251\272\344\275\215\344\270\212\357\274\214\342\200\234\350\267\263\342\200\235\347\232\204\350\277\207\347\250\213\344\270\255\357\274\214\345\217\252\350\246\201\347\233\270\345\220\214\346\235\241\344\273\266\346\273\241\350\266\263\345\260\261\345\217\257\344\273\245\350\277\236\347\273\255\350\277\233\350\241\214\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style="
                        "\" font-family:'arial,\345\256\213\344\275\223,sans-serif'; font-size:16pt; font-weight:600; color:#333333; background-color:#ffffff;\">     \350\260\201\346\234\200\345\205\210\346\212\212\346\255\243\345\257\271\351\235\242\347\232\204\351\230\265\345\234\260\345\205\250\351\203\250\345\215\240\351\242\206\357\274\214\350\260\201\345\260\261\345\217\226\345\276\227\350\203\234\345\210\251\343\200\202</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class regulation: public Ui_regulation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGULATION_H
