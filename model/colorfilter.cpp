#include "colorfilter.h"

ColorFilter::ColorFilter(QObject *parent) : Filter(parent)
{

}

ColorFilter::~ColorFilter()
{

}

void ColorFilter::processLine(int lineNumber)
{
    QRgb *line = reinterpret_cast<QRgb*>(image->scanLine(lineNumber));
    int width = image->width();
    for (int i=0; i<width; i++) {
        line[i] = processPixel(line[i]);
    }
}

