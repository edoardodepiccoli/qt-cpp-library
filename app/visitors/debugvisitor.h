#ifndef DEBUGVISITOR_H
#define DEBUGVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"

class DebugVisitor : public Visitor
{
public:
    DebugVisitor() = default;
    ~DebugVisitor() override = default;

    void visit(Book &book) override;
    void visit(Movie &movie) override;
    void visit(Article &article) override;
};

#endif // DEBUGVISITOR_H