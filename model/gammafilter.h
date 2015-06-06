#ifndef GAMMAFILTER_H
#define GAMMAFILTER_H

#include "colorfilter.h"

class GammaFilter : public ColorFilter
{
public:
    GammaFilter();
    ~GammaFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // GAMMAFILTER_H
