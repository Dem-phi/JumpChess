#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T10:18:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JumpChess
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    gameplay.cpp \
    boardmatrix.cpp \
    piece.cpp \
    mystack.cpp \
    graph.cpp \
    aigame.cpp \
    change.cpp \
    regulation.cpp \
    choose.cpp \
    gameover.cpp \
    record.cpp \
    userdata.cpp

HEADERS  += mainwindow.h \
    gameplay.h \
    boardmatrix.h \
    piece.h \
    graph.h \
    mystack.h \
    aigame.h \
    change.h \
    regulation.h \
    choose.h \
    gameover.h \
    record.h \
    userdata.h

FORMS    += mainwindow.ui \
    gameplay.ui \
    aigame.ui \
    regulation.ui \
    choose.ui \
    gameover.ui \
    record.ui

DISTFILES +=

RESOURCES += \
    res.qrc
