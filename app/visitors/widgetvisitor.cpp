#include "widgetvisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QUuid>
#include <QDebug>

WidgetVisitor::WidgetVisitor(QObject *parent)
    : QObject(parent), widget(nullptr)
{
}

void WidgetVisitor::visit(Book &book)
{
    QWidget *card = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(card);

    layout->addWidget(new QLabel("📚 Book"));
    layout->addWidget(new QLabel("Title: " + book.getTitle()));
    layout->addWidget(new QLabel("Author: " + book.getAuthor()));
    layout->addWidget(new QLabel("Year: " + QString::number(book.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(book.getReview())));

    QPushButton *deleteButton = new QPushButton("Delete Book");
    layout->addWidget(deleteButton);

    itemId = book.getId();
    connect(deleteButton, &QPushButton::clicked, this, &WidgetVisitor::onDeleteButtonClicked);

    widget = card;
}

void WidgetVisitor::visit(Movie &movie)
{
    QWidget *card = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(card);

    layout->addWidget(new QLabel("🎬 Movie"));
    layout->addWidget(new QLabel("Title: " + movie.getTitle()));
    layout->addWidget(new QLabel("Director: " + movie.getDirector()));
    layout->addWidget(new QLabel("Year: " + QString::number(movie.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(movie.getReview())));

    QPushButton *deleteButton = new QPushButton("Delete Movie");
    layout->addWidget(deleteButton);

    itemId = movie.getId();
    connect(deleteButton, &QPushButton::clicked, this, &WidgetVisitor::onDeleteButtonClicked);

    widget = card;
}

void WidgetVisitor::visit(Article &article)
{
    QWidget *card = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(card);

    layout->addWidget(new QLabel("📝 Article"));
    layout->addWidget(new QLabel("Title: " + article.getTitle()));
    layout->addWidget(new QLabel("Link: " + article.getLink()));
    layout->addWidget(new QLabel("Author: " + article.getAuthor()));
    layout->addWidget(new QLabel("Year: " + QString::number(article.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(article.getReview())));

    QPushButton *deleteButton = new QPushButton("Delete Article");
    layout->addWidget(deleteButton);

    itemId = article.getId();
    connect(deleteButton, &QPushButton::clicked, this, &WidgetVisitor::onDeleteButtonClicked);

    widget = card;
}

// Implementation of the slot that then sends up the signal to the IndexView
void WidgetVisitor::onDeleteButtonClicked()
{
    qDebug() << "WidgetVisitor::onDeleteButtonClicked() called for item ID:" << itemId;
    emit deleteItemRequested(itemId);
}
