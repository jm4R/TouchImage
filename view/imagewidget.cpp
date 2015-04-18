#include "imagewidget.h"

#include <QtWidgets>

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent),

    position(0),
    currentImage(0),
    horizontalOffset(0),
    verticalOffset(0),
    scaleFactor(1),
    path(0)
{
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
}

ImageWidget::~ImageWidget()
{
    delete path;
}

bool ImageWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QWidget::event(event);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    if (!currentImage) {
        return;
    }
    QPainter p(this);

    QMatrix &&m = calculateMatrix();
    p.setMatrix(m);
    p.drawImage(0, 0, *currentImage);
    if (path) {
        p.setMatrixEnabled(false);
        p.drawPath(*path);
    }

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

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    delete path;
    path = new QPainterPath(event->pos());
    startPoint = event->pos();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (path) {
        path->lineTo(event->pos());
        update();
    }
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (path) {
        path->lineTo(event->pos());
        update();
        QMatrix invertedMatrix = calculateMatrix().inverted();
        QPolygonF &&polygon = path->toFillPolygon(invertedMatrix);
        QPointF startPointT = invertedMatrix.map(startPoint);
        delete path; path = 0;
        emit pathDrawn(qMove(polygon), startPointT);
    }
}

bool ImageWidget::gestureEvent(QGestureEvent *event)
{
    if (QGesture *pan = event->gesture(Qt::PanGesture))
        panTriggered(static_cast<QPanGesture *>(pan));
    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    delete path; path = 0;
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

QMatrix ImageWidget::calculateMatrix()
{
    const qreal iw = currentImage->width();
    const qreal ih = currentImage->height();
    const qreal wh = height();
    const qreal ww = width();

    QMatrix m;
    m.translate(ww/2, wh/2);
    m.translate(horizontalOffset, verticalOffset);
    m.scale(scaleFactor, scaleFactor);
    m.translate(-iw/2, -ih/2);
    return qMove(m);
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    update();
    event->accept();
}

void ImageWidget::setImage(QImage *image)
{
    currentImage = image;
    update();
}
