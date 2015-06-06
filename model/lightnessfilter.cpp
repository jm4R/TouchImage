#include "lightnessfilter.h"
#include <QColor>

LightnessFilter::LightnessFilter()
{
    name = tr("Jasność");
    defaultParameter = 550;
    parameter = 500;
}

LightnessFilter::~LightnessFilter()
{

}

uint LightnessFilter::processPixel(uint pixel)
{
    QColor color(pixel);

    int newLightness = color.lightness() - 255 + (510.0 * parameter / 1000);
    if (newLightness > 255) {
        newLightness=255;
    } else if (newLightness < 0) {
        newLightness = 0;
    }
    color.setHsl(color.hslHue(), color.hslSaturation(), newLightness);
    return color.rgb();
}
