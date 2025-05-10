#ifndef ITEMSHOWVISITOR_H
#define ITEMSHOWVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"

#include <QWidget>
#include <QUuid>
#include <QObject>
#include <QLabel>
#include <QString>

class ItemShowVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit ItemShowVisitor(QObject *parent = nullptr);
    ~ItemShowVisitor() override;

    QWidget *getResult() const { return widget; }
    QUuid getItemId() const { return itemId; }

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

signals:
    void deleteItemRequested(const QUuid &itemId);
    void editItemRequested(const QUuid &itemId);

private:
    struct ItemData
    {
        QString type;
        QString title;
        QString description;
        QString year;
        QString review;
        QString comment;
        QString imagePath;
        QStringList extraInfo;
    };

    void clearWidget();
    ItemData extractItemData(const Book &book);
    ItemData extractItemData(const Movie &movie);
    ItemData extractItemData(const Article &article);
    QWidget *createItemWidget(const ItemData &data);
    QWidget *createImageWidget(const QString &imagePath, const QString &type);
    QWidget *createInfoWidget(const ItemData &data);
    QString getDefaultImagePath(const QString &type) const;
    QPixmap loadImage(const QString &path, const QString &type);

    QWidget *widget = nullptr;
    QUuid itemId;
    static const int IMAGE_MAX_WIDTH = 300;
};

#endif // ITEMSHOWVISITOR_H
