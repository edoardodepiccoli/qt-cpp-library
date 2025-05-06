#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include "visitor.h"
#include "../models/book.h"
#include "../models/movie.h"
#include "../models/article.h"
#include <QJsonObject>

class JSONVisitor : public Visitor {
public:
    QJsonObject getResult() const { return result; }
    
    void visit(Book& book) override;
    void visit(Movie& movie) override;
    void visit(Article& article) override;

private:
    QJsonObject result;
};

#endif // JSONVISITOR_H 