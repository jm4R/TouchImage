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
    double r = color.red() / 255.;
    double g = color.green() / 255.;
    double b = color.blue() / 255.;

    double f = -3.0 + (6.0 * parameter / 1000);
    double gamma = pow(2,f);
    r = pow(r, gamma);
    g = pow(g, gamma);
    b = pow(b, gamma);
    color.setRgb(r*255,g*255,b*255);
    return color.rgb();
}

