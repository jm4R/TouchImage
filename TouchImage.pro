#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T10:12:48
#
#-------------------------------------------------

QT       += core gui svg testlib

#TouchImage.pro
android {
    QT += androidextras
    SOURCES += model/androidfiledialog.cpp
    HEADERS += model/androidfiledialog.h
}
!android {
    SOURCES += model/qtfiledialog.cpp
    HEADERS += model/qtfiledialog.h
}

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
    view/rightmenuwidget.cpp \
    model/filter.cpp \
    model/filterprocess.cpp \
    model/colorfilter.cpp \
    model/grayscalefilter.cpp \
    controller/toolsprovider.cpp \
    view/filterwidget.cpp \
    model/sepiafilter.cpp \
    model/negativefilter.cpp \
    model/saturatefilter.cpp \
    view/brushwidget.cpp \
    model/splotfilter.cpp \
    model/denoisefilter.cpp \
    model/historyprovider.cpp \
    qt_lgpl_utils/qcolorpicker.cpp \
    qt_lgpl_utils/qcolorluminancepicker.cpp \
    view/colorwidget.cpp \
    view/toast.cpp \
    model/brush.cpp \
    model/settings.cpp \
    model/filedialogstrategy.cpp \
    model/lightnessfilter.cpp \
    model/exposurefilter.cpp \
    model/huefilter.cpp \
    model/gammafilter.cpp \
    model/gaussfilter.cpp \
    tests/historyprovidertest.cpp

HEADERS  += view/mainview.h \
    view/drawerswidget.h \
    view/imagewidget.h \
    controller/applicationcontroller.h \
    view/leftmenuwidget.h \
    view/screenadapter.h \
    view/rightmenuwidget.h \
    model/filter.h \
    model/filterprocess.h \
    model/colorfilter.h \
    model/grayscalefilter.h \
    controller/toolsprovider.h \
    view/filterwidget.h \
    model/sepiafilter.h \
    model/negativefilter.h \
    model/saturatefilter.h \
    view/brushwidget.h \
    model/splotfilter.h \
    model/denoisefilter.h \
    model/historyprovider.h \
    qt_lgpl_utils/qcolorpicker.h \
    qt_lgpl_utils/qcolorluminancepicker.h \
    view/colorwidget.h \
    view/toast.h \
    model/brush.h \
    model/settings.h \
    model/filedialogstrategy.h \
    model/lightnessfilter.h \
    model/exposurefilter.h \
    model/huefilter.h \
    model/gammafilter.h \
    model/gaussfilter.h \
    tests/historyprovidertest.h

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources/resources.qrc

FORMS += \
    view/leftmenuwidget.ui \
    view/rightmenuwidget.ui \
    view/filterwidget.ui \
    view/brushwidget.ui \
    view/colorwidget.ui

CONFIG += c++11

DISTFILES += \
    resources/TODO.txt \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle

TRANSLATIONS = translations/translation_pl_PL.ts

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
