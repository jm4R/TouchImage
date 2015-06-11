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
#include "view/toast.h"

#ifdef Q_OS_ANDROID
#include "model/androidfiledialog.h"
#else
#include "model/qtfiledialog.h"
#endif


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
    Toast toast;
    FileDialogStrategy *fileDialog;

    void buildUI();
    void connectViewModel();
    void setDefaults();
    void loadIcon(QToolButton *button, QString resourceName, float sizeCm);

public slots:

    void openFileNameReady(QString fileName);

    void brushesButtonClicked();
    void colorsButtonClicked();
    void filterButtonsClicked();
    void openFileButtonClicked();
    void filterInvoked();
    void brushInvoked(QPainterPath path);
    void operationFinished(int time);

private slots:
    void showMessage(QString message);
};

#endif // APPLICATIONaa_H
