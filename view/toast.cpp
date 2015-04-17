#include "toast.h"

Toast::Toast(QWidget *parent) : QObject(parent), parentWidget(parent)
{
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SLOT(hideToast()));
    toastLabel.setAlignment(Qt::AlignCenter);
    toastLabel.setObjectName("toastLabel");
}

Toast::~Toast()
{

}

void Toast::showToast(QString text, int ms)
{
    toastLabel.setParent(parentWidget);
    toastLabel.setText(text);
    int w = toastLabel.fontMetrics().width(text) * 1.2f;
    int h = toastLabel.fontMetrics().height() * 2;
    toastLabel.setGeometry(
                ( parentWidget->width() - w ) / 2,
                parentWidget->height() - h * 2,
                w,
                h
    );
    toastLabel.show();
    timer.start(ms);
}

void Toast::hideToast()
{
    toastLabel.setParent(0);
    toastLabel.hide();
}

