#include "gammafilter.h"

GammaFilter::GammaFilter()
{
    name = tr("Gamma");
    defaultParameter = 550;
    parameter = 500;
}

GammaFilter::~GammaFilter()
{

}

uint GammaFilter::processPixel(uint pixel)
{
    QColor color(pixel);

    double f = -3.0 + (6.0 * parameter / 1000);
    double gamma = pow(2,f);
    double newLightness = pow(color.lightnessF(), gamma);
    color.setHsl(color.hslHue(), color.hslSaturation(), newLightness*255);
    return color.rgb();
}

