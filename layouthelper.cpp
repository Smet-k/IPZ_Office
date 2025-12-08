#include "layouthelper.h"
#include <QWidget>

void clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0))) {
        if (QWidget *w = item->widget())
            w->deleteLater();          // safe: no instant free
        if (QLayout *childLayout = item->layout())
            clearLayout(childLayout);  // recursive
        if (item->widget())
            item->widget()->deleteLater();
    }
}
