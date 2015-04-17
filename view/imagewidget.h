#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QtWidgets>

/*QT_BEGIN_NAMESPACE
class QGestureEvent;
class QPanGesture;
class QPinchGesture;
class QSwipeGesture;
QT_END_NAMESPACE*/

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = 0);

public slots:
    void setImage(QImage *image);

protected:
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);
    void panTriggered(QPanGesture*);
    void pinchTriggered(QPinchGesture*);
    void swipeTriggered(QSwipeGesture*);

    void updateImage();

    QString path;
    QStringList files;
    int position;

    QImage *currentImage;

    qreal horizontalOffset;
    qreal verticalOffset;
    qreal scaleFactor;

signals:
    void gestureFinished();
};

#endif
