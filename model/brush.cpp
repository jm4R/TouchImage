#include "brush.h"
#include "settings.h"

Brush::Brush(QObject *parent) : QObject(parent)
{

}

Brush::~Brush()
{

}

QImage *Brush::getImage() const
{
    return image;
}

void Brush::setImage(QImage *value)
{
    image = value;
}

void Brush::process(QPainterPath path)
{
    Settings &s = Settings::instance();
    QPainter painter(image);
    painter.setMatrix(s.getTransformationMatrix());
    painter.setRenderHint(QPainter::Antialiasing, s.getAntialiasing());
    painter.setPen(s.getPen());
    painter.drawPath(path);
}

QString Brush::getName() const
{
    return name;
}
