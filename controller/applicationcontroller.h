#ifndef APPLICATIONaa_H
#define APPLICATIONaa_H
#include <QApplication>
#include <QString>
#include "view/mainview.h"
#include "view/drawerswidget.h"
#include "view/imagewidget.h"
#include "view/leftmenuwidget.h"
#include "view/rightmenuwidget.h"
#include "view/screenadapter.h"


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
    LeftMenuWidget leftMenuWidget;
    RightMenuWidget rightMenuWidget;
    ScreenAdapter screenAdapter;

    void buildUI();
    void loadIcon(QToolButton *button, QString resourceName, float sizeCm);
};

#endif // APPLICATIONaa_H
