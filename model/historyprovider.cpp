#include "historyprovider.h"

HistoryProvider::HistoryProvider(QObject *parent) : QObject(parent), runningFilter(0)
{
    currentIterator = list.end();
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

QImage *HistoryProvider::getCurrentImage()
{
    return *currentIterator;
}

void HistoryProvider::doFilterAndAppend(Filter *filter)
{
    if (list.isEmpty()) {
        return;
    }
    if (runningFilter == 0) {
        QImage *newImage = new QImage((*currentIterator)->copy());
        if (newImage->format() == QImage::Format_Invalid) {
            delete newImage;
            emit errorOccured(tr("Brak dostępnej pamięci do wykonania operacji"));
            return;
        }
        filter->setImage(newImage);
        connect(filter, SIGNAL(ready()), this, SLOT(filterFinished()));
        runningFilter = filter;
        timer.start();
        filter->process();
    } else {
        emit errorOccured(tr("Poprzedni filtr nie został jeszcze nałożony"));
    }
}

void HistoryProvider::doBrushAndAppend(Brush *brush, QPainterPath path)
{
    if (currentIterator == list.end()) {
        return;
    }
    QImage *newImage = new QImage((*currentIterator)->copy());
    if (newImage->format() == QImage::Format_Invalid) {
        delete newImage;
        emit errorOccured(tr("Brak dostępnej pamięci do wykonania operacji"));
        return;
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
    int elapsed = timer.elapsed();
    timer.invalidate();
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
    emit operationFinished(elapsed);
    runningFilter = 0;
}

