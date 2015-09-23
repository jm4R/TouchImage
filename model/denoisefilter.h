#ifndef DENOISEFILTER_H
#define DENOISEFILTER_H
#include "splotfilter.h"

/**
 * @brief
 * Klasa służąca do nakładania na obraz filtra odszumiającego (medianowego).
 * @sa Filter SplotFilter
 */
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
