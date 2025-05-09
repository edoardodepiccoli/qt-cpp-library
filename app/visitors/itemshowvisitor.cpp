#include "itemshowvisitor.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QUuid>
#include <QDebug>
#include <QPixmap>
#include <QFileInfo>

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

QString ItemShowVisitor::getDefaultImagePath(const QString &type) const
{
    if (type.contains("Book"))
    {
        return "app/db/default_book.png";
    }
    else if (type.contains("Movie"))
    {
        return "app/db/default_movie.png";
    }
    else if (type.contains("Article"))
    {
        return "app/db/default_article.png";
    }
    return "app/db/default.png";
}

QWidget *ItemShowVisitor::createImageWidget(const QString &imagePath, const QString &type)
{
    QWidget *imageWidget = new QWidget;
    QVBoxLayout *imageLayout = new QVBoxLayout(imageWidget);

    QLabel *imageLabel = new QLabel;
    QPixmap pixmap;

    if (!imagePath.isEmpty() && QFileInfo::exists(imagePath))
    {
        pixmap.load(imagePath);
    }
    else
    {
        // Load default image based on type
        QString defaultPath = getDefaultImagePath(type);
        if (QFileInfo::exists(defaultPath))
        {
            pixmap.load(defaultPath);
        }
        else
        {
            // If type-specific default doesn't exist, try generic default
            pixmap.load("app/db/default.png");
        }
    }

    // Scale the image while maintaining aspect ratio
    pixmap = pixmap.scaledToWidth(IMAGE_MAX_WIDTH, Qt::SmoothTransformation);
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);

    imageLayout->addWidget(imageLabel);
    imageLayout->addStretch(); // Push image to the top

    return imageWidget;
}

QWidget *ItemShowVisitor::createInfoWidget(const QString &type, const QString &title,
                                           const QString &description, const QString &year,
                                           const QString &review, const QString &comment,
                                           const QString &extraInfo1, const QString &extraInfo2)
{
    QWidget *infoWidget = new QWidget;
    QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);

    // Add all the information
    infoLayout->addWidget(new QLabel(type));
    infoLayout->addWidget(new QLabel("Title: " + title));

    QLabel *descLabel = new QLabel("Description: " + description);
    descLabel->setWordWrap(true);
    infoLayout->addWidget(descLabel);

    infoLayout->addWidget(new QLabel(extraInfo1));
    if (!extraInfo2.isEmpty())
    {
        infoLayout->addWidget(new QLabel(extraInfo2));
    }

    infoLayout->addWidget(new QLabel("Year: " + year));
    infoLayout->addWidget(new QLabel("Review: " + review));

    QLabel *commentLabel = new QLabel("Comment: " + comment);
    commentLabel->setWordWrap(true);
    infoLayout->addWidget(commentLabel);

    // Add buttons at the bottom
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *editButton = new QPushButton("Edit " + type);
    QPushButton *deleteButton = new QPushButton("Delete " + type);

    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    infoLayout->addLayout(buttonLayout);
    infoLayout->addStretch(); // Push all content to the top

    // Connect buttons
    connect(deleteButton, &QPushButton::clicked, this, [this]()
            { emit deleteItemRequested(itemId); });
    connect(editButton, &QPushButton::clicked, this, [this]()
            { emit editItemRequested(itemId); });

    return infoWidget;
}

void ItemShowVisitor::visit(Book &book)
{
    clearWidget();

    QWidget *result = new QFrame;
    QHBoxLayout *mainLayout = new QHBoxLayout(result);

    // Create image widget
    QWidget *imageWidget = createImageWidget(book.getImagePath(), "Book");
    mainLayout->addWidget(imageWidget);

    // Create info widget
    QWidget *infoWidget = createInfoWidget("📚 Book", book.getTitle(), book.getDescription(),
                                           QString::number(book.getYear()), QString::number(book.getReview()),
                                           book.getComment(), "Author: " + book.getAuthor());
    mainLayout->addWidget(infoWidget);

    itemId = book.getId();
    widget = result;
}

void ItemShowVisitor::visit(Movie &movie)
{
    clearWidget();

    QWidget *result = new QFrame;
    QHBoxLayout *mainLayout = new QHBoxLayout(result);

    // Create image widget
    QWidget *imageWidget = createImageWidget(movie.getImagePath(), "Movie");
    mainLayout->addWidget(imageWidget);

    // Create info widget
    QWidget *infoWidget = createInfoWidget("🎬 Movie", movie.getTitle(), movie.getDescription(),
                                           QString::number(movie.getYear()), QString::number(movie.getReview()),
                                           movie.getComment(), "Director: " + movie.getDirector());
    mainLayout->addWidget(infoWidget);

    itemId = movie.getId();
    widget = result;
}

void ItemShowVisitor::visit(Article &article)
{
    clearWidget();

    QWidget *result = new QFrame;
    QHBoxLayout *mainLayout = new QHBoxLayout(result);

    // Create image widget
    QWidget *imageWidget = createImageWidget(article.getImagePath(), "Article");
    mainLayout->addWidget(imageWidget);

    // Create info widget
    QWidget *infoWidget = createInfoWidget("📝 Article", article.getTitle(), article.getDescription(),
                                           QString::number(article.getYear()), QString::number(article.getReview()),
                                           article.getComment(), "Author: " + article.getAuthor(),
                                           "Link: " + article.getLink());
    mainLayout->addWidget(infoWidget);

    itemId = article.getId();
    widget = result;
}
