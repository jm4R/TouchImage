#ifndef SEPIAFILTER_H
#define SEPIAFILTER_H
#include "colorfilter.h"


class SepiaFilter : public ColorFilter
{
public:
    SepiaFilter();
    ~SepiaFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // SEPIAFILTER_H
