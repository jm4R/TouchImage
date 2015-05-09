#include "brush.h"

QMatrix Brush::transformationMatrix;

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
    QPainter painter(image);
    painter.setMatrix(transformationMatrix);
    QPen pen;
    QBrush brush;
    brush.setColor(QColor(255,0,0));
    pen.setBrush(brush);
    pen.setColor(QColor(0,255,0));
    pen.setWidth(15);
    painter.setPen(pen);
    painter.drawPath(path);
    //}MOCK
}

QString Brush::getName() const
{
    return name;
}

void Brush::setTransformationMatrix(QMatrix matrix)
{
    transformationMatrix = matrix;
}

