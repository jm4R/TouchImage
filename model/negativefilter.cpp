#include "negativefilter.h"

NegativeFilter::NegativeFilter()
{

}

NegativeFilter::~NegativeFilter()
{

}

uint NegativeFilter::processPixel(uint pixel)
{
    uint iR = qRed(pixel);
    uint iG = qGreen(pixel);
    uint iB = qBlue(pixel);
    return qRgb(255-iR, 255-iG, 255-iB);
}

