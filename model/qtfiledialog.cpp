#include "qtfiledialog.h"
#include <QStandardPaths>
#include <QFileDialog>

QtFileDialog::QtFileDialog(QObject *parent) : FileDialogStrategy(parent)
{

}

QtFileDialog::~QtFileDialog()
{

}

bool QtFileDialog::provideExistingFileName()
{
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    const QString fileName =
        QFileDialog::getOpenFileName(0, "Wybierz plik graficzny", picturesLocations.isEmpty() ? QString() : picturesLocations.front(), "Obrazy (*.png *.xpm *.jpg *.jpeg *.bmp);; Wszystkie pliki (*)");
    emit existingFileNameReady(fileName);
    return true;
}
