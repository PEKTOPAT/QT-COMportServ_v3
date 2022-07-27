#-------------------------------------------------
#
# Project created by QtCreator 2022-07-26T15:12:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = comPortGenerateThread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generatedatathread.cpp

HEADERS  += mainwindow.h \
    generatedatathread.h

FORMS    += mainwindow.ui
