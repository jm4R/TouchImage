#include "controller/applicationcontroller.h"
#include "view/mainview.h"

#include "tests/historyprovidertest.h"

//#define RUN_TESTS

int main(int argc, char *argv[])
{
#ifdef RUN_TESTS
    HistoryProviderTest *test = new HistoryProviderTest();
    QTest::qExec(test);
    delete test;
#endif

    QApplication qtApplication(argc, argv);

    QTranslator translator;
    QString fileName = "translation_" + QLocale::system().name();
    QString directoryPath = ":/res/translations/";
    bool success = translator.load(fileName, directoryPath);
    success = success && qtApplication.installTranslator(&translator);
    success = success && !translator.isEmpty();
    if (!success) {
        qWarning("Translation for system language not found, using default...");
    }

    MainView mv;
    ApplicationController application(qtApplication, mv);
    return application.executeApplication();
}
