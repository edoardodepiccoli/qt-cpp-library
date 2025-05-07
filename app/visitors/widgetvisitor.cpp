#include "widgetvisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>

void WidgetVisitor::visit(Book &book)
{
    QWidget *card = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(card);

    layout->addWidget(new QLabel("📚 Book"));
    layout->addWidget(new QLabel("Title: " + book.getTitle()));
    layout->addWidget(new QLabel("Author: " + book.getAuthor()));
    layout->addWidget(new QLabel("Year: " + QString::number(book.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(book.getReview())));
    layout->addWidget(new QPushButton("View Book"));

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
    layout->addWidget(new QPushButton("View Movie"));

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
    layout->addWidget(new QPushButton("View Article"));

    widget = card;
}
