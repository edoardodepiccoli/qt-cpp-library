#include "newitemview.h"
#include "../visitors/itemformvisitor.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QScrollArea>
#include <QDebug>

NewItemView::NewItemView(QWidget *parent)
    : QWidget(parent),
      mainLayout(nullptr),
      typeComboBox(nullptr),
      currentForm(nullptr),
      currentImagePath(QString()),
      currentFormVisitor(nullptr)
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

    // Delete the old visitor if it exists
    if (currentFormVisitor)
    {
        delete currentFormVisitor;
        currentFormVisitor = nullptr;
    }

    currentFormVisitor = new ItemFormVisitor(this);

    if (type == "book")
    {
        Book *book = new Book();
        currentFormVisitor->visit(*book);
        delete book; // Clean up the temporary book
    }
    else if (type == "movie")
    {
        Movie *movie = new Movie();
        currentFormVisitor->visit(*movie);
        delete movie; // Clean up the temporary movie
    }
    else if (type == "article")
    {
        Article *article = new Article();
        currentFormVisitor->visit(*article);
        delete article; // Clean up the temporary article
    }

    QWidget *form = currentFormVisitor->getResult();
    if (form)
    {
        // If we have a current image path, update the form's image path
        if (!currentImagePath.isEmpty())
        {
            if (auto *imagePathLabel = form->findChild<QLabel *>())
            {
                imagePathLabel->setText("Selected: " + currentImagePath);
            }
            currentFormVisitor->setCurrentImagePath(currentImagePath);
        }

        mainLayout->addWidget(form);
        currentForm = form;

        // Connect to the form's image selection signal
        connect(currentFormVisitor, &ItemFormVisitor::imagePathChanged,
                this, [this](const QString &path)
                { currentImagePath = path; });

        connect(currentFormVisitor, &ItemFormVisitor::createItemRequested,
                this, &NewItemView::createItemRequested);
    }
    else
    {
        delete currentFormVisitor;
        currentFormVisitor = nullptr;
    }
}

void NewItemView::onTypeChanged(const QString &type)
{
    setUpForm(type);
}
