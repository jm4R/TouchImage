#include "saturatefilter.h"

SaturateFilter::SaturateFilter()
{
    name = tr("Nasycenie");
}

SaturateFilter::~SaturateFilter()
{

}

uint SaturateFilter::processPixel(uint pixel)
{
    QColor color(pixel);
    int newSaturation = color.hsvSaturation()*2;
    if (newSaturation > 255) {
        newSaturation=255;
    }
    color.setHsv(color.hsvHue(), newSaturation, color.value());
    return color.rgb();
}

