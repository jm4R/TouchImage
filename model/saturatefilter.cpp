#include "saturatefilter.h"

SaturateFilter::SaturateFilter()
{
    name = tr("Nasycenie");
    defaultParameter = 50;
    parameter = 50;
}

SaturateFilter::~SaturateFilter()
{

}

uint SaturateFilter::processPixel(uint pixel)
{
    QColor color(pixel);
    int newSaturation = color.hsvSaturation()*4;
    if (newSaturation > 255) {
        newSaturation=255;
    }
    color.setHsv(color.hsvHue(), newSaturation, color.value());
    return color.rgb();
}

