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
    //MOCK{
    Settings &s = Settings::instance();
    QPainter painter(image);
    painter.setMatrix(s.getTransformationMatrix());
    QPen pen;
    QBrush brush;
    pen.setBrush(brush);
    pen.setColor(s.getColor());
    pen.setWidth(s.getBrushWidth());
    painter.setPen(pen);
    painter.drawPath(path);
    //}MOCK
}

QString Brush::getName() const
{
    return name;
}
