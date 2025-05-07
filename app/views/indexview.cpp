#include "indexview.h"
#include "../models/library.h"
#include "../visitors/widgetvisitor.h"

#include <QVBoxLayout>
#include <QScrollArea>

IndexView::IndexView(QWidget *parent)
    : QWidget(parent)
{
    // Scroll area to wrap content
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // Content widget that will hold all item widgets
    QWidget *contentWidget = new QWidget;
    mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setAlignment(Qt::AlignTop); // Stack items vertically
    mainLayout->setSpacing(12);

    contentWidget->setLayout(mainLayout);
    scrollArea->setWidget(contentWidget);

    // Final layout of IndexView
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->addWidget(scrollArea);
    setLayout(outerLayout);
}

void IndexView::populateFromLibrary(Library *library)
{
    // Clear existing cards
    QLayoutItem *item;
    while ((item = mainLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    // Generate a card for each item
    for (int i = 0; i < library->getItemCount(); ++i)
    {
        Item *item = library->getItem(i);
        WidgetVisitor visitor;
        item->accept(visitor);
        if (QWidget *w = visitor.getResult())
        {
            w->setStyleSheet("background-color: gray;");
            mainLayout->addWidget(w);
        }
    }
}
