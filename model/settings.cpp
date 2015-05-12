#include "settings.h"

Settings::Settings() :
  color(0,255,0),
  brushWidth(10)

{

}

Settings &Settings::instance()
{
    static Settings INSTANCE;
    return INSTANCE;
}

Settings::~Settings()
{

}

QColor Settings::getColor() const
{
    return color;
}

QMatrix Settings::getTransformationMatrix() const
{
    return transformationMatrix;
}

int Settings::getBrushWidth() const
{
    return brushWidth;
}

void Settings::setColor(QColor value)
{
    color = value;
}

void Settings::setTransformationMatrix(QMatrix value)
{
    transformationMatrix = value;
}

void Settings::setBrushWidth(int value)
{
    brushWidth = value;
}

