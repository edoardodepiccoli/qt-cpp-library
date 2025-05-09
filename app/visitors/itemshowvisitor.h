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
    void clearWidget();
    QWidget *createImageWidget(const QString &imagePath, const QString &type);
    QWidget *createInfoWidget(const QString &type, const QString &title, const QString &description,
                              const QString &year, const QString &review, const QString &comment,
                              const QString &extraInfo1, const QString &extraInfo2 = QString());
    QString getDefaultImagePath(const QString &type) const;

    QWidget *widget = nullptr;
    QUuid itemId;
    static const int IMAGE_MAX_WIDTH = 300; // Maximum width for the image
};

#endif // ITEMSHOWVISITOR_H
