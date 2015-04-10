#include "imagewidget.h"

#include <QtWidgets>

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent),
    position(0),
    horizontalOffset(0),
    verticalOffset(0),
    scaleFactor(1)

{
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
}

bool ImageWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QWidget::event(event);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    const qreal iw = currentImage.width();
    const qreal ih = currentImage.height();
    const qreal wh = height();
    const qreal ww = width();

    p.translate(ww/2, wh/2);
    p.translate(horizontalOffset, verticalOffset);
    p.scale(scaleFactor, scaleFactor);
    p.translate(-iw/2, -ih/2);
    p.drawImage(0, 0, currentImage);

    event->accept();
}

void ImageWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    scaleFactor = 1;
    verticalOffset = 0;
    horizontalOffset = 0;
    update();
    event->accept();
}

bool ImageWidget::gestureEvent(QGestureEvent *event)
{
    if (QGesture *pan = event->gesture(Qt::PanGesture))
        panTriggered(static_cast<QPanGesture *>(pan));
    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    event->accept();
    return true;
}

void ImageWidget::panTriggered(QPanGesture *gesture)
{
    QPointF delta = gesture->delta();
    horizontalOffset += delta.x();
    verticalOffset += delta.y();
    update();
    if (gesture->state() == Qt::GestureFinished) {
        emit gestureFinished();
        releaseMouse();
    }
}

void ImageWidget::pinchTriggered(QPinchGesture *gesture)
{
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        scaleFactor *= gesture->scaleFactor();
    }
    update();
    if (gesture->state() == Qt::GestureFinished) {
        emit gestureFinished();
        releaseMouse();
    }
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    update();
    event->accept();
}

bool ImageWidget::loadImage(const QString &fileName)
{
    QImageReader reader(fileName);
    if (!reader.canRead()) {
        return false;
    }

    QImage image;
    if (!reader.read(&image)) {
        return false;
    }
    currentImage = image;
    update();
    return true;
}

QImage *ImageWidget::getImage()
{
    return &currentImage;
}
