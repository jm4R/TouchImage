#include "screenadapter.h"
#include <QSvgRenderer>
#include <QPainter>

ScreenAdapter::ScreenAdapter(QObject *parent) : QObject(parent), screen(qApp->primaryScreen())
{

}

ScreenAdapter::~ScreenAdapter()
{

}

int ScreenAdapter::cmToPx(float cm)
{
    return screen->physicalDotsPerInch() * cm / INCH_PER_CM;
}

QPixmap ScreenAdapter::loadSvg(QString resourceName, float maxWidthCm, float maxHeightCm)
{
    QSvgRenderer renderer(resourceName);
    QSize defaultSize = renderer.defaultSize();
    double widthToHeightFactor = double(defaultSize.width()) / defaultSize.height();
    double requestedWidthToHeight = double(maxWidthCm) / maxHeightCm;
    float width, height;
    if (widthToHeightFactor < requestedWidthToHeight) {
        height = cmToPx(maxHeightCm);
        width = widthToHeightFactor * height;
    } else {
        width = cmToPx(maxWidthCm);
        height = width / widthToHeightFactor;
    }

    QPixmap result(width, height);
    result.fill(QColor(255,255,255,0));
    QPainter painter(&result);
    renderer.render(&painter, result.rect());

    return qMove(result);
}

