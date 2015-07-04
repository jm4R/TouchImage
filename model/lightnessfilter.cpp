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
    int toAdd = (int) (- 255 + (510.0 * parameter / 1000));
    QColor color(pixel);

    int newR = color.red() + toAdd;
    int newG = color.green() + toAdd;
    int newB = color.blue() + toAdd;
    if (newR > 255) {
        newR=255;
    } else if (newR < 0) {
        newR = 0;
    }
    if (newG > 255) {
        newG=255;
    } else if (newG < 0) {
        newG = 0;
    }
    if (newB > 255) {
        newB=255;
    } else if (newB < 0) {
        newB = 0;
    }

    color.setRgb(newR, newG, newB);
    return color.rgb();
}
