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

void ImageWidget::paintEvent(QPaintEvent*)
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
}

void ImageWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    scaleFactor = 1;
    verticalOffset = 0;
    horizontalOffset = 0;
    update();
}

bool ImageWidget::gestureEvent(QGestureEvent *event)
{
    if (QGesture *pan = event->gesture(Qt::PanGesture))
        panTriggered(static_cast<QPanGesture *>(pan));
    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    return true;
}

void ImageWidget::panTriggered(QPanGesture *gesture)
{
    QPointF delta = gesture->delta();
    horizontalOffset += delta.x();
    verticalOffset += delta.y();
    update();
}

void ImageWidget::pinchTriggered(QPinchGesture *gesture)
{
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        scaleFactor *= gesture->scaleFactor();
    }
    update();
}

void ImageWidget::resizeEvent(QResizeEvent*)
{
    update();
}

void ImageWidget::openDirectory(const QString &path)
{
    this->path = path;
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png";
    files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

    position = 0;
    goToImage(0);
    update();
}

QImage ImageWidget::loadImage(const QString &fileName)
{
    qDebug() << position << files << fileName;
    QImageReader reader(fileName);
    if (!reader.canRead()) {
        return QImage();
    }

    QImage image;
    if (!reader.read(&image)) {
        return QImage();
    }
    const QSize maximumSize(2000, 2000); // Reduce in case someone has large photo images.
    if (image.size().width() > maximumSize.width() || image.height() > maximumSize.height())
        image = image.scaled(maximumSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return image;
}

void ImageWidget::goToImage(int index)
{
    if (files.isEmpty())
        return;

    position = index;
    currentImage = loadImage(path+QLatin1String("/")+files.at(position));
    update();
}
