#ifndef RIGHTMENUWIDGET_H
#define RIGHTMENUWIDGET_H

#include <QFrame>

namespace Ui {
class RightMenuWidget;
}

class RightMenuWidget : public QFrame
{
    Q_OBJECT

public:
    explicit RightMenuWidget(QWidget *parent = 0);
    ~RightMenuWidget();

public:
    Ui::RightMenuWidget *ui;
};

#endif // RIGHTMENUWIDGET_H
