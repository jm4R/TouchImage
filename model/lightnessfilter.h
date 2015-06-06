#ifndef LIGHTNESSFILTER_H
#define LIGHTNESSFILTER_H

#include "colorfilter.h"

class LightnessFilter : public ColorFilter
{
public:
    LightnessFilter();
    ~LightnessFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // LIGHTNESSFILTER_H
