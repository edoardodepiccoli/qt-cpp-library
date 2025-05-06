#include "movie.h"
#include "../visitors/visitor.h"

Movie::Movie(const QString &title, const QString &description,
             int year, int review, const QString &comment,
             const QString &director)
    : Item(title, description, year, review, comment), director(director)
{
}

void Movie::accept(Visitor &visitor)
{
    visitor.visit(*this);
}