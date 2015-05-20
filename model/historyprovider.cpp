#include "historyprovider.h"

HistoryProvider::HistoryProvider(QObject *parent) : QObject(parent), runningFilter(0)
{

}

HistoryProvider::~HistoryProvider()
{
    qDeleteAll(list);
}

void HistoryProvider::resetToImage(QImage *newImage)
{
    qDeleteAll(list);
    list.clear();
    list.append(newImage);
    currentIterator = list.begin();
    emit currentImageChanged(newImage);
    emit undoStatusChanged(false);
    emit redoStatusChanged(false);
}

void HistoryProvider::doFilterAndAppend(Filter *filter)
{
    if (runningFilter == 0) {
        QImage *newImage = new QImage((*currentIterator)->copy());
        if (newImage->format() == QImage::Format_Invalid) {
            delete newImage;
            return; //TODO: - nie ma pamieci
        }
        filter->setImage(newImage);
        connect(filter, SIGNAL(ready()), this, SLOT(filterFinished()));
        runningFilter = filter;
        filter->process();
    } else {
        //TODO: info - 2 filters at time not allowed
    }
}

void HistoryProvider::doBrushAndAppend(Brush *brush, QPainterPath path)
{
    QImage *newImage = new QImage((*currentIterator)->copy());
    if (newImage->format() == QImage::Format_Invalid) {
        delete newImage;
        return; //TODO: - nie ma pamieci
    }
    brush->setImage(newImage);
    brush->process(path);

    Iterator itDelete = currentIterator+1;
    while (itDelete != list.end()) {
        delete *itDelete;
        itDelete = list.erase(itDelete);
    }
    list.append(newImage);
    currentIterator = list.end() - 1;
    emit currentImageChanged(*currentIterator);
    emit undoStatusChanged(true);
    emit redoStatusChanged(false);
}

void HistoryProvider::undo()
{
    currentIterator--;
    emit currentImageChanged(*currentIterator);
    emit undoStatusChanged( currentIterator != list.begin() );
    emit redoStatusChanged(true);
}

void HistoryProvider::redo()
{
    currentIterator++;
    emit currentImageChanged(*currentIterator);
    emit undoStatusChanged(true);
    emit redoStatusChanged( currentIterator != list.end()-1 );
}

void HistoryProvider::filterFinished()
{
    disconnect(runningFilter, SIGNAL(ready()), this, SLOT(filterFinished()));
    Iterator itDelete = currentIterator+1;
    while (itDelete != list.end()) {
        delete *itDelete;
        itDelete = list.erase(itDelete);
    }
    list.append(runningFilter->getImage());
    currentIterator = list.end() - 1;
    emit currentImageChanged(*currentIterator);
    emit undoStatusChanged(true);
    emit redoStatusChanged(false);
    runningFilter = 0;
}

