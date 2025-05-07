#include "itemcardvisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QUuid>
#include <QDebug>

ItemCardVisitor::ItemCardVisitor(QObject *parent)
    : QObject(parent), widget(nullptr)
{
}

void ItemCardVisitor::visit(Book &book)
{
    QWidget *card = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(card);

    layout->addWidget(new QLabel("📚 Book"));
    layout->addWidget(new QLabel("Title: " + book.getTitle()));
    layout->addWidget(new QLabel("Author: " + book.getAuthor()));
    layout->addWidget(new QLabel("Year: " + QString::number(book.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(book.getReview())));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *viewButton = new QPushButton("View Book");
    horizontalLayout->addWidget(viewButton);

    QPushButton *deleteButton = new QPushButton("Delete Book");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = book.getId();
    connect(deleteButton, &QPushButton::clicked, this, &ItemCardVisitor::onDeleteButtonClicked);
    connect(viewButton, &QPushButton::clicked, this, &ItemCardVisitor::onViewButtonClicked);
    widget = card;
}

void ItemCardVisitor::onViewButtonClicked()
{
    qDebug() << "ItemCardVisitor::onViewButtonClicked() called for item ID:" << itemId;
    emit viewItemRequested(itemId);
}

void ItemCardVisitor::visit(Movie &movie)
{
    QWidget *card = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(card);

    layout->addWidget(new QLabel("🎬 Movie"));
    layout->addWidget(new QLabel("Title: " + movie.getTitle()));
    layout->addWidget(new QLabel("Director: " + movie.getDirector()));
    layout->addWidget(new QLabel("Year: " + QString::number(movie.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(movie.getReview())));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *viewButton = new QPushButton("View Movie");
    horizontalLayout->addWidget(viewButton);

    QPushButton *deleteButton = new QPushButton("Delete Movie");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = movie.getId();
    connect(deleteButton, &QPushButton::clicked, this, &ItemCardVisitor::onDeleteButtonClicked);
    connect(viewButton, &QPushButton::clicked, this, &ItemCardVisitor::onViewButtonClicked);

    widget = card;
}

void ItemCardVisitor::visit(Article &article)
{
    QWidget *card = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(card);

    layout->addWidget(new QLabel("📝 Article"));
    layout->addWidget(new QLabel("Title: " + article.getTitle()));
    layout->addWidget(new QLabel("Link: " + article.getLink()));
    layout->addWidget(new QLabel("Author: " + article.getAuthor()));
    layout->addWidget(new QLabel("Year: " + QString::number(article.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(article.getReview())));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *viewButton = new QPushButton("View Article");
    horizontalLayout->addWidget(viewButton);

    QPushButton *deleteButton = new QPushButton("Delete Article");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = article.getId();
    connect(deleteButton, &QPushButton::clicked, this, &ItemCardVisitor::onDeleteButtonClicked);
    connect(viewButton, &QPushButton::clicked, this, &ItemCardVisitor::onViewButtonClicked);

    widget = card;
}

// Implementation of the slot that then sends up the signal to the IndexView
void ItemCardVisitor::onDeleteButtonClicked()
{
    qDebug() << "ItemCardVisitor::onDeleteButtonClicked() called for item ID:" << itemId;
    emit deleteItemRequested(itemId);
}
