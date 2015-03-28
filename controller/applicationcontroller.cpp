#include "applicationcontroller.h"

ApplicationController::ApplicationController(QApplication &_application, MainView &_mainView) :
      application(_application),
      mainView(_mainView),
      drawersWidget(&mainView),
      imageWidget(&mainView)
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
    mainView.setCentralWidget(&drawersWidget);

    //MOCK{
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    const QString directory =
        QFileDialog::getExistingDirectory(&mainView, "Select image folder",
                                          picturesLocations.isEmpty() ? QString() : picturesLocations.front());
    imageWidget.openDirectory(directory);
    //}MOCK
    //Insert your code here
}

int ApplicationController::executeApplication()
{
    buildUI();
    mainView.show();
    return application.exec();
}
