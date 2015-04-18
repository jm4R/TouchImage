#include "brush.h"

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

void Brush::process(QPolygonF polygon, QPointF start)
{
    //MOCK{
    QPainter painter(image);
    QPen pen;
    QBrush brush;
    brush.setColor(QColor(255,0,0));
    pen.setBrush(brush);
    pen.setColor(QColor(0,255,0));
    pen.setWidth(15);
    painter.setPen(pen);
    painter.drawPolygon(polygon);
    //}MOCK
}

QString Brush::getName() const
{
    return name;
}

