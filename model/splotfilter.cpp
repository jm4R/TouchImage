#include "splotfilter.h"

SplotFilter::SplotFilter()
{

}

SplotFilter::~SplotFilter()
{

}

void SplotFilter::processLine(int lineNumber)
{
    if (lineNumber == 0 || lineNumber+1 == image->height()) {
        return;
    }
    QRgb *lineA = reinterpret_cast<QRgb*>(image->scanLine(lineNumber-1));
    QRgb *lineB = reinterpret_cast<QRgb*>(image->scanLine(lineNumber));
    QRgb *lineC = reinterpret_cast<QRgb*>(image->scanLine(lineNumber+1));
    int width = image->width();
    for (int i=1; i<width-1; i++) {
        uint m[9] = {lineA[i-1], lineA[i], lineA[i+1],
                     lineB[i-1], lineB[i], lineB[i+1],
                     lineC[i-1], lineC[i], lineC[i+1]
                    };
        lineB[i] = processMatrix(m);
    }
}

