#include "grayscalefilter.h"

GrayscaleFilter::GrayscaleFilter(QObject *parent) : ColorFilter(parent)
{
    name = tr("Desaturacja");
    defaultParameter = 1000;
    parameter = 1000;
}

GrayscaleFilter::~GrayscaleFilter()
{

}

uint GrayscaleFilter::processPixel(uint pixel)
{
    uint v = qGray(pixel);
    return mergePixel( pixel, qRgb(v,v,v) );
}

