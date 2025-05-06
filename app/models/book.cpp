#include "book.h"
#include "../visitors/visitor.h"

Book::Book(const QString& title, const QString& description, 
           int year, const int& review, const QString& comment,
           const QString& author)
    : Item(title, description, year, review, comment)
    , author(author)
{
}

void Book::accept(Visitor& visitor) {
    visitor.visit(*this);
} 