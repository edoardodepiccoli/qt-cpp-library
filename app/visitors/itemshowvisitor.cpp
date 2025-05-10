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
    static const QMap<QString, QString> defaultImages = {
        {"Book", "app/db/default_book.png"},
        {"Movie", "app/db/default_movie.png"},
        {"Article", "app/db/default_article.png"}};

    for (const auto &key : defaultImages.keys())
    {
        if (type.contains(key))
        {
            return defaultImages[key];
        }
    }
    return "app/db/default.png";
}

QPixmap ItemShowVisitor::loadImage(const QString &path, const QString &type)
{
    QPixmap pixmap;
    if (!path.isEmpty() && QFileInfo::exists(path))
    {
        if (!pixmap.load(path))
        {
            qWarning() << "Failed to load image from path:" << path;
        }
    }

    if (pixmap.isNull())
    {
        QString defaultPath = getDefaultImagePath(type);
        if (QFileInfo::exists(defaultPath))
        {
            if (!pixmap.load(defaultPath))
            {
                qWarning() << "Failed to load default image from path:" << defaultPath;
            }
        }
        if (pixmap.isNull())
        {
            pixmap.load("app/db/default.png");
        }
    }

    return pixmap.scaledToWidth(IMAGE_MAX_WIDTH, Qt::SmoothTransformation);
}

QWidget *ItemShowVisitor::createImageWidget(const QString &imagePath, const QString &type)
{
    QWidget *imageWidget = new QWidget;
    QVBoxLayout *imageLayout = new QVBoxLayout(imageWidget);

    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(loadImage(imagePath, type));
    imageLabel->setAlignment(Qt::AlignCenter);

    imageLayout->addWidget(imageLabel);
    imageLayout->addStretch();

    return imageWidget;
}

QWidget *ItemShowVisitor::createInfoWidget(const ItemData &data)
{
    QWidget *infoWidget = new QWidget;
    QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);

    // Add type and title
    infoLayout->addWidget(new QLabel(data.type));
    infoLayout->addWidget(new QLabel("Title: " + data.title));

    // Add description with word wrap
    QLabel *descLabel = new QLabel("Description: " + data.description);
    descLabel->setWordWrap(true);
    infoLayout->addWidget(descLabel);

    // Add extra info
    for (const QString &info : data.extraInfo)
    {
        infoLayout->addWidget(new QLabel(info));
    }

    // Add year and review
    infoLayout->addWidget(new QLabel("Year: " + data.year));
    infoLayout->addWidget(new QLabel("Review: " + data.review));

    // Add comment with word wrap
    QLabel *commentLabel = new QLabel("Comment: " + data.comment);
    commentLabel->setWordWrap(true);
    infoLayout->addWidget(commentLabel);

    // Add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *editButton = new QPushButton("Edit " + data.type);
    QPushButton *deleteButton = new QPushButton("Delete " + data.type);

    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, [this]()
            { emit deleteItemRequested(itemId); });
    connect(editButton, &QPushButton::clicked, this, [this]()
            { emit editItemRequested(itemId); });

    infoLayout->addLayout(buttonLayout);
    infoLayout->addStretch();

    return infoWidget;
}

QWidget *ItemShowVisitor::createItemWidget(const ItemData &data)
{
    QWidget *result = new QFrame;
    QHBoxLayout *mainLayout = new QHBoxLayout(result);

    mainLayout->addWidget(createImageWidget(data.imagePath, data.type));
    mainLayout->addWidget(createInfoWidget(data));

    return result;
}

ItemShowVisitor::ItemData ItemShowVisitor::extractItemData(const Book &book)
{
    ItemData data;
    data.type = "📚 Book";
    data.title = book.getTitle();
    data.description = book.getDescription();
    data.year = QString::number(book.getYear());
    data.review = QString::number(book.getReview());
    data.comment = book.getComment();
    data.imagePath = book.getImagePath();
    data.extraInfo << "Author: " + book.getAuthor();
    return data;
}

ItemShowVisitor::ItemData ItemShowVisitor::extractItemData(const Movie &movie)
{
    ItemData data;
    data.type = "🎬 Movie";
    data.title = movie.getTitle();
    data.description = movie.getDescription();
    data.year = QString::number(movie.getYear());
    data.review = QString::number(movie.getReview());
    data.comment = movie.getComment();
    data.imagePath = movie.getImagePath();
    data.extraInfo << "Director: " + movie.getDirector();
    return data;
}

ItemShowVisitor::ItemData ItemShowVisitor::extractItemData(const Article &article)
{
    ItemData data;
    data.type = "📝 Article";
    data.title = article.getTitle();
    data.description = article.getDescription();
    data.year = QString::number(article.getYear());
    data.review = QString::number(article.getReview());
    data.comment = article.getComment();
    data.imagePath = article.getImagePath();
    data.extraInfo << "Author: " + article.getAuthor();
    data.extraInfo << "Link: " + article.getLink();
    return data;
}

void ItemShowVisitor::visit(Book &book)
{
    clearWidget();
    itemId = book.getId();
    widget = createItemWidget(extractItemData(book));
}

void ItemShowVisitor::visit(Movie &movie)
{
    clearWidget();
    itemId = movie.getId();
    widget = createItemWidget(extractItemData(movie));
}

void ItemShowVisitor::visit(Article &article)
{
    clearWidget();
    itemId = article.getId();
    widget = createItemWidget(extractItemData(article));
}
