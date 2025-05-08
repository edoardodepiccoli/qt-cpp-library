#include "itemformvisitor.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

ItemFormVisitor::ItemFormVisitor(QObject *parent)
    : QObject(parent), form(nullptr), titleEdit(nullptr), descriptionEdit(nullptr),
      yearEdit(nullptr), reviewEdit(nullptr), commentEdit(nullptr), authorEdit(nullptr),
      directorEdit(nullptr), linkEdit(nullptr)
{
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

    QPushButton *createButton = new QPushButton("Create Book");
    layout->addWidget(createButton);

    connect(createButton, &QPushButton::clicked, this, &ItemFormVisitor::onCreateButtonClicked);

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

    QPushButton *createButton = new QPushButton("Create Movie");
    layout->addWidget(createButton);

    connect(createButton, &QPushButton::clicked, this, &ItemFormVisitor::onCreateButtonClicked);

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

    QPushButton *createButton = new QPushButton("Create Article");
    layout->addWidget(createButton);

    connect(createButton, &QPushButton::clicked, this, &ItemFormVisitor::onCreateButtonClicked);

    this->form = form;
    currentFormType = FormType::Article;
}

void ItemFormVisitor::onCreateButtonClicked()
{
    Item *item = nullptr;

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
        item = book;
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
        item = movie;
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
        item = article;
        break;
    }
    }

    if (item)
    {
        switch (currentFormType)
        {
        case FormType::Book:
            qDebug() << "Creating Book";
            break;
        case FormType::Movie:
            qDebug() << "Creating Movie";
            break;
        case FormType::Article:
            qDebug() << "Creating Article";
            break;
        }

        emit createItemRequested(item);
    }
}