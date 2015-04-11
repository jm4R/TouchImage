#include "filterprocess.h"
#include <QDebug>

FilterProcess::FilterProcess(int threadNumber, int threadCount)
{
    this->threadNumber = threadNumber;
    this->threadCount = threadCount;
    this->moveToThread(&thread);
}

FilterProcess::~FilterProcess()
{

}
Filter *FilterProcess::getFilter() const
{
    return filter;
}

void FilterProcess::setFilter(Filter *value)
{
    filter = value;
}

void FilterProcess::startThread()
{
    thread.start();
}

void FilterProcess::run()
{
    int imageHeight = filter->getImage()->height();
    int start = threadNumber * imageHeight / threadCount;
    int stop = (threadNumber+1) * imageHeight / threadCount;

    for (int j=start; j<stop; j++) {
        filter->processLine(j);
    }
    emit ready();
}

void FilterProcess::freeThread()
{
    thread.quit();
}

void FilterProcess::waitForThread()
{
    thread.wait();
}
