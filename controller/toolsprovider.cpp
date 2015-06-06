#include "toolsprovider.h"
#include "model/grayscalefilter.h"
#include "model/sepiafilter.h"
#include "model/negativefilter.h"
#include "model/saturatefilter.h"
#include "model/gammafilter.h"
#include "model/lightnessfilter.h"
#include "model/exposurefilter.h"
#include "model/huefilter.h"
#include "model/denoisefilter.h"
#include "model/gaussfilter.h"
#include <QVariant>

ToolsProvider::ToolsProvider(QObject *parent) : QObject(parent),
    filtersCount(0)
{
    QList<Filter *> *_filters = const_cast< QList<Filter *> *>(&filters);
    _filters->append(0);
    _filters->append(new GrayscaleFilter);
    _filters->append(new SepiaFilter);
    _filters->append(new NegativeFilter);
    _filters->append(new SaturateFilter);
    _filters->append(new GammaFilter);
    _filters->append(new LightnessFilter);
    _filters->append(new ExposureFilter);
    _filters->append(new HueFilter);
    _filters->append(new DenoiseFilter);
    _filters->append(new GaussFilter);

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
            if (filters[i]) {
                int tmp = filters[i]->getParameter();
                filters[i]->setParameter(filters[i]->getDefaultParameter());
                filters[i]->setImage(&filteredImage);
                filters[i]->process();
                filters[i]->wait();
                filters[i]->setParameter(tmp);
            }
            QPixmap icon;
            icon.convertFromImage(filteredImage);
            newButton->setIcon(icon);
            newButton->setIconSize(icon.size());
            newButton->setCheckable(true);
            newButton->setChecked( filters[i] == currentFilter );
            newButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            newButton->setText(filters[i] ? filters[i]->getName() : tr("Brak"));
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
}
Filter *ToolsProvider::getCurrentFilter() const
{
    return currentFilter;
}

Brush *ToolsProvider::getCurrentBrush() const
{
    //{MOCK
    static Brush brush;
    return &brush;
    //}MOCK
}

