#ifndef GRAYSCALEFILTER_H
#define GRAYSCALEFILTER_H
#include "colorfilter.h"

class GrayscaleFilter : public ColorFilter
{
public:
    GrayscaleFilter();
    ~GrayscaleFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // GRAYSCALEFILTER_H
