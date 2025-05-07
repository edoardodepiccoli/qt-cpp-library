#include "itemformvisitor.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

ItemFormVisitor::ItemFormVisitor(QObject *parent)
    : QObject(parent), form(nullptr)
{
}

void ItemFormVisitor::visit(Book &book)
{
    QWidget *form = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(form);

    QLabel *titleLabel = new QLabel("Title:");
    QLineEdit *titleEdit = new QLineEdit;
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);

    QLabel *descriptionLabel = new QLabel("Description:");
    QTextEdit *descriptionEdit = new QTextEdit;
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    QLabel *yearLabel = new QLabel("Year:");
    QLineEdit *yearEdit = new QLineEdit;
    layout->addWidget(yearLabel);
    layout->addWidget(yearEdit);

    QLabel *reviewLabel = new QLabel("Review:");
    QLineEdit *reviewEdit = new QLineEdit;
    layout->addWidget(reviewLabel);
    layout->addWidget(reviewEdit);

    QLabel *commentLabel = new QLabel("Comment:");
    QTextEdit *commentEdit = new QTextEdit;
    layout->addWidget(commentLabel);
    layout->addWidget(commentEdit);

    QLabel *authorLabel = new QLabel("Author:");
    QLineEdit *authorEdit = new QLineEdit;
    layout->addWidget(authorLabel);
    layout->addWidget(authorEdit);

    QPushButton *createButton = new QPushButton("Create Book");
    layout->addWidget(createButton);

    this->form = form;
}

void ItemFormVisitor::visit(Movie &movie)
{
    QWidget *form = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(form);

    QLabel *titleLabel = new QLabel("Title:");
    QLineEdit *titleEdit = new QLineEdit;
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);

    QLabel *descriptionLabel = new QLabel("Description:");
    QTextEdit *descriptionEdit = new QTextEdit;
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    QLabel *yearLabel = new QLabel("Year:");
    QLineEdit *yearEdit = new QLineEdit;
    layout->addWidget(yearLabel);
    layout->addWidget(yearEdit);

    QLabel *reviewLabel = new QLabel("Review:");
    QLineEdit *reviewEdit = new QLineEdit;
    layout->addWidget(reviewLabel);
    layout->addWidget(reviewEdit);

    QLabel *commentLabel = new QLabel("Comment:");
    QTextEdit *commentEdit = new QTextEdit;
    layout->addWidget(commentLabel);
    layout->addWidget(commentEdit);

    QLabel *directorLabel = new QLabel("Director:");
    QLineEdit *directorEdit = new QLineEdit;
    layout->addWidget(directorLabel);
    layout->addWidget(directorEdit);

    QPushButton *createButton = new QPushButton("Create Movie");
    layout->addWidget(createButton);

    this->form = form;
}

void ItemFormVisitor::visit(Article &article)
{
    QWidget *form = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(form);

    QLabel *titleLabel = new QLabel("Title:");
    QLineEdit *titleEdit = new QLineEdit;
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);

    QLabel *descriptionLabel = new QLabel("Description:");
    QTextEdit *descriptionEdit = new QTextEdit;
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    QLabel *yearLabel = new QLabel("Year:");
    QLineEdit *yearEdit = new QLineEdit;
    layout->addWidget(yearLabel);
    layout->addWidget(yearEdit);

    QLabel *reviewLabel = new QLabel("Review:");
    QLineEdit *reviewEdit = new QLineEdit;
    layout->addWidget(reviewLabel);
    layout->addWidget(reviewEdit);

    QLabel *commentLabel = new QLabel("Comment:");
    QTextEdit *commentEdit = new QTextEdit;
    layout->addWidget(commentLabel);
    layout->addWidget(commentEdit);

    QLabel *linkLabel = new QLabel("Link:");
    QLineEdit *linkEdit = new QLineEdit;
    layout->addWidget(linkLabel);
    layout->addWidget(linkEdit);

    QLabel *authorLabel = new QLabel("Author:");
    QLineEdit *authorEdit = new QLineEdit;
    layout->addWidget(authorLabel);
    layout->addWidget(authorEdit);

    QPushButton *createButton = new QPushButton("Create Article");
    layout->addWidget(createButton);

    this->form = form;
}