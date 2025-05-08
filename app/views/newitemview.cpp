#include "newitemview.h"
#include "../visitors/itemformvisitor.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QScrollArea>
#include <QDebug>

NewItemView::NewItemView(QWidget *parent)
    : QWidget(parent)
{
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *contentWidget = new QWidget;
    mainLayout = new QVBoxLayout(contentWidget);

    typeComboBox = new QComboBox(this);
    typeComboBox->addItem("book", "book");
    typeComboBox->addItem("movie", "movie");
    typeComboBox->addItem("article", "article");

    mainLayout->addWidget(new QLabel("Select Item Type:"));
    mainLayout->addWidget(typeComboBox);
    mainLayout->addStretch();

    connect(typeComboBox, &QComboBox::currentTextChanged,
            this, &NewItemView::onTypeChanged);

    setUpForm("book");

    contentWidget->setLayout(mainLayout);
    scrollArea->setWidget(contentWidget);

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->addWidget(scrollArea);
    setLayout(outerLayout);
}

void NewItemView::setUpForm(const QString &type)
{
    if (currentForm)
    {
        mainLayout->removeWidget(currentForm);
        delete currentForm;
        currentForm = nullptr;
    }

    ItemFormVisitor *visitor = new ItemFormVisitor(this);

    if (type == "book")
    {
        Book *book = new Book();
        visitor->visit(*book);
        delete book; // Clean up the temporary book
    }
    else if (type == "movie")
    {
        Movie *movie = new Movie();
        visitor->visit(*movie);
        delete movie; // Clean up the temporary movie
    }
    else if (type == "article")
    {
        Article *article = new Article();
        visitor->visit(*article);
        delete article; // Clean up the temporary article
    }

    QWidget *form = visitor->getResult();
    if (form)
    {
        mainLayout->addWidget(form);
        currentForm = form;

        connect(visitor, &ItemFormVisitor::createItemRequested,
                this, &NewItemView::createItemRequested); // Qt should automatically forward the item pointer, I hope
    }
    else
    {
        delete visitor;
    }
}

void NewItemView::onTypeChanged(const QString &type)
{
    setUpForm(type);
}
