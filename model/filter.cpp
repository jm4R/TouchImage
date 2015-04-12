#include "filter.h"
#include <QDebug>

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
    processMutex.lock();
    for (int i=0; i<threadCount; i++) {
        FilterProcessPointer filterProcess = filterProcessPool[i];
        filterProcess->setFilter(this);
        connect(this, &Filter::startProcesses, filterProcess.data(), &FilterProcess::run);
        connect(filterProcess.data(), &FilterProcess::ready, this, &Filter::handleProcessReady, Qt::DirectConnection);
        filterProcess->startThread();
    }
    threadRuns = threadCount;
    emit startProcesses();
}

void Filter::wait()
{
    for (int i=0; i<threadCount; i++) {
        FilterProcessPointer filterProcess = filterProcessPool[i];
        filterProcess->waitForThread();
    }
}

void Filter::handleProcessReady()
{
    handleMutex.lock();
    threadRuns--;
    if (threadRuns == 0) {
        emit ready();
        for (int i=0; i<threadCount; i++) {
            FilterProcessPointer filterProcess = filterProcessPool[i];
            filterProcess->freeThread();
            disconnect(this, 0, filterProcess.data(), 0);
            disconnect(filterProcess.data(), 0, this, 0);
        }
        processMutex.unlock();
    }
    handleMutex.unlock();
}
int Filter::getDefaultParameter() const
{
    return defaultParameter;
}

int Filter::getParameter() const
{
    return parameter;
}

void Filter::setParameter(int value)
{
    parameter = value;
}

QString Filter::getName() const
{
    return name;
}


