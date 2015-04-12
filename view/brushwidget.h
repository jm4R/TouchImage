#ifndef BRUSHWIDGET_H
#define BRUSHWIDGET_H

#include <QFrame>

namespace Ui {
class BrushWidget;
}

class BrushWidget : public QFrame
{
    Q_OBJECT

public:
    explicit BrushWidget(QWidget *parent = 0);
    ~BrushWidget();

private:
    Ui::BrushWidget *ui;
};

#endif // BRUSHWIDGET_H
