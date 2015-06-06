#ifndef GAUSSFILTER_H
#define GAUSSFILTER_H

#include "splotfilter.h"

class GaussFilter : public SplotFilter
{
public:
    GaussFilter();
    ~GaussFilter();
protected:
    uint processMatrix(uint m[9]);
};

#endif // GAUSSFILTER_H
