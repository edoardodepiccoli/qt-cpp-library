#include "indexview.h"
#include "../models/library.h"
#include "../visitors/itemcardvisitor.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QUuid>
#include <QDebug>

IndexView::IndexView(QWidget *parent)
    : QWidget(parent), libraryModel(nullptr)
{
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *contentWidget = new QWidget;
    mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setSpacing(12);

    contentWidget->setLayout(mainLayout);
    scrollArea->setWidget(contentWidget);

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->addWidget(scrollArea);
    setLayout(outerLayout);
}

void IndexView::populateFromLibrary(Library *library)
{
    libraryModel = library;

    // Clear existing cards
    QLayoutItem *item;
    while ((item = mainLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }

    // Generate a card for each item
    for (int i = 0; i < libraryModel->getItemCount(); ++i)
    {
        Item *item = libraryModel->getItem(i);
        if (item)
        {
            // Pass this (IndexView) as the parent to the visitor
            // This helps with Qt automatic memory management (really cool and useful stuff)
            ItemCardVisitor *visitor = new ItemCardVisitor(this);
            item->accept(*visitor);
            if (QWidget *w = visitor->getResult())
            {
                w->setStyleSheet("background-color: gray;");
                mainLayout->addWidget(w);

                connect(visitor, &ItemCardVisitor::viewItemRequested,
                        this, &IndexView::viewItemRequested);
            }
            else
            {
                // If the visitor didn't create a widget, delete the visitor
                delete visitor;
            }
        }
    }
}