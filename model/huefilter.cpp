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

    int newHue = color.hslHue();
    if (newHue < 0) {
        return pixel;
    }
    newHue += 180 + (360.0 * parameter / 1000);
    if (newHue > 359) {
        newHue -= 360;
    }
    if (newHue > 359) {
        newHue -= 360;
    }
    color.setHsl(newHue, color.hslSaturation(), color.lightness());
    return color.rgb();
}

