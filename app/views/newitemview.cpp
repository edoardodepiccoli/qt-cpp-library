#include "newitemview.h"
#include "../visitors/itemformvisitor.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QScrollArea>
NewItemView::NewItemView(QWidget *parent)
    : QWidget(parent)
{
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *contentWidget = new QWidget;
    mainLayout = new QVBoxLayout(contentWidget);

    // Add type selection combo box
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
    qDebug() << "Setting up form";

    if (currentForm)
    {
        mainLayout->removeWidget(currentForm);
        qDebug() << "Removing previous form";
        delete currentForm;
        currentForm = nullptr;
    }

    ItemFormVisitor *visitor = new ItemFormVisitor(this);

    if (type == "book")
    {
        Book *book = new Book();
        visitor->visit(*book);
    }
    else if (type == "movie")
    {
        Movie *movie = new Movie();
        visitor->visit(*movie);
    }
    else if (type == "article")
    {
        Article *article = new Article();
        visitor->visit(*article);
    }

    QWidget *form = visitor->getResult();
    mainLayout->addWidget(form);
    currentForm = form;
}

void NewItemView::onTypeChanged(const QString &type)
{
    qDebug() << "Selected item type:" << type;
    setUpForm(type);
}