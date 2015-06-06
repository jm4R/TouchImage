#include "denoisefilter.h"

DenoiseFilter::DenoiseFilter()
{
    name = tr("Odszumianie");
}

DenoiseFilter::~DenoiseFilter()
{

}

uint DenoiseFilter::processMatrix(uint m[9])
{
    std::qsort(m, 9, sizeof(uint), compareB);
    return m[4];
}



int compareB(const void *a, const void *b)
{
    uint pA = *(static_cast<const uint*>(a));
    uint pB = *(static_cast<const uint*>(b));
    return qGray(pA) - qGray(pB);
}
