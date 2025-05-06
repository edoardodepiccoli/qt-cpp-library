#ifndef ARTICLE_H
#define ARTICLE_H

#include "item.h"

class Visitor;

class Article : public Item
{
public:
    Article(const QString &title = "", const QString &description = "",
            int year = 0, int review = 3, const QString &comment = "",
            const QString &link = "");

    QString getLink() const { return link; }
    void setLink(const QString &l) { link = l; }

    void accept(Visitor &visitor) override;

private:
    QString link;
};

#endif // ARTICLE_H