#ifndef ITEM_H
#define ITEM_H

#include <QUuid>
#include <QString>

class Visitor; // Forward declaration

class Item
{
public:
    Item(const QString &title = "", const QString &description = "",
         int year = 0, int review = 3, const QString &comment = "");
    virtual ~Item() = default;

    QUuid getId() const { return id; }
    void setId(const QUuid &newId) { id = newId; }

    QString getTitle() const { return title; }
    QString getDescription() const { return description; }
    int getYear() const { return year; }
    int getReview() const { return review; }
    QString getComment() const { return comment; }

    void setTitle(const QString &t) { title = t; }
    void setDescription(const QString &d) { description = d; }
    void setYear(int y) { year = y; }
    void setReview(int r)
    {
        if (r >= 1 && r <= 5)
        {
            review = r;
        }
    }
    void setComment(const QString &c) { comment = c; }

    virtual void accept(Visitor &visitor) = 0;

protected:
    QUuid id; // Add unique identifier because without that it would be a mess
    QString title;
    QString description;
    int year;
    int review;
    QString comment;
};

#endif // ITEM_H