#ifndef APPLICATIONaa_H
#define APPLICATIONaa_H
#include <QApplication>
#include "view/mainview.h"
#include "view/drawerswidget.h"
#include "view/imagewidget.h"


class ApplicationController : public QObject
{
    Q_OBJECT
public:
    ApplicationController(QApplication &_application, MainView &_mainView);
    ~ApplicationController();
    int executeApplication();

private:
    QApplication &application;
    MainView &mainView;
    DrawersWidget drawersWidget;
    ImageWidget imageWidget;

    void buildUI();
};

#endif // APPLICATIONaa_H
