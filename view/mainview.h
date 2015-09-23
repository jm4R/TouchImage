#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

/**
 * @brief
 * Klasa odpowiadająca za wyświetlanie i zarządzanie widżetem głównego okna/widoku aplikacji.
 */
class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();
};

#endif // MAINVIEW_H
