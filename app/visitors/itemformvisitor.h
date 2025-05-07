#ifndef ITEMFORMVISITOR_H
#define ITEMFORMVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"

#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

class ItemFormVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit ItemFormVisitor(QObject *parent = nullptr);

    QWidget *getResult() const { return form; }

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

private:
    QWidget *form;
};

#endif // ITEMFORMVISITOR_H