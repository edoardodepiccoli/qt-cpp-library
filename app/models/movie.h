#ifndef MOVIE_H
#define MOVIE_H

#include "item.h"

class Visitor;

class Movie : public Item
{
public:
    Movie(const QString &title = "", const QString &description = "",
          int year = 0, int review = 3, const QString &comment = "",
          const QString &director = "");
    ~Movie() override = default;

    QString getDirector() const { return director; }
    void setDirector(const QString &d) { director = d; }

    void accept(Visitor &visitor) override;

private:
    QString director;
};

#endif // MOVIE_H