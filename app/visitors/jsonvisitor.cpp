#include "jsonvisitor.h"

void JSONVisitor::visit(Book &book)
{
    QJsonObject obj;
    obj["type"] = "book";
    obj["title"] = book.getTitle();
    obj["description"] = book.getDescription();
    obj["year"] = book.getYear();
    obj["review"] = book.getReview();
    obj["comment"] = book.getComment();
    obj["author"] = book.getAuthor();
    result = obj;
}

void JSONVisitor::visit(Movie &movie)
{
    QJsonObject obj;
    obj["type"] = "movie";
    obj["title"] = movie.getTitle();
    obj["description"] = movie.getDescription();
    obj["year"] = movie.getYear();
    obj["review"] = movie.getReview();
    obj["comment"] = movie.getComment();
    obj["director"] = movie.getDirector();
    result = obj;
}

void JSONVisitor::visit(Article &article)
{
    QJsonObject obj;
    obj["type"] = "article";
    obj["title"] = article.getTitle();
    obj["description"] = article.getDescription();
    obj["year"] = article.getYear();
    obj["review"] = article.getReview();
    obj["comment"] = article.getComment();
    obj["link"] = article.getLink();
    obj["author"] = article.getAuthor();
    result = obj;
}