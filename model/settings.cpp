#include "settings.h"

Settings::Settings()
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

QMatrix Settings::getTransformationMatrix() const
{
    return transformationMatrix;
}

void Settings::setTransformationMatrix(QMatrix value)
{
    transformationMatrix = value;
}
bool Settings::getAntialiasing() const
{
    return antialiasing;
}

void Settings::setAntialiasing(bool value)
{
    antialiasing = value;
}

QPen Settings::getPen() const
{
    return pen;
}

void Settings::setPen(QPen value)
{
    pen = value;
}
