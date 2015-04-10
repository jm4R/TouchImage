#include "grayscalefilter.h"

GrayscaleFilter::GrayscaleFilter()
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

