#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T10:12:48
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TouchImage
TEMPLATE = app


SOURCES += main.cpp\
    view/mainview.cpp \
    view/drawerswidget.cpp \
    view/imagewidget.cpp \
    controller/applicationcontroller.cpp \
    view/leftmenuwidget.cpp \
    view/screenadapter.cpp \
    view/rightmenuwidget.cpp

HEADERS  += view/mainview.h \
    view/drawerswidget.h \
    view/imagewidget.h \
    controller/applicationcontroller.h \
    view/leftmenuwidget.h \
    view/screenadapter.h \
    view/rightmenuwidget.h

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources/resources.qrc

FORMS += \
    view/leftmenuwidget.ui \
    view/rightmenuwidget.ui

CONFIG += c++11
