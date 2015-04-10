#include "grayscalefilter.h"

GrayscaleFilter::GrayscaleFilter(QObject *parent) : ColorFilter(parent)
{

}

GrayscaleFilter::~GrayscaleFilter()
{

}

uint GrayscaleFilter::processPixel(uint pixel)
{
    uint v = ( qRed(pixel) + qGreen(pixel) + qBlue(pixel) ) / 3;
    return qRgb(v,v,v);
}

