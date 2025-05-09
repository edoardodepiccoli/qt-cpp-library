#include "itemformvisitor.h"
#include <QFileDialog>
#include <QMessageBox>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>

ItemFormVisitor::ItemFormVisitor(QObject *parent, Item *item)
    : QObject(parent), form(nullptr), titleEdit(nullptr), descriptionEdit(nullptr),
      yearEdit(nullptr), reviewEdit(nullptr), commentEdit(nullptr), authorEdit(nullptr),
      directorEdit(nullptr), linkEdit(nullptr), item(item)
{
    isEditing = item != nullptr;
}

void ItemFormVisitor::addImageUploadSection(QVBoxLayout *layout)
{
    QLabel *imageLabel = new QLabel("Image:");
    imageButton = new QPushButton("Select Image");
    imagePathLabel = new QLabel("No image selected");
    imagePathLabel->setWordWrap(true);

    layout->addWidget(imageLabel);
    layout->addWidget(imageButton);
    layout->addWidget(imagePathLabel);

    connect(imageButton, &QPushButton::clicked, this, &ItemFormVisitor::onImageButtonClicked);
}

void ItemFormVisitor::onImageButtonClicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select Image", "",
                                                    "Image Files (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!filePath.isEmpty())
    {
        currentImagePath = filePath;
        imagePathLabel->setText("Selected: " + filePath);
        emit imagePathChanged(filePath);
    }
}

void ItemFormVisitor::visit(Book &book)
{
    QWidget *form = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(form);

    QLabel *titleLabel = new QLabel("Title:");
    titleEdit = new QLineEdit;
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);

    QLabel *descriptionLabel = new QLabel("Description:");
    descriptionEdit = new QTextEdit;
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    QLabel *yearLabel = new QLabel("Year:");
    yearEdit = new QLineEdit;
    layout->addWidget(yearLabel);
    layout->addWidget(yearEdit);

    QLabel *reviewLabel = new QLabel("Review:");
    reviewEdit = new QLineEdit;
    layout->addWidget(reviewLabel);
    layout->addWidget(reviewEdit);

    QLabel *commentLabel = new QLabel("Comment:");
    commentEdit = new QTextEdit;
    layout->addWidget(commentLabel);
    layout->addWidget(commentEdit);

    QLabel *authorLabel = new QLabel("Author:");
    authorEdit = new QLineEdit;
    layout->addWidget(authorLabel);
    layout->addWidget(authorEdit);

    addImageUploadSection(layout);

    if (isEditing)
    {
        QPushButton *editButton = new QPushButton("Update Book");
        layout->addWidget(editButton);
        connect(editButton, &QPushButton::clicked, this, &ItemFormVisitor::onUpdateButtonClicked);
        populateFormFields(&book);
    }
    else
    {
        QPushButton *createButton = new QPushButton("Create Book");
        layout->addWidget(createButton);
        connect(createButton, &QPushButton::clicked, this, &ItemFormVisitor::onCreateButtonClicked);
    }

    this->form = form;
    currentFormType = FormType::Book;
}

void ItemFormVisitor::visit(Movie &movie)
{
    QWidget *form = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(form);

    QLabel *titleLabel = new QLabel("Title:");
    titleEdit = new QLineEdit;
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);

    QLabel *descriptionLabel = new QLabel("Description:");
    descriptionEdit = new QTextEdit;
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    QLabel *yearLabel = new QLabel("Year:");
    yearEdit = new QLineEdit;
    layout->addWidget(yearLabel);
    layout->addWidget(yearEdit);

    QLabel *reviewLabel = new QLabel("Review:");
    reviewEdit = new QLineEdit;
    layout->addWidget(reviewLabel);
    layout->addWidget(reviewEdit);

    QLabel *commentLabel = new QLabel("Comment:");
    commentEdit = new QTextEdit;
    layout->addWidget(commentLabel);
    layout->addWidget(commentEdit);

    QLabel *directorLabel = new QLabel("Director:");
    directorEdit = new QLineEdit;
    layout->addWidget(directorLabel);
    layout->addWidget(directorEdit);

    addImageUploadSection(layout);

    if (isEditing)
    {
        QPushButton *editButton = new QPushButton("Update Movie");
        layout->addWidget(editButton);
        connect(editButton, &QPushButton::clicked, this, &ItemFormVisitor::onUpdateButtonClicked);
        populateFormFields(&movie);
    }
    else
    {
        QPushButton *createButton = new QPushButton("Create Movie");
        layout->addWidget(createButton);
        connect(createButton, &QPushButton::clicked, this, &ItemFormVisitor::onCreateButtonClicked);
    }

    this->form = form;
    currentFormType = FormType::Movie;
}

void ItemFormVisitor::visit(Article &article)
{
    QWidget *form = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(form);

    QLabel *titleLabel = new QLabel("Title:");
    titleEdit = new QLineEdit;
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);

    QLabel *descriptionLabel = new QLabel("Description:");
    descriptionEdit = new QTextEdit;
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    QLabel *yearLabel = new QLabel("Year:");
    yearEdit = new QLineEdit;
    layout->addWidget(yearLabel);
    layout->addWidget(yearEdit);

    QLabel *reviewLabel = new QLabel("Review:");
    reviewEdit = new QLineEdit;
    layout->addWidget(reviewLabel);
    layout->addWidget(reviewEdit);

    QLabel *commentLabel = new QLabel("Comment:");
    commentEdit = new QTextEdit;
    layout->addWidget(commentLabel);
    layout->addWidget(commentEdit);

    QLabel *linkLabel = new QLabel("Link:");
    linkEdit = new QLineEdit;
    layout->addWidget(linkLabel);
    layout->addWidget(linkEdit);

    QLabel *authorLabel = new QLabel("Author:");
    authorEdit = new QLineEdit;
    layout->addWidget(authorLabel);
    layout->addWidget(authorEdit);

    addImageUploadSection(layout);

    if (isEditing)
    {
        QPushButton *editButton = new QPushButton("Update Article");
        layout->addWidget(editButton);
        connect(editButton, &QPushButton::clicked, this, &ItemFormVisitor::onUpdateButtonClicked);
        populateFormFields(&article);
    }
    else
    {
        QPushButton *createButton = new QPushButton("Create Article");
        layout->addWidget(createButton);
        connect(createButton, &QPushButton::clicked, this, &ItemFormVisitor::onCreateButtonClicked);
    }

    this->form = form;
    currentFormType = FormType::Article;
}

void ItemFormVisitor::populateFormFields(Item *item)
{
    if (!item)
        return;

    titleEdit->setText(item->getTitle());
    descriptionEdit->setText(item->getDescription());
    yearEdit->setText(QString::number(item->getYear()));
    reviewEdit->setText(QString::number(item->getReview()));
    commentEdit->setText(item->getComment());

    // Set current image path if it exists
    QString imagePath = item->getImagePath();
    if (!imagePath.isEmpty())
    {
        currentImagePath = imagePath;
        imagePathLabel->setText("Current: " + imagePath);
    }

    if (auto book = dynamic_cast<Book *>(item))
    {
        authorEdit->setText(book->getAuthor());
    }
    else if (auto movie = dynamic_cast<Movie *>(item))
    {
        directorEdit->setText(movie->getDirector());
    }
    else if (auto article = dynamic_cast<Article *>(item))
    {
        authorEdit->setText(article->getAuthor());
        linkEdit->setText(article->getLink());
    }
}

Item *ItemFormVisitor::createItemFromForm() const
{
    Item *newItem = nullptr;

    switch (currentFormType)
    {
    case FormType::Book:
    {
        Book *book = new Book();
        book->setTitle(titleEdit->text());
        book->setDescription(descriptionEdit->toPlainText());
        book->setYear(yearEdit->text().toInt());
        book->setReview(reviewEdit->text().toInt());
        book->setComment(commentEdit->toPlainText());
        book->setAuthor(authorEdit->text());
        newItem = book;
        break;
    }
    case FormType::Movie:
    {
        Movie *movie = new Movie();
        movie->setTitle(titleEdit->text());
        movie->setDescription(descriptionEdit->toPlainText());
        movie->setYear(yearEdit->text().toInt());
        movie->setReview(reviewEdit->text().toInt());
        movie->setComment(commentEdit->toPlainText());
        movie->setDirector(directorEdit->text());
        newItem = movie;
        break;
    }
    case FormType::Article:
    {
        Article *article = new Article();
        article->setTitle(titleEdit->text());
        article->setDescription(descriptionEdit->toPlainText());
        article->setYear(yearEdit->text().toInt());
        article->setReview(reviewEdit->text().toInt());
        article->setComment(commentEdit->toPlainText());
        article->setLink(linkEdit->text());
        article->setAuthor(authorEdit->text());
        newItem = article;
        break;
    }
    }

    // Set the image path on the new item if it exists
    if (newItem && !currentImagePath.isEmpty())
    {
        newItem->setImagePath(currentImagePath);
    }

    return newItem;
}

void ItemFormVisitor::onCreateButtonClicked()
{
    if (Item *newItem = createItemFromForm())
    {
        if (!currentImagePath.isEmpty())
        {
            // The image will be set after the item is created and has an ID
            emit createItemRequested(newItem);
            // The MainWindow will handle setting the image after the item is created
        }
        else
        {
            emit createItemRequested(newItem);
        }
    }
}

void ItemFormVisitor::onUpdateButtonClicked()
{
    if (Item *newItem = createItemFromForm())
    {
        newItem->setId(item->getId()); // Preserve the original ID

        // If we have a current image path, set it on the new item
        if (!currentImagePath.isEmpty())
        {
            newItem->setImagePath(currentImagePath);
        }
        else
        {
            // If no new image was selected, preserve the old image path
            newItem->setImagePath(item->getImagePath());
        }

        emit updateItemRequested(newItem);
    }
}