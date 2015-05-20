#ifndef BRUSHWIDGET_H
#define BRUSHWIDGET_H

#include <QFrame>
#include <QResizeEvent>

namespace Ui {
class BrushWidget;
}

class BrushWidget : public QFrame
{
    Q_OBJECT

public:
    explicit BrushWidget(QWidget *parent = 0);
    ~BrushWidget();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::BrushWidget *ui;

private slots:
    void updatePreview();
};


#endif // BRUSHWIDGET_H
