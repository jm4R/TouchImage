#ifndef LEFTMENUWIDGET_H
#define LEFTMENUWIDGET_H

#include <QFrame>
#include <QButtonGroup>

namespace Ui {
class LeftMenuWidget;
}

class LeftMenuWidget : public QFrame
{
    Q_OBJECT

public:
    explicit LeftMenuWidget(QWidget *parent = 0);
    ~LeftMenuWidget();

public:
    Ui::LeftMenuWidget *ui;

private:
    QButtonGroup buttonGroup;
};

#endif // LEFTMENUWIDGET_H
