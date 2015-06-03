#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T10:53:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = haffman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp
QMAKE_CXXFLAGS += -std=c++11

HEADERS  += mainwindow.h \
    haffman.h

FORMS    += mainwindow.ui
