#ifndef ARTICLE_H
#define ARTICLE_H

#include "item.h"

class Visitor;

class Article : public Item
{
public:
    Article(
        const QString &title = "",
        const QString &description = "",
        int year = 0, int review = 3,
        const QString &comment = "",
        const QString &author = "",
        const QString &link = "");
    ~Article() override = default;
    QString getLink() const { return link; }
    void setLink(const QString &l) { link = l; }

    QString getAuthor() const { return author; }
    void setAuthor(const QString &l) { author = l; }

    void accept(Visitor &visitor) override;

private:
    QString link;
    QString author;
};

#endif // ARTICLE_H