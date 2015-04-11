#ifndef SCREENADAPTER_H
#define SCREENADAPTER_H

#include <QObject>
#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <cfloat>

class ScreenAdapter : public QObject
{
    Q_OBJECT
public:
    explicit ScreenAdapter(QObject *parent = 0);
    ~ScreenAdapter();

    int cmToPx(float cm);
    QPixmap loadSvg(QString resourceName, float maxWidthCm, float maxHeightCm = FLT_MAX);
    QImage loadRaster(QString resourceName, float maxWidthCm, float maxHeightCm = FLT_MAX);

private:
    static constexpr float INCH_PER_CM = 2.54f;
    QScreen *screen;
signals:

public slots:
};

#endif // SCREENADAPTER_H
