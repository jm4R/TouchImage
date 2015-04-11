#include "toolsprovider.h"
#include "model/grayscalefilter.h"

ToolsProvider::ToolsProvider(QObject *parent) : QObject(parent),
    filtersCount(0)
{
    QList<Filter *> *_filters = const_cast< QList<Filter *> *>(&filters);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
    _filters->append(new GrayscaleFilter);
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

QButtonGroup& ToolsProvider::generateButtonGroup(const QImage &iconImage)
{
    if (buttonGroup.buttons().empty()) {
        for (int i=0; i<filtersCount; i++) {
            QToolButton *newButton = new QToolButton();
            QImage filteredImage = iconImage.copy();
            filters[i]->setImage(&filteredImage);
            filters[i]->process();
            filters[i]->wait();
            QPixmap icon;
            icon.convertFromImage(filteredImage);
            newButton->setIcon(icon);
            newButton->setIconSize(icon.size());
            newButton->setCheckable(true);
            newButton->setChecked( filters[i] == currentFilter );
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


