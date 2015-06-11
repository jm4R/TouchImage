#ifndef BRUSHWIDGET_H
#define BRUSHWIDGET_H

#include <QFrame>
#include <QResizeEvent>
#include <QPen>

namespace Ui {
class BrushWidget;
}

class BrushWidget : public QFrame
{
    Q_OBJECT

public:
    explicit BrushWidget(QWidget *parent = 0);
    ~BrushWidget();

public slots:
    void setColor(QColor color);

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    QPen generatePen();
    void drawPreview(QPen pen, bool antialiasing);
    Ui::BrushWidget *ui;
    QColor color;
    QSize size;
    QPainterPath path;

private slots:
    void updatePen();

signals:
    void penChanged(QPen pen);
    void antialiasingChanged(bool antialiasing);
};


#endif // BRUSHWIDGET_H
