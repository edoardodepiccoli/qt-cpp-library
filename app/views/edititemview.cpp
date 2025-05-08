#include <QVBoxLayout>
#include <QLabel>

#include "edititemview.h"
#include "../models/item.h"
#include "../visitors/itemformvisitor.h"

EditItemView::EditItemView(QWidget *parent, Item *item)
    : QWidget(parent), item(item)
{
    layout = new QVBoxLayout(this);

    // Create the form visitor in edit mode
    ItemFormVisitor *formVisitor = new ItemFormVisitor(this, item);

    // Visit the item to create the appropriate form
    item->accept(*formVisitor);

    // Add the form to the layout
    layout->addWidget(formVisitor->getResult());

    // Connect the edit signal
    connect(formVisitor, &ItemFormVisitor::updateItemRequested,
            this, [this](Item *updatedItem)
            { emit updateItemRequested(updatedItem); });

    layout->addStretch();

    setLayout(layout);
}
