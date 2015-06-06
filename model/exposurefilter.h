#ifndef EXPOSUREFILTER_H
#define EXPOSUREFILTER_H

#include "colorfilter.h"

class ExposureFilter : public ColorFilter
{
public:
    ExposureFilter();
    ~ExposureFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // EXPOSUREFILTER_H
