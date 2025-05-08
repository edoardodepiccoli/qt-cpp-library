#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "showitemview.h"
#include "../visitors/itemshowvisitor.h"

ShowItemView::ShowItemView(QWidget *parent, Item *item) : QWidget(parent)
{
    qDebug() << "ShowItemView constructor";
    if (item)
    {
        this->item = std::unique_ptr<Item>(item); // Take ownership
    }

    ItemShowVisitor *visitor = new ItemShowVisitor(this);
    if (this->item)
    {
        this->item->accept(*visitor);
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    QWidget *result = visitor->getResult();

    connect(visitor, &ItemShowVisitor::deleteItemRequested, this, &ShowItemView::deleteItemRequested);
    connect(visitor, &ItemShowVisitor::editItemRequested, this, &ShowItemView::editItemRequested);

    layout->addWidget(result);

    this->setLayout(layout);
}

ShowItemView::~ShowItemView() = default;
