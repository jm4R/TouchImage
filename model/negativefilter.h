#ifndef NEGATVEFILTER_H
#define NEGATVEFILTER_H

#include "colorfilter.h"

class NegativeFilter : public ColorFilter
{
public:
    NegativeFilter();
    ~NegativeFilter();
protected:
    uint processPixel(uint pixel);
};

#endif // NEGATVEFILTER_H
