#ifndef BOOK_H
#define BOOK_H

#include "item.h"

class Visitor;

class Book : public Item
{
public:
    Book(const QString &title = "", const QString &description = "",
         int year = 0, const int &review = 3, const QString &comment = "",
         const QString &author = "");
    ~Book() override = default;

    QString getAuthor() const { return author; }
    void setAuthor(const QString &a) { author = a; }

    void accept(Visitor &visitor) override;

private:
    QString author;
};

#endif // BOOK_H