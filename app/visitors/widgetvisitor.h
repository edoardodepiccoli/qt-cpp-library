#ifndef WIDGETVISITOR_H
#define WIDGETVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"

#include <QWidget>

class WidgetVisitor : public Visitor
{
public:
    QWidget *getResult() const { return widget; }

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;

private:
    QWidget *widget = nullptr;
};

#endif // WIDGETVISITOR_H
