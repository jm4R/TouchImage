#ifndef SATURATEFILTER_H
#define SATURATEFILTER_H
#include "colorfilter.h"


class SaturateFilter : public ColorFilter
{
public:
    SaturateFilter();
    ~SaturateFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // SATURATEFILTER_H
