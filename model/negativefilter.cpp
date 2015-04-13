#include "negativefilter.h"

NegativeFilter::NegativeFilter()
{
    name = tr("Negatyw");
    defaultParameter = 1000;
    parameter = 1000;
}

NegativeFilter::~NegativeFilter()
{

}

uint NegativeFilter::processPixel(uint pixel)
{
    uint iR = qRed(pixel);
    uint iG = qGreen(pixel);
    uint iB = qBlue(pixel);
    return mergePixel( pixel, qRgb(255-iR, 255-iG, 255-iB) );
}

