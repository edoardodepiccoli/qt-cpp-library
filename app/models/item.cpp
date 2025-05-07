#include "item.h"

Item::Item(const QString &title, const QString &description,
           int year, int review, const QString &comment)
    : id(QUuid::createUuid()), // Generate unique ID on construction, see more on QUuid in the docs
      title(title),
      description(description),
      year(year),
      review(review >= 1 && review <= 5 ? review : 3),
      comment(comment)
{
}