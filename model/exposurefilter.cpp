#include "exposurefilter.h"

ExposureFilter::ExposureFilter()
{
    name = tr("Ekspozycja");
    defaultParameter = 550;
    parameter = 500;
}

ExposureFilter::~ExposureFilter()
{

}

uint ExposureFilter::processPixel(uint pixel)
{
    QColor color(pixel);

    double eV = -3.0 + (6.0 * parameter / 1000);
    double f = pow(2,eV);
    int newR = color.red() * f;
    int newG = color.green() * f;
    int newB = color.blue() * f;
    newR = newR > 255 ? 255 : newR;
    newG = newG > 255 ? 255 : newG;
    newB = newB > 255 ? 255 : newB;
    color.setRgb(newR, newG, newB);
    return color.rgb();
}

