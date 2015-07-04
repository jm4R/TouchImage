#include "saturatefilter.h"

SaturateFilter::SaturateFilter()
{
    name = tr("Nasycenie");
    defaultParameter = 500;
    parameter = 500;
}

SaturateFilter::~SaturateFilter()
{

}

uint SaturateFilter::processPixel(uint pixel)
{
    QColor color(pixel);

    int newSaturation = color.hslSaturation();
    newSaturation += newSaturation * 4 * parameter / 1000;
    if (newSaturation > 255) {
        newSaturation=255;
    }
    color.setHsl(color.hslHue(), newSaturation, color.lightness());
    return color.rgb();
}

