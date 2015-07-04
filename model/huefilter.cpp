#include "huefilter.h"

HueFilter::HueFilter()
{
    name = tr("Odcień");
    defaultParameter = 0;
    parameter = 500;
}

HueFilter::~HueFilter()
{

}

uint HueFilter::processPixel(uint pixel)
{
    QColor color(pixel);

    int newHue = color.hsvHue();
    if (newHue < 0) {
        return pixel;
    }
    newHue += 180 + (360.0 * parameter / 1000);
    newHue %= 360;
    color.setHsv(newHue, color.hsvSaturation(), color.value());
    return color.rgb();
}

