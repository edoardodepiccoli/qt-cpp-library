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

ItemShowVisitor::~ItemShowVisitor()
{
    clearWidget();
}

void ItemShowVisitor::clearWidget()
{
    if (widget)
    {
        delete widget;
        widget = nullptr;
    }
}

void ItemShowVisitor::visit(Book &book)
{
    clearWidget(); // Clear any existing widget before creating a new one

    QWidget *result = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(result);

    layout->addWidget(new QLabel("📚 Book"));
    layout->addWidget(new QLabel("Title: " + book.getTitle()));

    QLabel *descLabel = new QLabel("Description: " + book.getDescription());
    descLabel->setWordWrap(true);
    layout->addWidget(descLabel);

    layout->addWidget(new QLabel("Author: " + book.getAuthor()));
    layout->addWidget(new QLabel("Year: " + QString::number(book.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(book.getReview())));

    QLabel *commentLabel = new QLabel("Comment: " + book.getComment());
    commentLabel->setWordWrap(true);
    layout->addWidget(commentLabel);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *editButton = new QPushButton("Edit Book");
    horizontalLayout->addWidget(editButton);

    QPushButton *deleteButton = new QPushButton("Delete Book");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = book.getId();
    connect(deleteButton, &QPushButton::clicked, this, [this]()
            { emit deleteItemRequested(itemId); });
    connect(editButton, &QPushButton::clicked, this, [this]()
            { emit editItemRequested(itemId); });

    widget = result;
}

void ItemShowVisitor::visit(Movie &movie)
{
    clearWidget(); // Clear any existing widget before creating a new one

    QWidget *result = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(result);

    layout->addWidget(new QLabel("🎬 Movie"));
    layout->addWidget(new QLabel("Title: " + movie.getTitle()));

    QLabel *descLabel = new QLabel("Description: " + movie.getDescription());
    descLabel->setWordWrap(true);
    layout->addWidget(descLabel);

    layout->addWidget(new QLabel("Director: " + movie.getDirector()));
    layout->addWidget(new QLabel("Year: " + QString::number(movie.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(movie.getReview())));

    QLabel *commentLabel = new QLabel("Comment: " + movie.getComment());
    commentLabel->setWordWrap(true);
    layout->addWidget(commentLabel);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *editButton = new QPushButton("Edit Movie");
    horizontalLayout->addWidget(editButton);

    QPushButton *deleteButton = new QPushButton("Delete Movie");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = movie.getId();
    connect(deleteButton, &QPushButton::clicked, this, [this]()
            { emit deleteItemRequested(itemId); });
    connect(editButton, &QPushButton::clicked, this, [this]()
            { emit editItemRequested(itemId); });

    widget = result;
}

void ItemShowVisitor::visit(Article &article)
{
    clearWidget(); // Clear any existing widget before creating a new one

    QWidget *result = new QFrame;
    QVBoxLayout *layout = new QVBoxLayout(result);

    layout->addWidget(new QLabel("📝 Article"));
    layout->addWidget(new QLabel("Title: " + article.getTitle()));

    QLabel *descLabel = new QLabel("Description: " + article.getDescription());
    descLabel->setWordWrap(true);
    layout->addWidget(descLabel);

    layout->addWidget(new QLabel("Author: " + article.getAuthor()));

    QLabel *linkLabel = new QLabel("Link: " + article.getLink());
    linkLabel->setWordWrap(true);
    layout->addWidget(linkLabel);

    layout->addWidget(new QLabel("Year: " + QString::number(article.getYear())));
    layout->addWidget(new QLabel("Review: " + QString::number(article.getReview())));

    QLabel *commentLabel = new QLabel("Comment: " + article.getComment());
    commentLabel->setWordWrap(true);
    layout->addWidget(commentLabel);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    QPushButton *editButton = new QPushButton("Edit Article");
    horizontalLayout->addWidget(editButton);

    QPushButton *deleteButton = new QPushButton("Delete Article");
    horizontalLayout->addWidget(deleteButton);

    layout->addLayout(horizontalLayout);

    itemId = article.getId();
    connect(deleteButton, &QPushButton::clicked, this, [this]()
            { emit deleteItemRequested(itemId); });
    connect(editButton, &QPushButton::clicked, this, [this]()
            { emit editItemRequested(itemId); });

    widget = result;
}
