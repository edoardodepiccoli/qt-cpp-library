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

ItemCardVisitor::~ItemCardVisitor()
{
    clearWidget();
}

void ItemCardVisitor::clearWidget()
{
    if (widget)
    {
        delete widget;
        widget = nullptr;
    }
}

void ItemCardVisitor::visit(Book &book)
{
    clearWidget(); // Clear any existing widget before creating a new one

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

    layout->addLayout(horizontalLayout);

    itemId = book.getId();
    connect(viewButton, &QPushButton::clicked, this, [this]()
            { emit itemShowRequested(itemId); });
    widget = card;
}

void ItemCardVisitor::visit(Movie &movie)
{
    clearWidget(); // Clear any existing widget before creating a new one

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

    layout->addLayout(horizontalLayout);

    itemId = movie.getId();
    connect(viewButton, &QPushButton::clicked, this, [this]()
            { emit itemShowRequested(itemId); });

    widget = card;
}

void ItemCardVisitor::visit(Article &article)
{
    clearWidget(); // Clear any existing widget before creating a new one

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

    layout->addLayout(horizontalLayout);

    itemId = article.getId();
    connect(viewButton, &QPushButton::clicked, this, [this]()
            { emit itemShowRequested(itemId); });

    widget = card;
}