#ifndef DENOISEFILTER_H
#define DENOISEFILTER_H
#include "splotfilter.h"

class DenoiseFilter : public SplotFilter
{
public:
    DenoiseFilter();
    ~DenoiseFilter();
protected:
    uint processMatrix(uint m[9]);
};

int compareB(const void *a, const void *b);
#endif // DENOISEFILTER_H
