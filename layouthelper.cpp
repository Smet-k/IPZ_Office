#include "layouthelper.h"

void clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {

        if (item->widget()) {
            delete item->widget();   // delete the widget
        }

        if (item->layout()) {
            clearLayout(item->layout()); // recursively delete nested layouts
        }

        delete item; // delete the QLayoutItem
    }
}
