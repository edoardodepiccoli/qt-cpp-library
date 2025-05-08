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
    qDebug() << "IndexView constructor";
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

IndexView::~IndexView()
{
    // Clear all visitors
    qDeleteAll(visitors);
    visitors.clear();
}

void IndexView::populateFromLibrary(Library *library)
{
    libraryModel = library;

    // Clear existing cards and visitors
    QLayoutItem *item;
    while ((item = mainLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    qDeleteAll(visitors);
    visitors.clear();

    // Generate a card for each item
    for (int i = 0; i < libraryModel->getItemCount(); ++i)
    {
        Item *item = libraryModel->getItem(i);
        if (item)
        {
            // Pass this (IndexView) as the parent to the visitor
            ItemCardVisitor *visitor = new ItemCardVisitor(this);
            visitors.append(visitor); // Track the visitor
            item->accept(*visitor);
            if (QWidget *w = visitor->getResult())
            {
                w->setParent(this); // Explicitly set parent
                w->setStyleSheet("background-color: gray;");
                mainLayout->addWidget(w);

                connect(visitor, &ItemCardVisitor::itemShowRequested,
                        this, &IndexView::itemShowRequested);
            }
            else
            {
                // If the visitor didn't create a widget, delete the visitor
                visitors.removeOne(visitor);
                delete visitor;
            }
        }
    }
}