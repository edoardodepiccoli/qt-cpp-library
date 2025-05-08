#include "itemshowvisitor.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QUuid>
#include <QDebug>

ItemShowVisitor::ItemShowVisitor(QObject *parent)
    : QObject(parent), widget(nullptr)
{
}

void ItemShowVisitor::visit(Book &book)
{
    QWidget *result = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(result);

    layout->addWidget(new QLabel("📚 Book"));
    layout->addWidget(new QLabel("Title: " + book.getTitle()));
    layout->addWidget(new QLabel("Author: " + book.getAuthor()));
    layout->addWidget(new QLabel("Year: " + QString::number(book.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(book.getReview())));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *editButton = new QPushButton("Edit Book");
    horizontalLayout->addWidget(editButton);

    QPushButton *deleteButton = new QPushButton("Delete Book");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = book.getId();
    connect(deleteButton, &QPushButton::clicked, this, [this]()
            { qDebug() << "deleteItemRequested in ItemShowVisitor" << itemId;
                emit deleteItemRequested(itemId); });
    connect(editButton, &QPushButton::clicked, this, [this]()
            { qDebug() << "editItemRequested in ItemShowVisitor" << itemId;
                emit editItemRequested(itemId); });

    widget = result;
}

void ItemShowVisitor::visit(Movie &movie)
{
    QWidget *result = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(result);

    layout->addWidget(new QLabel("🎬 Movie"));
    layout->addWidget(new QLabel("Title: " + movie.getTitle()));
    layout->addWidget(new QLabel("Director: " + movie.getDirector()));
    layout->addWidget(new QLabel("Year: " + QString::number(movie.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(movie.getReview())));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *editButton = new QPushButton("Edit Movie");
    horizontalLayout->addWidget(editButton);

    QPushButton *deleteButton = new QPushButton("Delete Movie");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = movie.getId();
    connect(deleteButton, &QPushButton::clicked, this, [this]()
            { qDebug() << "deleteItemRequested in ItemShowVisitor" << itemId;
                emit deleteItemRequested(itemId); });
    connect(editButton, &QPushButton::clicked, this, [this]()
            { qDebug() << "editItemRequested in ItemShowVisitor" << itemId;
                emit editItemRequested(itemId); });

    widget = result;
}

void ItemShowVisitor::visit(Article &article)
{
    QWidget *result = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(result);

    layout->addWidget(new QLabel("📝 Article"));
    layout->addWidget(new QLabel("Title: " + article.getTitle()));
    layout->addWidget(new QLabel("Link: " + article.getLink()));
    layout->addWidget(new QLabel("Author: " + article.getAuthor()));
    layout->addWidget(new QLabel("Year: " + QString::number(article.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(article.getReview())));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *editButton = new QPushButton("Edit Article");
    horizontalLayout->addWidget(editButton);

    QPushButton *deleteButton = new QPushButton("Delete Article");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = article.getId();
    connect(deleteButton, &QPushButton::clicked, this, [this]()
            { qDebug() << "deleteItemRequested in ItemShowVisitor" << itemId;
                emit deleteItemRequested(itemId); });
    connect(editButton, &QPushButton::clicked, this, [this]()
            { qDebug() << "editItemRequested in ItemShowVisitor" << itemId;
                emit editItemRequested(itemId); });

    widget = result;
}
