#ifndef ITEMCARDVISITOR_H
#define ITEMCARDVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"

#include <QWidget>
#include <QUuid>
#include <QObject>

class ItemCardVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit ItemCardVisitor(QObject *parent = nullptr);
    ~ItemCardVisitor() override;

    QWidget *getResult() const { return widget; }
    QUuid getItemId() const { return itemId; }

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

signals:
    void itemShowRequested(const QUuid &itemId);

private:
    void clearWidget();
    QWidget *widget = nullptr;
    QUuid itemId;
};

#endif // ITEMCARDVISITOR_H
