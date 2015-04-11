#ifndef TOOLSPROVIDER_H
#define TOOLSPROVIDER_H

#include <QObject>
#include <QList>
#include <QButtonGroup>
#include <QToolButton>
#include "model/filter.h"
#include "model/grayscalefilter.h"

class ToolsProvider : public QObject
{
    Q_OBJECT
public:
    explicit ToolsProvider(QObject *parent = 0);
    ~ToolsProvider();

    const QList<Filter *> getFilters() const;
    QButtonGroup &generateButtonGroup(const QImage &iconImage);

signals:
    void currentFilterChanged(Filter *filter);
public slots:

private slots:
    void changeCurrentFilter(int id);
private:
    const QList<Filter *> filters;
    const int filtersCount;
    Filter *currentFilter;
    QButtonGroup buttonGroup;
};

#endif // TOOLSPROVIDER_H
