#include "article.h"
#include "../visitors/visitor.h"

Article::Article(const QString &title, const QString &description,
                 int year, int review, const QString &comment,
                 const QString &link)
    : Item(title, description, year, review, comment), link(link)
{
}

void Article::accept(Visitor &visitor)
{
    visitor.visit(*this);
}