#include "applicationcontroller.h"
#include "ui_leftmenuwidget.h"
#include "ui_rightmenuwidget.h"
#include "model/settings.h"


ApplicationController::ApplicationController(QApplication &_application, MainView &_mainView) :
      QObject(&_application),
      application(_application),
      mainView(_mainView),
      drawersWidget(&_mainView),
      imageWidget(&drawersWidget),
      leftMenuWidget(&drawersWidget),
      toast (&drawersWidget)
{
    QFile styleFile(":/res/style.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    qApp->setStyleSheet(styleSheet);
    styleFile.close();

    #ifdef Q_OS_ANDROID
    fileDialog = new AndroidFileDialog(this);
    #else
    fileDialog = new QtFileDialog(this);
    #endif
}

ApplicationController::~ApplicationController()
{

}

void ApplicationController::buildUI()
{
    drawersWidget.setBottomWidget(&imageWidget);

    loadIcon(leftMenuWidget.ui->brushesButton, "brush.svg", 1.0f);
    loadIcon(leftMenuWidget.ui->filtersButton, "filter.svg", 1.0f);
    loadIcon(leftMenuWidget.ui->colorsButton, "color.svg", 1.0f);
    loadIcon(leftMenuWidget.ui->hideButton, "leftArrow.svg", 0.4f);

    filterButtonsClicked();

    loadIcon(rightMenuWidget.ui->hideButton, "rightArrow.svg", 0.4f);
    loadIcon(rightMenuWidget.ui->openButton, "openFile.svg", 1.0f);
    loadIcon(rightMenuWidget.ui->redoButton, "redo.svg", 1.0f);
    loadIcon(rightMenuWidget.ui->saveButton, "saveFile.svg", 1.0f);
    loadIcon(rightMenuWidget.ui->undoButton, "undo.svg", 1.0f);

    int menuWidth = screenAdapter.cmToPx(2.5);
    drawersWidget.setLeftWidget(&leftMenuWidget, menuWidth);
    drawersWidget.setRightWidget(&rightMenuWidget, menuWidth);
    drawersWidget.setHandlerWidth(screenAdapter.cmToPx(0.25));

    mainView.setCentralWidget(&drawersWidget);

    QImage exampleImage = screenAdapter.loadRaster(":/res/icons/example.jpg", 5.0f, 1.5f);
    filterWidget.putButtonGroup(toolsProvider.generateButtonGroup(exampleImage));

}

void ApplicationController::connectViewModel()
{
    //left menu:
    connect(leftMenuWidget.ui->hideButton, SIGNAL(clicked()), &drawersWidget, SLOT(hideDrawers()));
    connect(leftMenuWidget.ui->brushesButton, SIGNAL(clicked()), this, SLOT(brushesButtonClicked()));
    connect(leftMenuWidget.ui->colorsButton, SIGNAL(clicked()), this, SLOT(colorsButtonClicked()));
    connect(leftMenuWidget.ui->filtersButton, SIGNAL(clicked()), this, SLOT(filterButtonsClicked()));

    //right menu:
    connect(rightMenuWidget.ui->openButton, SIGNAL(clicked()), &drawersWidget, SLOT(hideDrawers()));
    connect(rightMenuWidget.ui->saveButton, SIGNAL(clicked()), &drawersWidget, SLOT(hideDrawers()));
    connect(rightMenuWidget.ui->hideButton, SIGNAL(clicked()), &drawersWidget, SLOT(hideDrawers()));
    connect(rightMenuWidget.ui->undoButton, SIGNAL(clicked()), &drawersWidget, SLOT(hideDrawers()));
    connect(rightMenuWidget.ui->redoButton, SIGNAL(clicked()), &drawersWidget, SLOT(hideDrawers()));
    connect(rightMenuWidget.ui->openButton, &QToolButton::clicked, this, &ApplicationController::openFileButtonClicked);
    connect(rightMenuWidget.ui->saveButton, &QToolButton::clicked, this, &ApplicationController::saveFileButtonClicked);
    connect(&historyProvider, SIGNAL(undoStatusChanged(bool)), rightMenuWidget.ui->undoButton, SLOT(setEnabled(bool)));
    connect(&historyProvider, SIGNAL(redoStatusChanged(bool)), rightMenuWidget.ui->redoButton, SLOT(setEnabled(bool)));
    connect(rightMenuWidget.ui->undoButton, SIGNAL(clicked()), &historyProvider, SLOT(undo()));
    connect(rightMenuWidget.ui->redoButton, SIGNAL(clicked()), &historyProvider, SLOT(redo()));

    //filter widget:
    connect(&toolsProvider, SIGNAL(currentFilterChanged(Filter*)), &filterWidget, SLOT(setFilter(Filter*)));
    connect(&filterWidget, SIGNAL(filterInvoked()), this, SLOT(filterInvoked()));
    connect(&historyProvider, SIGNAL(currentImageChanged(QImage*)), &filterWidget, SLOT(setImage(QImage*)));

    //image widget:
    connect(&historyProvider, SIGNAL(currentImageChanged(QImage*)), &imageWidget, SLOT(setImage(QImage*)));
    connect(&imageWidget, SIGNAL(matrixChanged(QMatrix)), &Settings::instance(), SLOT(setTransformationMatrix(QMatrix)));
    connect(&imageWidget, SIGNAL(pathDrawn(QPainterPath)), this, SLOT(brushInvoked(QPainterPath)));

    //color widget:
    connect(&colorWidget, SIGNAL(colorChanged(QColor)), &brushWidget, SLOT(setColor(QColor)));

    //brush widget:
    connect(&brushWidget, SIGNAL(penChanged(QPen)), &Settings::instance(), SLOT(setPen(QPen)));
    connect(&brushWidget, SIGNAL(antialiasingChanged(bool)), &Settings::instance(), SLOT(setAntialiasing(bool)));
    connect(&brushWidget, SIGNAL(penChanged(QPen)), &imageWidget, SLOT(setPen(QPen)));
    connect(&brushWidget, SIGNAL(antialiasingChanged(bool)), &imageWidget, SLOT(setAntialiasing(bool)));

    //open file dialog:
    connect(fileDialog, SIGNAL(existingFileNameReady(QString)), this, SLOT(openFileNameReady(QString)));

    //toast:
    connect(&historyProvider, SIGNAL(operationFinished(int)), this, SLOT(operationFinished(int)));
    connect(&historyProvider, SIGNAL(errorOccured(QString)), this, SLOT(showMessage(QString)));
}

void ApplicationController::setDefaults()
{
    colorWidget.setHsv(0,0,255);

}

void ApplicationController::loadIcon(QToolButton *button, QString resourceName, float sizeCm)
{
    QPixmap iconPixmap = screenAdapter.loadSvg(":/res/icons/" + resourceName, sizeCm);
    button->setIconSize(iconPixmap.size());
    button->setIcon(iconPixmap);
}

void ApplicationController::openFileButtonClicked()
{
    bool success = fileDialog->provideExistingFileName();
    if (!success) {
        toast.showToast(tr("Failed to open file"));
    }
}

void ApplicationController::saveFileButtonClicked()
{
    QImage *currentImage = historyProvider.getCurrentImage();
    if (currentImage) {
        QString dirPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        QString fileName = QDateTime::currentDateTime().toString("TouchImage_yyMMdd_hhmmss.png");
        QString fullPath = dirPath + "/" + fileName;
        bool success = currentImage->save(fullPath);
        if (!success) {
            toast.showToast(tr("Failed to save file"));
        } else {
            toast.showToast(fileName + tr(" saved"));
        }
    } else {
        toast.showToast(tr("Nothing to save"));
    }
}

void ApplicationController::openFileNameReady(QString fileName)
{

    QImageReader reader(fileName);
    if (!reader.canRead()) {
        toast.showToast(tr("Failed to open file"));
    }

    QImage *newImage = new QImage();
    if (!reader.read(newImage)) {
        toast.showToast(tr("Failed to open file"));
    }
    historyProvider.resetToImage(newImage);
}

void ApplicationController::brushesButtonClicked()
{
    drawersWidget.setTopWidgetToLeft(&brushWidget);
}

void ApplicationController::colorsButtonClicked()
{
    drawersWidget.setTopWidgetToLeft(&colorWidget);
}

void ApplicationController::filterButtonsClicked()
{
    drawersWidget.setTopWidgetToLeft(&filterWidget);
}

void ApplicationController::filterInvoked()
{
    Filter *filter = toolsProvider.getCurrentFilter();
    historyProvider.doFilterAndAppend(filter);
}

void ApplicationController::brushInvoked(QPainterPath path)
{
    Brush *brush = toolsProvider.getCurrentBrush();
    historyProvider.doBrushAndAppend(brush, path);
}

void ApplicationController::operationFinished(int time)
{
    toast.showToast(QString::number(time) + "ms");
}

void ApplicationController::showMessage(QString message)
{
    toast.showToast(message);
}

int ApplicationController::executeApplication()
{
    buildUI();
    connectViewModel();
    setDefaults();
#ifndef Q_OS_ANDROID
    mainView.setMinimumSize(960, 540);
    mainView.show();
#else
    mainView.setWindowState( mainView.windowState()| Qt::WindowFullScreen);
    mainView.showFullScreen();
#endif
    return application.exec();
}
