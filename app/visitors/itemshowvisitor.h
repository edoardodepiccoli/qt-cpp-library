#ifndef ITEMSHOWVISITOR_H
#define ITEMSHOWVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"

#include <QWidget>
#include <QUuid>
#include <QObject>

class ItemShowVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit ItemShowVisitor(QObject *parent = nullptr);
    ~ItemShowVisitor() override = default;

    QWidget *getResult() const { return widget; }
    QUuid getItemId() const { return itemId; }

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

signals:
    void deleteItemRequested(const QUuid &itemId);
    void editItemRequested(const QUuid &itemId);

private:
    QWidget *widget = nullptr;
    QUuid itemId;
};

#endif // ITEMSHOWVISITOR_H
