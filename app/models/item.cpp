#include "item.h"

Item::Item(const QString &title, const QString &description,
           int year, int review, const QString &comment)
    : title(title), description(description), year(year), review(review >= 1 && review <= 5 ? review : 3), comment(comment)
{
}