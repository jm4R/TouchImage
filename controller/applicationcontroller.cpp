#include "applicationcontroller.h"
#include "ui_leftmenuwidget.h"
#include "ui_rightmenuwidget.h"

ApplicationController::ApplicationController(QApplication &_application, MainView &_mainView) :
      application(_application),
      mainView(_mainView),
      drawersWidget(&mainView),
      imageWidget(&mainView),
      leftMenuWidget(&mainView)
{
    QFile File(":/res/style.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    application.setStyleSheet(styleSheet);
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
    connect(leftMenuWidget.ui->hideButton, &QToolButton::clicked, &drawersWidget, &DrawersWidget::hideDrawers);

    loadIcon(rightMenuWidget.ui->hideButton, "rightArrow.svg", 0.4f);
    loadIcon(rightMenuWidget.ui->openButton, "openFile.svg", 1.0f);
    loadIcon(rightMenuWidget.ui->redoButton, "redo.svg", 1.0f);
    loadIcon(rightMenuWidget.ui->saveButton, "saveFile.svg", 1.0f);
    loadIcon(rightMenuWidget.ui->undoButton, "undo.svg", 1.0f);
    connect(rightMenuWidget.ui->hideButton, &QToolButton::clicked, &drawersWidget, &DrawersWidget::hideDrawers);
    connect(rightMenuWidget.ui->undoButton, &QToolButton::clicked, &drawersWidget, &DrawersWidget::hideDrawers);
    connect(rightMenuWidget.ui->redoButton, &QToolButton::clicked, &drawersWidget, &DrawersWidget::hideDrawers);

    int menuWidth = screenAdapter.cmToPx(2.5);
    drawersWidget.setLeftWidget(&leftMenuWidget, menuWidth);
    drawersWidget.setRightWidget(&rightMenuWidget, menuWidth);
    drawersWidget.setHandlerWidth(screenAdapter.cmToPx(0.25));

    mainView.setCentralWidget(&drawersWidget);

    //MOCK{
    connect(rightMenuWidget.ui->openButton, &QToolButton::clicked, this, &ApplicationController::openFile);
    Filter *grayscaleFilter = new GrayscaleFilter;
    grayscaleFilter->setImage(imageWidget.getImage());
    connect(leftMenuWidget.ui->filtersButton, &QToolButton::clicked, grayscaleFilter, &Filter::process);
    connect(grayscaleFilter, SIGNAL(ready()), &imageWidget, SLOT(repaint()) );
    //}MOCK
}

void ApplicationController::loadIcon(QToolButton *button, QString resourceName, float sizeCm)
{
    QPixmap iconPixmap = screenAdapter.loadSvg(":/res/icons/" + resourceName, sizeCm);
    button->setIconSize(iconPixmap.size());
    button->setIcon(iconPixmap);
}

void ApplicationController::openFile()
{
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    const QString fileName =
        QFileDialog::getOpenFileName(&mainView, "Select image folder",
                                          picturesLocations.isEmpty() ? QString() : picturesLocations.front(), "Obrazy (*.png *.xpm *.jpg *.jpeg *.bmp);; Wszystkie pliki (*)");
    imageWidget.loadImage(fileName);
}

int ApplicationController::executeApplication()
{
    buildUI();
#ifndef Q_OS_ANDROID
    mainView.setMinimumSize(800, 600);
    mainView.show();
#else
    mainView.setWindowState( mainView.windowState()| Qt::WindowFullScreen);
    mainView.showFullScreen();
#endif
    return application.exec();
}
