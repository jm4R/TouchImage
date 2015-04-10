#include "filter.h"

//static begin
QList<Filter::FilterProcessPointer> Filter::filterProcessPool;
int Filter::threadCount;
//static end

Filter::Filter(QObject *parent) :
    QObject(parent),
    threadRuns(0),
    image(0)
{
    if (filterProcessPool.empty()) {
        threadCount = QThread::idealThreadCount();
        if (threadCount < 1)
            threadCount = 1;
        for (int i=0; i<threadCount; i++) {
            FilterProcessPointer filterProcess(new FilterProcess(i, threadCount));
            filterProcessPool.append(filterProcess);
        }
    }
}

Filter::~Filter()
{

}
QImage *Filter::getImage() const
{
    return image;
}

void Filter::setImage(QImage *value)
{
    image = value;
}

void Filter::process()
{
    for (int i=0; i<threadCount; i++) {
        FilterProcessPointer filterProcess = filterProcessPool[i];
        filterProcess->setFilter(this);
        connect(this, &Filter::startProcesses, filterProcess.data(), &FilterProcess::run);
        connect(filterProcess.data(), &FilterProcess::ready, this, &Filter::handleProcessReady);
        filterProcess->startThread();
    }
    threadRuns = threadCount;
    emit startProcesses();
}

void Filter::handleProcessReady()
{
    threadRuns--;
    if (threadRuns == 0) {
        emit ready();
        for (int i=0; i<threadCount; i++) {
            FilterProcessPointer filterProcess = filterProcessPool[i];
            filterProcess->freeThread();
            disconnect(this, 0, filterProcess.data(), 0);
            disconnect(filterProcess.data(), 0, this, 0);
        }
    }
}

