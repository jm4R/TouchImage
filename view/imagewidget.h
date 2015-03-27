#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QGestureEvent;
class QPanGesture;
class QPinchGesture;
class QSwipeGesture;
QT_END_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(lcExample)

//! [class definition begin]
class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = 0);
    void openDirectory(const QString &path);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    bool gestureEvent(QGestureEvent *event);
    void panTriggered(QPanGesture*);
    void pinchTriggered(QPinchGesture*);
    void swipeTriggered(QSwipeGesture*);
//! [class definition begin]

    void updateImage();
    QImage loadImage(const QString &fileName);
    void loadImage();
    void goToImage(int index);

    QString path;
    QStringList files;
    int position;

    QImage currentImage;

    qreal horizontalOffset;
    qreal verticalOffset;
    qreal scaleFactor;
};

#endif
