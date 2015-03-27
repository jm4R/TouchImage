#include "controller/applicationcontroller.h"
#include "view/mainview.h"

int main(int argc, char *argv[])
{
    QApplication qtApplication(argc, argv);
    MainView mv;
    ApplicationController application(qtApplication, mv);
    return application.executeApplication();
}
