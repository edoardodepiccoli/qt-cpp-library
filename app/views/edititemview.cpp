#include <QVBoxLayout>
#include <QLabel>

#include "edititemview.h"
#include "../models/item.h"

EditItemView::EditItemView(QWidget *parent, Item *item)
    : QWidget(parent), item(item)
{
    qDebug() << "EditItemView constructor";
    layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("This is EditItemView"));
    if (item)
    {
        layout->addWidget(new QLabel(item->getTitle()));
    }
    else
    {
        layout->addWidget(new QLabel("No item selected"));
    }
    layout->addStretch();

    setLayout(layout);
}
