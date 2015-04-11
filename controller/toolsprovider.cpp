#include "toolsprovider.h"
#include "model/grayscalefilter.h"
#include <QVariant>

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
    qDeleteAll(filters);
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
            newButton->setProperty("style", QVariant("pickFilterButton"));
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
            newButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            newButton->setText("nazwa");
            buttonGroup.addButton(newButton, i);
        }
        connect(&buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(changeCurrentFilter(int)));
    }
    return buttonGroup;
}

void ToolsProvider::changeCurrentFilter(int id)
{
    currentFilter = filters[id];
    emit currentFilterChanged(currentFilter);
    //TODO emit
}


