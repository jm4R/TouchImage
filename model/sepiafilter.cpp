#include "sepiafilter.h"

SepiaFilter::SepiaFilter()
{
    name = tr("Sepia");
    defaultParameter = 1000;
    parameter = 1000;
}

SepiaFilter::~SepiaFilter()
{

}

uint SepiaFilter::processPixel(uint pixel)
{
    uint iR = qRed(pixel);
    uint iG = qGreen(pixel);
    uint iB = qBlue(pixel);
    uint r = (iR * .393) + (iG *.769) + (iB * .189);
    uint g = (iR * .349) + (iG *.686) + (iB * .168);
    uint b = (iR * .272) + (iG *.534) + (iB * .131);
    uint out = qRgb(r <= 255 ? r : 255, g <= 255 ? g : 255, b <= 255 ?b : 255);
    return mergePixel(pixel, out);
}

