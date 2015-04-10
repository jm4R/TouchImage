#include "toolsprovider.h"
#include "model/grayscalefilter.h"

ToolsProvider::ToolsProvider(QObject *parent) : QObject(parent),
    filtersCount(0)
{
    QList<Filter *> *_filters = const_cast< QList<Filter *> *>(&filters);
    _filters->append(new GrayscaleFilter);

    currentFilter = filters[0];
    *(const_cast<int *> (&filtersCount)) = filters.count();
}

ToolsProvider::~ToolsProvider()
{

}

const QList<Filter *> ToolsProvider::getFilters() const
{
    return filters;
}

QButtonGroup& ToolsProvider::generateButtonGroup()
{
    if (buttonGroup.buttons().empty()) {
        for (int i=0; i<filtersCount; i++) {
            QToolButton *newButton = new QToolButton();
            buttonGroup.addButton(newButton, i);
        }
        connect(&buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(changeCurrentFilter(int)));
    }
    return buttonGroup;
}

void ToolsProvider::changeCurrentFilter(int id)
{
    currentFilter = filters[id];
    //TODO emit
}


