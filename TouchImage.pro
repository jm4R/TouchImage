#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T10:12:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TouchImage
TEMPLATE = app


SOURCES += main.cpp\
    view/mainview.cpp \
    view/drawerswidget.cpp \
    view/imagewidget.cpp \
    controller/applicationcontroller.cpp

HEADERS  += view/mainview.h \
    view/drawerswidget.h \
    view/imagewidget.h \
    controller/applicationcontroller.h

CONFIG += mobility
MOBILITY = 

