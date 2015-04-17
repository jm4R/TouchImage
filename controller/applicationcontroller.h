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
#include "view/filterwidget.h"
#include "view/brushwidget.h"
#include "view/colorwidget.h"

#include "model/historyprovider.h"

#include "toolsprovider.h"

//MOCK{
#include "model/grayscalefilter.h"
//}MOCK


class ApplicationController : public QObject
{
    Q_OBJECT
public:
    ApplicationController(QApplication &_application, MainView &_mainView);
    ~ApplicationController();
    int executeApplication();

private:
    //widgets:
    QApplication &application;
    MainView &mainView;
    DrawersWidget drawersWidget;
    ImageWidget imageWidget;
    LeftMenuWidget leftMenuWidget;
    RightMenuWidget rightMenuWidget;
    FilterWidget filterWidget;
    BrushWidget brushWidget;
    ColorWidget colorWidget;

    //other:
    ScreenAdapter screenAdapter;
    ToolsProvider toolsProvider;
    HistoryProvider historyProvider;


    void buildUI();
    void loadIcon(QToolButton *button, QString resourceName, float sizeCm);

public slots:
    //TODO temp
    void openFileButtonClicked();

    void brushesButtonClicked();
    void colorsButtonClicked();
    void filterButtonsClicked();
    void filterInvoked();
};

#endif // APPLICATIONaa_H
