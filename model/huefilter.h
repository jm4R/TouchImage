#ifndef HUEFILTER_H
#define HUEFILTER_H

#include "colorfilter.h"

class HueFilter : public ColorFilter
{
public:
    HueFilter();
    ~HueFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // HUEFILTER_H
