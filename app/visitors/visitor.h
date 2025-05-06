#ifndef VISITOR_H
#define VISITOR_H

class Book;
class Movie;
class Article;

class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visit(Book &book) = 0;
    virtual void visit(Movie &movie) = 0;
    virtual void visit(Article &article) = 0;
};

#endif // VISITOR_H