#include "indexview.h"
#include "../models/library.h"
#include "../visitors/itemcardvisitor.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QUuid>
#include <QDebug>
#include <QLineEdit>

IndexView::IndexView(QWidget *parent)
    : QWidget(parent), libraryModel(nullptr)
{
    QLineEdit *searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search...");
    searchBar->setFixedHeight(30);
    connect(searchBar, &QLineEdit::textChanged, this, &IndexView::onSearchTextChanged);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *contentWidget = new QWidget;
    mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setSpacing(12);

    contentWidget->setLayout(mainLayout);
    scrollArea->setWidget(contentWidget);

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setSpacing(0);
    outerLayout->addWidget(searchBar);
    outerLayout->addWidget(scrollArea);
    setLayout(outerLayout);
}

IndexView::~IndexView()
{
    // Clear all visitors
    qDeleteAll(visitors);
    visitors.clear();
}

void IndexView::populateFromLibrary(Library *library, QString &searchQuery)
{
    if (!library)
        return; // Guard against null library

    libraryModel = library;
    currentSearchQuery = searchQuery;

    // Clear existing cards and visitors
    QLayoutItem *item;
    while ((item = mainLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    qDeleteAll(visitors);
    visitors.clear();

    // Get search results
    std::vector<Item *> searchResults = libraryModel->searchItems(currentSearchQuery);

    // Generate a card for each search result
    for (Item *item : searchResults)
    {
        if (!item)
            continue; // Skip null items

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

void IndexView::onSearchTextChanged(const QString &query)
{
    if (libraryModel)
    {
        currentSearchQuery = query; // Update the current search query
        populateFromLibrary(libraryModel, currentSearchQuery);
    }
}