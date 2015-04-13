#ifndef SPLOTFILTER_H
#define SPLOTFILTER_H
#include "filter.h"


class SplotFilter : public Filter
{
public:
    SplotFilter();
    ~SplotFilter();
protected:
    void processLine(int lineNumber);
    virtual uint processMatrix(uint m[9]) = 0;
};

#endif // SPLOTFILTER_H
