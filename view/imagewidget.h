#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QtWidgets>

/**
 * @brief
 * Klasa odpowiadająca za wyświetlanie i zarządzanie widżetem głównego widoku edytowanej grafiki.
 */
class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = 0);
    ~ImageWidget();

public slots:
    void setImage(QImage *image);
    void setPen(QPen value);
    void setAntialiasing(bool value);

protected:
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);
    void panTriggered(QPanGesture*);
    void pinchTriggered(QPinchGesture*);
    void updateImage();
    QMatrix calculateMatrix();

    QImage *currentImage;

    qreal horizontalOffset;
    qreal verticalOffset;
    qreal scaleFactor;

    QPainterPath *path;
    QPen pen;
    bool antialiasing;

signals:
    void gestureFinished();
    void pathDrawn(QPainterPath polygon);
    void matrixChanged(QMatrix matrix);
};

#endif
