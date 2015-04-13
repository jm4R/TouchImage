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
    return mergePixel( pixel, qGray(pixel) );
}

