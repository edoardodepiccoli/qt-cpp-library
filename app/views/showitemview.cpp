#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "showitemview.h"
#include "../visitors/itemshowvisitor.h"

ShowItemView::ShowItemView(QWidget *parent, Item *item) : QWidget(parent), item(item)
{
    visitor = std::make_unique<ItemShowVisitor>(this);
    if (this->item)
    {
        this->item->accept(*visitor);
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    QWidget *result = visitor->getResult();

    connect(visitor.get(), &ItemShowVisitor::deleteItemRequested, this, &ShowItemView::deleteItemRequested);
    connect(visitor.get(), &ItemShowVisitor::editItemRequested, this, &ShowItemView::editItemRequested);

    layout->addWidget(result);

    this->setLayout(layout);
}
